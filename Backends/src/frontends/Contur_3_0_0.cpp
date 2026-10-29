//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Fronted source for the Contur backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Oct
///
/// \author Tomasz Procter
///          (t.procter.1@research.gla.ac.uk)
/// \date 2021 June
/// \date 2023 May
/// \date  2024 Oct
///
/// \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
/// \date 2023 Feb
///
/// \author Pengxuan Zhu
/// \date 2026 Oct
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/Contur_3_0_0.hpp"

#ifdef HAVE_PYBIND11

  using namespace pybind11::literals;

  BE_NAMESPACE
  {

    // Helper function for setting some default arguments for Contur.
    // Used by the functions Contur_LogLike_from_stream and Contur_LogLike_from_file below.
    void Contur_add_GAMBIT_default_args(pybind11::dict& args_dict)
    {
      args_dict[pybind11::cast("QUIET")] = pybind11::bool_(true);
      args_dict[pybind11::cast("NOMULTIP")] = pybind11::bool_(true);
      args_dict[pybind11::cast("YODASTREAM_API_OUTPUT_OPTIONS")] = pybind11::list();
      args_dict[pybind11::cast("YODASTREAM_API_OUTPUT_OPTIONS")].attr("append")("LLR");
      args_dict[pybind11::cast("YODASTREAM_API_OUTPUT_OPTIONS")].attr("append")("Pool_LLR");
      args_dict[pybind11::cast("YODASTREAM_API_OUTPUT_OPTIONS")].attr("append")("Pool_tags");
    }


    Contur_output Contur_LogLike_from_stream(std::shared_ptr<std::ostringstream> yodastream, std::vector<std::string>& contur_yaml_args)
    {
      //Convert C++ ostringstream to python StringIO
      pybind11::str InputString = pybind11::cast(yodastream->str());
      pybind11::object yoda_string_IO = Contur.attr("StringIO")(InputString);
      yoda_string_IO.attr("seek")(pybind11::int_(pybind11::cast(0)));

      // Get default settings for Contur run and add a couple of our own as defaults for GAMBIT
      pybind11::dict args_dict = 
        ((Contur.attr("arg_utils").attr("get_argparser")(pybind11::cast("analysis"))).attr(
          "parse_args")(pybind11::cast(contur_yaml_args))).attr("__dict__");
      args_dict[pybind11::cast("YODASTREAM")] = yoda_string_IO;

      Contur_add_GAMBIT_default_args(args_dict);

      //Return the contur output.
      pybind11::object output = Contur.attr("run_analysis").attr("main")(args_dict);
      if (!pybind11::isinstance<pybind11::dict>(output))
        throw std::runtime_error("Contur returned no valid measurement point (expected a dictionary).");
      return Contur_output(output.cast<pybind11::dict>());
    }


    Contur_output Contur_LogLike_from_file(str& YODA_filename, std::vector<std::string>& contur_yaml_args)
    {
      // Get default settings for Contur run and add a couple of our own as defaults for GAMBIT
      pybind11::dict args_dict = 
        ((Contur.attr("arg_utils").attr("get_argparser")(pybind11::cast("analysis"))).attr(
          "parse_args")(pybind11::cast(contur_yaml_args))).attr("__dict__");
      args_dict[pybind11::cast("YODASTREAM")] = YODA_filename;

      Contur_add_GAMBIT_default_args(args_dict);

      //Run contur, get a LLR and return it
      pybind11::object output = Contur.attr("run_analysis").attr("main")(args_dict);
      if (!pybind11::isinstance<pybind11::dict>(output))
        throw std::runtime_error("Contur returned no valid measurement point (expected a dictionary).");
      return Contur_output(output.cast<pybind11::dict>());
    }


    //Appends all analyses at given beamString (e.g. 13TeV) that contur knows about to the lit of analyses
    //to study.
    void Contur_get_analyses_from_beam(std::vector<std::string>& analyses, std::string& beamString)
    {
      pybind11::list beams;
      pybind11::object theBeam;
      bool beamFound = false;
      #pragma omp critical
      {
        beams = Contur.attr("static_db").attr("get_beams")();
      }
      for (size_t  i = 0; i < pybind11::len(beams); ++i){
        if (beams[i].attr("id").cast<std::string>() == beamString){
          theBeam = beams[i];
          beamFound = true;
          break;
        }
      }
      if (! beamFound ){
        // TODO: give appropriate warning that we're returning an empty vector.
        analyses = {};
        return;
      }
      # pragma omp critical
      {
        pybind11::list anaObjectList = Contur.attr("static_db").attr("get_analyses")(pybind11::none(), pybind11::none(), theBeam);
        for (const pybind11::handle anaObject : anaObjectList){
          analyses.push_back(anaObject.attr("name").cast<str>());
        }
      }
      
    }
  }
  END_BE_NAMESPACE

#endif

BE_INI_FUNCTION
{
  #ifdef HAVE_PYBIND11
    static bool checked_rivet = false;
    if (!checked_rivet)
    {
      // Contur uses the Python loader, not the BOSS AnalysisHandler. In
      // particular on macOS they must share the same installed libRivet;
      // a second build-tree library has an empty analysis registry.
      const auto rivet = pybind11::module::import("rivet");
      const auto names = rivet.attr("AnalysisLoader").attr("analysisNames")();
      if (pybind11::len(names) == 0)
      {
        const auto core_path = rivet.attr("core").attr("__file__").cast<std::string>();
        const auto paths = pybind11::str(rivet.attr("getAnalysisLibPaths")()).cast<std::string>();
        backend_error().raise(LOCAL_INFO,
          "Contur's Python Rivet loader found no analysis plugins. Python extension: "
          + core_path + "; analysis paths: " + paths
          + ". Check the Rivet installation and rebuild the Rivet backend. On macOS, "
            "Python, BOSS and the analysis plugins must use the same installed libRivet, "
            "not a second copy under src/.libs. No events have been analysed by this point.");
      }
      checked_rivet = true;
    }
  #endif
}
END_BE_INI_FUNCTION
