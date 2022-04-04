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
#include "gambit/Backends/frontends/Contur_2_2_1.hpp"


using namespace pybind11::literals;

BE_NAMESPACE
{

  // Convenience functions
  //TODO: I think this stuff can probably be got rid of now.
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

    //Return the contur output.
    //TODO: In fact, why not unify the repeated code from this and func below into one function?
    return Contur_output(Contur.attr("run_analysis").attr("main")(args_dict));
  }

  //std::vector<Contur_output> Multi_Contur_LogLike_from_stream(std::shared_ptr<std::ostringstream> yodastream, std::vector<std::string> &contur_yaml_args);
  



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

    //From Contur 2.2.0 onwards, need to pass a contur beam object in instead of jusrt a string (as contur now has lep support also)
    //Would be nice to simplify this a bit, but not sure how.

    //First get a legitimate beam
    pybind11::list beams;
    pybind11::object thebeam;
    bool beamfound = false;
    #pragma omp critical
    {
      beams = Contur.attr("static_db").attr("get_beams")();
    }
    for(int i=0; i < pybind11::len(beams); ++i){
      if (beams[i].attr("id")().cast<std::string>() == beamString){
        thebeam = beams[i];
        beamfound = true;
        break;
      }
    }
    if (!beamfound){
      analyses = {};
      //TODO ISSUE WARNING
      return;
    }

    pybind11::list ConturAnalysisObjects;
    # pragma omp critical
    {
      ConturAnalysisObjects=Contur.attr("static_db").attr("get_analyses")(thebeam);
    }
    for (const auto& analysis : ConturAnalysisObjects){
      analyses.push_back(analysis.attr("name").cast<std::string>());
    }
  }
}
END_BE_NAMESPACE

BE_INI_FUNCTION
{}
END_BE_INI_FUNCTION
