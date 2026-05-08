//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for the HiggsTools backend.
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/HiggsTools_1_2.hpp"

#ifdef HAVE_PYBIND11

  #include "gambit/Utils/begin_ignore_warnings_pybind11.hpp"
  #include <pybind11/stl.h>
  #include "gambit/Utils/end_ignore_warnings.hpp"

  BE_NAMESPACE
  {
    using namespace pybind11::literals;

    // Convert a HiggsTools_input struct into a pybind11::dict.
    static pybind11::dict input_to_dict(const HiggsTools_input& in)
    {
      pybind11::dict d;
      d["n_neutral"] = in.n_neutral;
      d["n_charged"] = in.n_charged;
      d["Mh"] = pybind11::cast(in.Mh);
      d["deltaMh"] = pybind11::cast(in.deltaMh);
      d["hGammaTot"] = pybind11::cast(in.hGammaTot);
      d["CP"] = pybind11::cast(in.CP);
      d["BR_hjss"] = pybind11::cast(in.BR_hjss);
      d["BR_hjcc"] = pybind11::cast(in.BR_hjcc);
      d["BR_hjbb"] = pybind11::cast(in.BR_hjbb);
      d["BR_hjmumu"] = pybind11::cast(in.BR_hjmumu);
      d["BR_hjtautau"] = pybind11::cast(in.BR_hjtautau);
      d["BR_hjWW"] = pybind11::cast(in.BR_hjWW);
      d["BR_hjZZ"] = pybind11::cast(in.BR_hjZZ);
      d["BR_hjZga"] = pybind11::cast(in.BR_hjZga);
      d["BR_hjgaga"] = pybind11::cast(in.BR_hjgaga);
      d["BR_hjgg"] = pybind11::cast(in.BR_hjgg);
      d["BR_hjinvisible"] = pybind11::cast(in.BR_hjinvisible);
      d["BR_hjhihi"] = pybind11::cast(in.BR_hjhihi);
      d["g2hjss"] = pybind11::cast(in.g2hjss);
      d["g2hjcc"] = pybind11::cast(in.g2hjcc);
      d["g2hjbb"] = pybind11::cast(in.g2hjbb);
      d["g2hjtt"] = pybind11::cast(in.g2hjtt);
      d["g2hjmumu"] = pybind11::cast(in.g2hjmumu);
      d["g2hjtautau"] = pybind11::cast(in.g2hjtautau);
      d["g2hjWW"] = pybind11::cast(in.g2hjWW);
      d["g2hjZZ"] = pybind11::cast(in.g2hjZZ);
      d["g2hjgaga"] = pybind11::cast(in.g2hjgaga);
      d["g2hjZga"] = pybind11::cast(in.g2hjZga);
      d["g2hjgg"] = pybind11::cast(in.g2hjgg);
      d["MHplus"] = pybind11::cast(in.MHplus);
      d["deltaMHplus"] = pybind11::cast(in.deltaMHplus);
      d["HpGammaTot"] = pybind11::cast(in.HpGammaTot);
      d["BR_Hpjcs"] = pybind11::cast(in.BR_Hpjcs);
      d["BR_Hpjcb"] = pybind11::cast(in.BR_Hpjcb);
      d["BR_Hptaunu"] = pybind11::cast(in.BR_Hptaunu);
      d["BR_tWpb"] = in.BR_tWpb;
      d["BR_tHpjb"] = pybind11::cast(in.BR_tHpjb);
      return d;
    }

    /// LHC HiggsSignals log-likelihood (= -0.5 * chi^2).
    double HiggsTools_LHC_LogLike(const HiggsTools_input& in)
    {
      double chisq;
      #pragma omp critical (HiggsTools)
      {
        pybind11::dict d = input_to_dict(in);
        chisq = HiggsTools.attr("lhc_chisq")(d).cast<double>();
      }
      return -0.5 * chisq;
    }

    /// Strongest HiggsBounds applied-limit obs/exp ratio (raw, not a likelihood).
    double HiggsTools_run_bounds(const HiggsTools_input& in)
    {
      double obsRatio;
      #pragma omp critical (HiggsTools)
      {
        pybind11::dict d = input_to_dict(in);
        obsRatio = HiggsTools.attr("run_bounds")(d).cast<double>();
      }
      return obsRatio;
    }
  }
  END_BE_NAMESPACE

#endif

BE_INI_FUNCTION
{}
END_BE_INI_FUNCTION
