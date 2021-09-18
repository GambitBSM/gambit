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
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/Contur_2_1_0.hpp"


using namespace pybind11::literals;

BE_NAMESPACE
{

  // Convenience functions
  double Contur_LogLike(vector_shared_ptr<YODA::AnalysisObject> &aos)
  {

    //pybind11::object ao = yoda.attr("AnalysisObject");
    return 0.0;

  }

  Contur_output Contur_LogLike_from_stream(std::shared_ptr<std::ostringstream> yodastream, std::vector<std::string> &contur_yaml_args)
  {
    //Convert C++ ostringstream to python StringIO
    pybind11::str InputString = pybind11::cast(yodastream->str());
    pybind11::object yoda_string_IO = Contur.attr("StringIO")(InputString);
    yoda_string_IO.attr("seek")(pybind11::int_(pybind11::cast(0)));

    //Get default settings for Contur run and add a couple of our own as defaults for GAMBIT
    pybind11::dict args_dict = 
      ((Contur.attr("arg_utils").attr("get_argparser")(pybind11::cast("analysis"))).attr(
        "parse_args")(pybind11::cast(contur_yaml_args))).attr("__dict__");
    args_dict[pybind11::cast("YODASTREAM")] = yoda_string_IO;
    args_dict[pybind11::cast("QUIET")] = pybind11::bool_(true);
    args_dict[pybind11::cast("YODASTREAM_API_OUTPUT_OPTIONS")] = pybind11::list();
    args_dict[pybind11::cast("YODASTREAM_API_OUTPUT_OPTIONS")].attr("append")("LLR");
    args_dict[pybind11::cast("YODASTREAM_API_OUTPUT_OPTIONS")].attr("append")("Pool_LLR");
    args_dict[pybind11::cast("YODASTREAM_API_OUTPUT_OPTIONS")].attr("append")("Pool_tags");

    //This is a temporary fix until Contur has its refloading cache system improved
    Contur.attr("config").attr("refLoaded") = pybind11::bool_(false);

    //Return the contur output.
    //TODO this should be done by reference, no idea why I did it this way originally.
    //Ditto for function below.
    //TODO: In fact, why not unify the repeated code into one function?
    return Contur_output(Contur.attr("run_analysis").attr("main")(args_dict));
  }

  Contur_output Contur_LogLike_from_file(str &YODA_filename, std::vector<std::string>& contur_yaml_args)
  {
    //Get default settings for Contur run and add a couple of our own as defaults for GAMBIT
    pybind11::dict args_dict = 
      ((Contur.attr("arg_utils").attr("get_argparser")(pybind11::cast("analysis"))).attr(
        "parse_args")(pybind11::cast(contur_yaml_args))).attr("__dict__");
    args_dict[pybind11::cast("YODASTREAM")] = YODA_filename;
    args_dict[pybind11::cast("QUIET")] = pybind11::bool_(true);
    args_dict[pybind11::cast("YODASTREAM_API_OUTPUT_OPTIONS")] = pybind11::list();
    args_dict[pybind11::cast("YODASTREAM_API_OUTPUT_OPTIONS")].attr("append")("LLR");
    args_dict[pybind11::cast("YODASTREAM_API_OUTPUT_OPTIONS")].attr("append")("Pool_LLR");
    args_dict[pybind11::cast("YODASTREAM_API_OUTPUT_OPTIONS")].attr("append")("Pool_tags");

    //Run contur, get a LLR and return it
    return Contur_output(Contur.attr("run_analysis").attr("main")(args_dict));
  }


  //Appends all analyses at given beamString (e.g. 13TeV) that contur knows about to the lit of analyses
  //to study.
  void Contur_get_analyses_from_beam(std::vector<std::string> &analyses, std::string &beamString)
  {
    std::vector<std::string> obtained_analyses;
    # pragma omp critical
    {
      obtained_analyses = Contur.attr("static_db").attr("getAnalyses")(pybind11::none(), beamString).cast<std::vector<std::string>>();
    }
    for (std::string analysis : obtained_analyses){
      analyses.push_back(analysis);
    }
  }
}
END_BE_NAMESPACE

BE_INI_FUNCTION
{}
END_BE_INI_FUNCTION
