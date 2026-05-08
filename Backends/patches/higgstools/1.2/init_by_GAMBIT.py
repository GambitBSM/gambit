"""
GAMBIT wrapper around the HiggsTools Python interface.

This file is copied into the HiggsTools install directory at configure time
and is the single entry point that GAMBIT's HiggsTools frontend imports.
It exposes two convenience functions, lhc_chisq and run_bounds, that build
a Higgs.predictions.Predictions object from a plain Python dict and return
the LHC HiggsSignals chi^2 (and the HiggsBounds applied-limits result),
respectively.

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

hb_data_path = os.path.join(_here, "hbdataset")
hs_data_path = os.path.join(_here, "hsdataset")

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
        # CP = +1 for scalar, -1 for pseudoscalar; HiggsTools uses an enum.
        cp = d["CP"][i]
        cp_label = HP.ECharge.neutral
        ref_model = HP.ReferenceModel.SMHiggsEW
        h_id = "h{0}".format(i + 1)
        neutral_ids.append(h_id)
        h = pred.addParticle(HP.BsmParticle(h_id, cp_label,
                                            HP.CP.even if cp >= 0 else HP.CP.odd))
        h.setMass(d["Mh"][i])
        h.setTotalWidth(d["hGammaTot"][i])
        # Branching ratios to SM final states.
        h.setBr("ss", d["BR_hjss"][i])
        h.setBr("cc", d["BR_hjcc"][i])
        h.setBr("bb", d["BR_hjbb"][i])
        h.setBr("mumu", d["BR_hjmumu"][i])
        h.setBr("tautau", d["BR_hjtautau"][i])
        h.setBr("WW", d["BR_hjWW"][i])
        h.setBr("ZZ", d["BR_hjZZ"][i])
        h.setBr("Zgam", d["BR_hjZga"][i])
        h.setBr("gamgam", d["BR_hjgaga"][i])
        h.setBr("gg", d["BR_hjgg"][i])
        h.setBrInv(d["BR_hjinvisible"][i])
        # Effective coupling input is HiggsTools' canonical way of getting
        # production cross-section ratios for free.
        ec = HP.EffectiveCouplings()
        ec.tt = d["g2hjtt"][i] ** 0.5
        ec.bb = d["g2hjbb"][i] ** 0.5
        ec.cc = d["g2hjcc"][i] ** 0.5
        ec.ss = d["g2hjss"][i] ** 0.5
        ec.tautau = d["g2hjtautau"][i] ** 0.5
        ec.mumu = d["g2hjmumu"][i] ** 0.5
        ec.WW = d["g2hjWW"][i] ** 0.5
        ec.ZZ = d["g2hjZZ"][i] ** 0.5
        ec.gamgam = d["g2hjgaga"][i] ** 0.5
        ec.Zgam = d["g2hjZga"][i] ** 0.5
        ec.gg = d["g2hjgg"][i] ** 0.5
        HP.effectiveCouplingInput(h, ec, reference=ref_model)

    # Higgs-to-Higgs cascades (h_i -> h_j h_j).
    BR_hjhihi = d["BR_hjhihi"]
    for i in range(n_neutral):
        for j in range(n_neutral):
            br = BR_hjhihi[i][j]
            if br > 0.0 and i != j:
                pred.particle(neutral_ids[i]).setDecayWidth(neutral_ids[j],
                                                            neutral_ids[j], br)

    # Charged Higgs sector
    for k in range(n_charged):
        hp = pred.addParticle(HP.BsmParticle("Hp{0}".format(k + 1),
                                             HP.ECharge.single))
        hp.setMass(d["MHplus"][k])
        hp.setTotalWidth(d["HpGammaTot"][k])
        hp.setBr("cs", d["BR_Hpjcs"][k])
        hp.setBr("cb", d["BR_Hpjcb"][k])
        hp.setBr("taunu", d["BR_Hptaunu"][k])

    # Top quark BRs (only if a charged Higgs is present).
    if n_charged > 0:
        pred.setBrTopWb(d["BR_tWpb"])
        for k in range(n_charged):
            pred.setBrTopHpjb(k, d["BR_tHpjb"][k])

    return pred


def lhc_chisq(d):
    """Return the HiggsSignals chi^2 (LHC Higgs measurements)."""
    pred = _build_predictions(d)
    res = _signals()(pred)
    # HSResult.chisq holds the total chi^2 in HiggsTools 1.2.
    return float(getattr(res, "chisq", res))


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
