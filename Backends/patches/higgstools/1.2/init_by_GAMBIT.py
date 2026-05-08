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
        h.setTotalWidth(d["hGammaTot"][i])

        # SM-like decay channels.  HiggsTools rejects setBr if the cumulative
        # BR sum would exceed 1; GAMBIT's DecayTable BRs can sum to slightly
        # above unity due to floating-point round-off, so renormalise here.
        sm_brs = [
            (HP.Decay.ss, d["BR_hjss"][i]),
            (HP.Decay.cc, d["BR_hjcc"][i]),
            (HP.Decay.bb, d["BR_hjbb"][i]),
            (HP.Decay.mumu, d["BR_hjmumu"][i]),
            (HP.Decay.tautau, d["BR_hjtautau"][i]),
            (HP.Decay.WW, d["BR_hjWW"][i]),
            (HP.Decay.ZZ, d["BR_hjZZ"][i]),
            (HP.Decay.Zgam, d["BR_hjZga"][i]),
            (HP.Decay.gamgam, d["BR_hjgaga"][i]),
            (HP.Decay.gg, d["BR_hjgg"][i]),
            (HP.Decay.directInv, d["BR_hjinvisible"][i]),
        ]
        # Include h_i -> h_j h_j cascades in the normalisation budget.
        cascade_brs = [d["BR_hjhihi"][i][j] for j in range(n_neutral)
                       if d["BR_hjhihi"][i][j] > 0.0]
        total_br = sum(br for _, br in sm_brs) + sum(cascade_brs)
        norm = total_br if total_br > 1.0 else 1.0
        for decay, br in sm_brs:
            h.setBr(decay, br / norm)

        # Effective couplings -> production cross-section ratios for free.
        # Square-rooted because GAMBIT stores g^2 while HiggsTools wants g.
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

    # Higgs-to-Higgs cascades (h_i -> h_j h_j) via the (id1, id2, value)
    # overload of setBr.  Normalise against the same budget as the SM BRs.
    BR_hjhihi = d["BR_hjhihi"]
    for i in range(n_neutral):
        sm_total = (d["BR_hjss"][i] + d["BR_hjcc"][i] + d["BR_hjbb"][i]
                    + d["BR_hjmumu"][i] + d["BR_hjtautau"][i]
                    + d["BR_hjWW"][i] + d["BR_hjZZ"][i] + d["BR_hjZga"][i]
                    + d["BR_hjgaga"][i] + d["BR_hjgg"][i]
                    + d["BR_hjinvisible"][i])
        cascade_total = sum(BR_hjhihi[i][j] for j in range(n_neutral)
                            if BR_hjhihi[i][j] > 0.0)
        norm = sm_total + cascade_total
        if norm <= 1.0:
            norm = 1.0
        for j in range(n_neutral):
            br = BR_hjhihi[i][j]
            if br > 0.0:
                pred.particle(neutral_ids[i]).setBr(
                    neutral_ids[j], neutral_ids[j], br / norm
                )

    # Charged Higgs sector.
    for k in range(n_charged):
        hp = pred.addParticle(
            HP.BsmParticle("Hp{0}".format(k + 1), HP.ECharge.single, HP.CP.undefined)
        )
        hp.setMass(d["MHplus"][k])
        hp.setTotalWidth(d["HpGammaTot"][k])
        ch_brs = [
            (HP.Decay.cs, d["BR_Hpjcs"][k]),
            (HP.Decay.cb, d["BR_Hpjcb"][k]),
            (HP.Decay.taunu, d["BR_Hptaunu"][k]),
        ]
        ch_total = sum(br for _, br in ch_brs)
        ch_norm = ch_total if ch_total > 1.0 else 1.0
        for decay, br in ch_brs:
            hp.setBr(decay, br / ch_norm)

        # t -> H+ b is modelled as a "production" rate of the charged Higgs.
        # Apply at all colliders HiggsTools is aware of.
        for coll in (HP.Collider.LHC8, HP.Collider.LHC13):
            hp.setCxn(coll, HP.Production.brtHpb, d["BR_tHpjb"][k])

    if n_charged > 0:
        pred.setBrTopWb(d["BR_tWpb"])

    return pred


def lhc_chisq(d):
    """Return the HiggsSignals chi^2 (LHC Higgs measurements)."""
    pred = _build_predictions(d)
    res = _signals()(pred)
    # Signals(pred) returns a plain float in HiggsTools 1.2.
    return float(res)


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
