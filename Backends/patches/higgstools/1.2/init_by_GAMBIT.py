"""GAMBIT wrapper around the HiggsTools Python interface.

Loaded by GAMBIT's HiggsTools_1_2 frontend.  Exposes lhc_chisq(d) (the
LHC HiggsSignals chi^2) and run_bounds(d) (the strongest HiggsBounds
applied-limit obs/exp ratio).  d is a plain dict matching the C++
struct HiggsTools_input (see Backends/include/gambit/Backends/
backend_types/HiggsTools.hpp).  HiggsTools 1.2 has no dedicated LEP
chi^2.

Set GAMBIT_HIGGSTOOLS_DUMP=<path> to JSON-dump every input dict (one
record per line) for offline replay/cross-checks.
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

# Data sets installed in sibling backend dirs (see cmake/backends.cmake).
_installed = os.path.dirname(os.path.dirname(_here))
hb_data_path = os.path.join(_installed, "higgstools_hbdataset", "1.2")
hs_data_path = os.path.join(_installed, "higgstools_hsdataset", "1.2")

# Cache the heavy Bounds/Signals objects: loaded once per process.
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
    """Translate a GAMBIT HiggsTools_input dict into a HiggsTools Predictions.

    Neutral SM-channel BRs and total widths are derived inside HiggsTools by
    effectiveCouplingInput from the squared effective couplings; the
    BR_hj* and hGammaTot fields in d are not currently pushed to HiggsTools
    (deviations from coupling-squared scaling for SM channels are typically
    sub-percent and below LHC sensitivity).  Non-SM neutral channels
    (invisibles, h_i->h_j h_j) are added as partial widths below.
    """
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

        # GAMBIT's HiggsCouplingsTable lacks first-gen Yukawas and lam;
        # default dd <- ss, uu <- cc, ee <- mumu, lam <- 1.0 (SM-aligned).
        # See HiggsTools.hpp for the cleanup recipe if a future model needs
        # non-MFV first-gen Yukawas or a non-SM Higgs trilinear.
        def s(x):
            return x ** 0.5
        ec = HP.NeutralEffectiveCouplings(
            uu=s(d["g2hjcc"][i]),
            cc=s(d["g2hjcc"][i]),
            tt=s(d["g2hjtt"][i]),
            dd=s(d["g2hjss"][i]),
            ss=s(d["g2hjss"][i]),
            bb=s(d["g2hjbb"][i]),
            ee=s(d["g2hjmumu"][i]),
            mumu=s(d["g2hjmumu"][i]),
            tautau=s(d["g2hjtautau"][i]),
            WW=s(d["g2hjWW"][i]),
            ZZ=s(d["g2hjZZ"][i]),
            Zgam=s(d["g2hjZga"][i]),
            gamgam=s(d["g2hjgaga"][i]),
            gg=s(d["g2hjgg"][i]),
            lam=1.0,
        )
        HP.effectiveCouplingInput(h, ec, reference=HP.ReferenceModel.SMHiggsEW)

    # Add invisibles + h_i -> h_j h_j cascades as partial widths
    # (effectiveCouplingInput owns the SM channels). With S = sum(target BRs)
    # and W_SM the original SM-derived total width, w_i = W_SM * b_i / (1 - S)
    # makes the new BRs sum to S and rescales the SM channels to (1 - S).
    for i in range(n_neutral):
        h = pred.particle(neutral_ids[i])
        target = [(HP.Decay.directInv, d["BR_hjinvisible"][i])]
        for j in range(n_neutral):
            br = d["BR_hjhihi"][i][j]
            if br > 0.0:
                target.append(((neutral_ids[j], neutral_ids[j]), br))
        S = sum(b for _, b in target)
        if S <= 0.0:
            continue
        S = min(S, 0.9999)  # keep the rescaling well-defined
        W_SM = h.totalWidth()
        for channel, b in target:
            if b <= 0.0:
                continue
            w = W_SM * b / (1.0 - S)
            if isinstance(channel, tuple):
                h.setDecayWidth(channel[0], channel[1], w)
            else:
                h.setDecayWidth(channel, w)

    # Charged Higgs sector.
    for k in range(n_charged):
        hp = pred.addParticle(
            HP.BsmParticle("Hp{0}".format(k + 1), HP.ECharge.single, HP.CP.undefined)
        )
        hp.setMass(d["MHplus"][k])
        hp.setTotalWidth(d["HpGammaTot"][k])
        # Renormalise charged BRs only if they exceed 1 (round-off).
        ch_brs = [
            (HP.Decay.cs, d["BR_Hpjcs"][k]),
            (HP.Decay.cb, d["BR_Hpjcb"][k]),
            (HP.Decay.taunu, d["BR_Hptaunu"][k]),
        ]
        ch_total = sum(br for _, br in ch_brs)
        ch_norm = ch_total if ch_total > 1.0 else 1.0
        for decay, br in ch_brs:
            hp.setBr(decay, br / ch_norm)

        # t -> H+ b enters as charged-Higgs production at LHC8/13.
        for coll in (HP.Collider.LHC8, HP.Collider.LHC13):
            hp.setCxn(coll, HP.Production.brtHpb, d["BR_tHpjb"][k])

    if n_charged > 0:
        pred.setBrTopWb(d["BR_tWpb"])

    return pred


def _maybe_dump_input(label, d):
    """JSON-dump d to GAMBIT_HIGGSTOOLS_DUMP (one record per line) if set."""
    path = os.environ.get("GAMBIT_HIGGSTOOLS_DUMP")
    if not path:
        return
    import json
    with open(path, "a") as f:
        json.dump({"label": label, "input": d}, f)
        f.write("\n")


def lhc_chisq(d):
    """Return the HiggsSignals chi^2 (LHC Higgs measurements)."""
    _maybe_dump_input("lhc_chisq", d)
    pred = _build_predictions(d)
    return float(_signals()(pred))


def run_bounds(d):
    """Return the strongest HiggsBounds applied-limit obs/exp ratio (0 if none).

    Currently exposed via the HiggsTools backend but not wired into a
    GAMBIT capability; available for future per-analysis queries.
    """
    _maybe_dump_input("run_bounds", d)
    pred = _build_predictions(d)
    res = _bounds()(pred)
    if not res.appliedLimits:
        return 0.0
    return max(lim.obsRatio() for lim in res.appliedLimits)
