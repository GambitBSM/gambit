"""
GAMBIT wrapper around the HiggsTools Python interface.

This file is copied into the HiggsTools install directory at configure time
and is the single entry point that GAMBIT's HiggsTools frontend imports.
It exposes two convenience functions, lhc_chisq and run_bounds, that build
a Higgs.predictions.Predictions object from a plain Python dict and return
the LHC HiggsSignals chi^2 (and the maximum HiggsBounds applied-limit
obs/exp ratio), respectively.

Note: HiggsTools 1.2 has no dedicated LEP chi^2 likelihood; only the
LHC HiggsSignals likelihood is wrapped here.

The input dict layout is documented in the GAMBIT C++ struct
HiggsTools_input (see Backends/include/gambit/Backends/backend_types/
HiggsTools.hpp).  Required keys:

    n_neutral, n_charged: int
    Mh, hGammaTot, CP, BR_hjss, BR_hjcc, BR_hjbb, BR_hjmumu, BR_hjtautau,
    BR_hjWW, BR_hjZZ, BR_hjZga, BR_hjgaga, BR_hjgg, BR_hjinvisible,
    g2hjWW, g2hjZZ, g2hjtt, g2hjbb, g2hjcc, g2hjss, g2hjtautau, g2hjmumu,
    g2hjgaga, g2hjZga, g2hjgg :
        list[float] of length n_neutral
    BR_hjhihi : list[list[float]] of shape (n_neutral, n_neutral)
    MHplus, HpGammaTot, BR_Hpjcs, BR_Hpjcb, BR_Hptaunu :
        list[float] of length n_charged
    BR_tWpb : float
    BR_tHpjb : list[float] of length n_charged

API design note: HiggsTools enforces sum(BR) <= 1 internally, and
``effectiveCouplingInput`` populates SM-channel BRs proportionally to the
effective couplings.  We use that as the primary input (production xsecs +
SM BRs come for free) and only override BRs explicitly for non-SM channels
that effectiveCouplingInput does not touch: invisible decays and
Higgs-to-Higgs cascade decays h_i -> h_j h_j.
"""

import os
import sys

_here = os.path.dirname(os.path.abspath(__file__))
_target = os.path.join(_here, "python_install")
if os.path.isdir(_target) and _target not in sys.path:
    sys.path.insert(0, _target)

import Higgs.predictions as HP
import Higgs.bounds as HB
import Higgs.signals as HS

# Data sets are installed in sibling backend directories (see
# cmake/backends.cmake) and named by the GAMBIT convention.
_installed = os.path.dirname(os.path.dirname(_here))
hb_data_path = os.path.join(_installed, "higgstools_hbdataset", "1.2")
hs_data_path = os.path.join(_installed, "higgstools_hsdataset", "1.2")

# Cache the heavy Bounds/Signals objects so we only load the JSON limit
# and measurement files once per process.
_bounds_cache = None
_signals_cache = None


def _bounds():
    global _bounds_cache
    if _bounds_cache is None:
        _bounds_cache = HB.Bounds(hb_data_path)
    return _bounds_cache


def _signals():
    global _signals_cache
    if _signals_cache is None:
        _signals_cache = HS.Signals(hs_data_path)
    return _signals_cache


def _build_predictions(d):
    """Translate a GAMBIT HiggsTools_input dict into a HiggsTools Predictions."""
    pred = HP.Predictions()

    n_neutral = int(d["n_neutral"])
    n_charged = int(d["n_charged"])

    neutral_ids = []
    for i in range(n_neutral):
        cp = HP.CP.even if d["CP"][i] >= 0 else HP.CP.odd
        h_id = "h{0}".format(i + 1)
        neutral_ids.append(h_id)
        h = pred.addParticle(HP.BsmParticle(h_id, HP.ECharge.neutral, cp))
        h.setMass(d["Mh"][i])

        # Effective couplings -> production xsecs and SM-channel BRs.  GAMBIT
        # passes squared-coupling ratios; HiggsTools wants the coupling itself.
        def s(x):
            return x ** 0.5
        ec = HP.NeutralEffectiveCouplings(
            cc=s(d["g2hjcc"][i]),
            ss=s(d["g2hjss"][i]),
            tt=s(d["g2hjtt"][i]),
            bb=s(d["g2hjbb"][i]),
            mumu=s(d["g2hjmumu"][i]),
            tautau=s(d["g2hjtautau"][i]),
            WW=s(d["g2hjWW"][i]),
            ZZ=s(d["g2hjZZ"][i]),
            Zgam=s(d["g2hjZga"][i]),
            gamgam=s(d["g2hjgaga"][i]),
            gg=s(d["g2hjgg"][i]),
        )
        HP.effectiveCouplingInput(h, ec, reference=HP.ReferenceModel.SMHiggsEW)

    # Override BRs for non-SM channels (invisibles + h_i -> h_j h_j cascades).
    # ``effectiveCouplingInput`` already filled the SM channels with BRs that
    # sum to 1; we cannot set further BRs directly without violating that
    # constraint.  Instead we add partial decay widths via setDecayWidth: if
    # the SM-derived total width is W and we want target BR B in a new
    # channel, the required partial width is W * B / (1 - B).
    def _add_channel(particle, target_br, set_width):
        if target_br <= 0.0:
            return
        # Cap the target slightly below 1 to keep the formula well-defined.
        target_br = min(target_br, 0.9999)
        old_w = particle.totalWidth()
        new_partial = old_w * target_br / (1.0 - target_br)
        set_width(new_partial)

    for i in range(n_neutral):
        h = pred.particle(neutral_ids[i])
        _add_channel(h, d["BR_hjinvisible"][i],
                     lambda w, h=h: h.setDecayWidth(HP.Decay.directInv, w))
        for j in range(n_neutral):
            br = d["BR_hjhihi"][i][j]
            if br > 0.0:
                jname = neutral_ids[j]
                _add_channel(h, br,
                             lambda w, h=h, jn=jname: h.setDecayWidth(jn, jn, w))

    # Charged Higgs sector.
    for k in range(n_charged):
        hp = pred.addParticle(
            HP.BsmParticle("Hp{0}".format(k + 1), HP.ECharge.single, HP.CP.undefined)
        )
        hp.setMass(d["MHplus"][k])
        hp.setTotalWidth(d["HpGammaTot"][k])
        # Charged Higgs BRs renormalised to <=1 to absorb GAMBIT round-off.
        ch_brs = [
            (HP.Decay.cs, d["BR_Hpjcs"][k]),
            (HP.Decay.cb, d["BR_Hpjcb"][k]),
            (HP.Decay.taunu, d["BR_Hptaunu"][k]),
        ]
        ch_total = sum(br for _, br in ch_brs)
        ch_norm = ch_total if ch_total > 1.0 else 1.0
        for decay, br in ch_brs:
            hp.setBr(decay, br / ch_norm)

        # t -> H+ b is modelled as a "production" rate of the charged Higgs
        # at the LHC, applied at all colliders HiggsTools is aware of.
        for coll in (HP.Collider.LHC8, HP.Collider.LHC13):
            hp.setCxn(coll, HP.Production.brtHpb, d["BR_tHpjb"][k])

    if n_charged > 0:
        pred.setBrTopWb(d["BR_tWpb"])

    return pred


def lhc_chisq(d):
    """Return the HiggsSignals chi^2 (LHC Higgs measurements)."""
    pred = _build_predictions(d)
    return float(_signals()(pred))


def run_bounds(d):
    """Return the strongest applied-limit obs/exp ratio from HiggsBounds.

    Returns 0.0 if no limit applies.  GAMBIT does not currently turn the
    bounds result into a likelihood; we keep this hook available so that
    individual analyses can be queried in the future.
    """
    pred = _build_predictions(d)
    res = _bounds()(pred)
    if not res.appliedLimits:
        return 0.0
    return max(lim.obsRatio() for lim in res.appliedLimits)
