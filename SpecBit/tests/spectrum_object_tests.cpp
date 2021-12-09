//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Standalone executable to test basic Spectrum
///  and SpectrumContents classes 
///
///  Not built with GAMBIT cmake system. 
///  Compile with 'make -f MakeSpecBitTests' from
///  GAMBIT root directory. May require customisation
///  for your system.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@imperial.ac.uk)
///  \date 2019 June, Oct
///
///  *********************************************

#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/standalone_utils.hpp"
#include "gambit/Utils/static_members.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Elements/spectrum_contents.hpp"
#include "gambit/Elements/slhaea_helpers.hpp"
#include "gambit/SpecBit/SpectrumContents/RegisteredSpectra.hpp"

using namespace Gambit;

int main(int argc, char* argv[])
{
    std::cout<<"Creating MSSM Spectrum Contents object"<<std::endl; 
    SpectrumContents::MSSM mssm_contents; 

    std::cout<<"Creating template SLHAea object corresponding to required spectrum contents: mssm_template.slha"<<std::endl;
    // Create template SLHAea object complying with MSSM contents definition
    // (Won't include stuff the Spectrum objects don't care about, like MODSEL blocks and whatnot)
    SLHAstruct mssm_slha1 = mssm_contents.create_template_SLHAea(1);
    SLHAstruct mssm_slha2 = mssm_contents.create_template_SLHAea(2);

    std::cout<<"Writing SLHAea objecta to file for inspection: mssm_template.slha1(2)"<<std::endl;
    std::ofstream ofs1("mssm_template.slha1");
    std::ofstream ofs2("mssm_template.slha2");
    ofs1 << mssm_slha1;
    ofs2 << mssm_slha2;
    ofs1.close();
    ofs2.close();

    std::cout<<"Creating Spectrum object from template MSSM SLHAea (1) objects and corresponding Contents object"<<std::endl;
    Spectrum mssm_spec1(mssm_slha1,mssm_contents,100); // Last parameter is scale at which running parameters are defined. Could try to infer from certain blocks, but I think better to explictly specify it.
    std::cout<<"Creating Spectrum object from template MSSM SLHAea (2) objects and corresponding Contents object"<<std::endl;
    Spectrum mssm_spec2(mssm_slha2,mssm_contents,100);


    std::cout<<"Writing SLHA-compliant outputs from MSSM Spectrum objects"<<std::endl;
    mssm_spec1.writeSLHAfile("mssm_compliant_template1.slha1", 1);
    mssm_spec1.writeSLHAfile("mssm_compliant_template1.slha2", 2);
    mssm_spec2.writeSLHAfile("mssm_compliant_template2.slha1", 1);
    mssm_spec2.writeSLHAfile("mssm_compliant_template2.slha2", 2);

    // Do the same thing with a couple of test SLHA files from SoftSUSY
    std::cout<<"Reading SoftSUSY-generated SLHA1 spectrum and wrapping it"<<std::endl;
    SLHAstruct ss1;
    std::ifstream ifs1("SpecBit/tests/softsusy_output.slha1");
    ifs1 >> ss1;
    ifs1.close();
    // SLHA1 is missing some stuff that we need, e.g. lepton masses.
    // We could add those automatically with some defaults, but I think
    // it is just better to force people to add this stuff?
    SLHAea_add(ss1,"SMINPUTS",11,5.10998902e-04,"Me(pole)");
    SLHAea_add(ss1,"SMINPUTS",13,1.05658357e-01,"Mmu(pole)");
    // This stuff is less essential, however we need it in order to
    // be able to write out SLHA2 compliant files later on.
    SLHAea_add(ss1,"SMINPUTS",21,4.75000000e-03,"Mdown(2 GeV) MSbar");
    SLHAea_add(ss1,"SMINPUTS",22,2.40000000e-03,"Mup(2 GeV) MSbar");
    SLHAea_add(ss1,"SMINPUTS",23,1.04000000e-01,"Mstrange(2 GeV) MSbar");
    SLHAea_add(ss1,"SMINPUTS",24,1.27000000e+00,"Mcharm(Mcharm) MSbar");

    // Need neutrino masses too, but I think those we can safely add as zero by default.

    // Needs to explicitly add pole mass uncertainties. Input transform does not assume they are zero!
    for(auto p: mssm_contents.all_parameters_with_tag(Par::Pole_Mass))
    {
       for(auto indices: p.allowed_indices())
       {
          std::pair<std::string,std::vector<int>> low = mssm_contents.get_SLHA_indices(Par::Pole_Mass_1srd_low,p.name(),indices);
          int pdgcode = low.second.at(0); // First index should be PDG code, which will be the same for the upper uncertainty  
          SLHAea_add(ss1, "DMASS", pdgcode, 0, 0.0, p.name()+" pole mass lower uncertainty");
          SLHAea_add(ss1, "DMASS", pdgcode, 1, 0.0, p.name()+" pole mass upper uncertainty");
       } 
    }

    double Q = SLHAea_get_scale(ss1,"GAUGE"); // Determine scale of spectrum
    Spectrum mssm_spec(ss1,mssm_contents,Q);
    std::cout<<"Writing SLHA-compliant outputs from MSSM Spectrum object"<<std::endl;
    mssm_spec.writeSLHAfile("mssm_compliant_softsusy1.slha1", 1);
    mssm_spec.writeSLHAfile("mssm_compliant_softsusy1.slha2", 2);

    std::cout<<"Reading SoftSUSY-generated SLHA2 spectrum and wrapping it"<<std::endl;
    SLHAstruct ss2;
    std::ifstream ifs2("SpecBit/tests/softsusy_output.slha2");
    ifs2 >> ss2;
    ifs2.close();

    // Now we have SLHA2 stuff automatically, but still need to add the pole mass uncertainties ourselves
    for(auto p: mssm_contents.all_parameters_with_tag(Par::Pole_Mass))
    {
       for(auto indices: p.allowed_indices())
       {
          std::pair<std::string,std::vector<int>> low = mssm_contents.get_SLHA_indices(Par::Pole_Mass_1srd_low,p.name(),indices);
          int pdgcode = low.second.at(0); // First index should be PDG code, which will be the same for the upper uncertainty  
          SLHAea_add(ss2, "DMASS", pdgcode, 0, 0.0, p.name()+" pole mass lower uncertainty");
          SLHAea_add(ss2, "DMASS", pdgcode, 1, 0.0, p.name()+" pole mass upper uncertainty");
       } 
    }

    Q = SLHAea_get_scale(ss2,"GAUGE"); // Determine scale of spectrum
    mssm_spec = Spectrum(ss2,mssm_contents,Q);
    std::cout<<"Writing SLHA-compliant outputs from MSSM Spectrum object"<<std::endl;
    mssm_spec.writeSLHAfile("mssm_compliant_softsusy2.slha1", 1);
    mssm_spec.writeSLHAfile("mssm_compliant_softsusy2.slha2", 2);

    std::cout<<"Explicity call a few of the getters for good measure..."<<std::endl;
    for(int i=1;i<=3;i++)
    {
       std::cout<<"mssm_spec.get(Par::Pole_Mass,\"e-\","<<i<<"): "<<mssm_spec.get(Par::Pole_Mass,"e-",i)<<std::endl;
       std::cout<<"mssm_spec.get(Par::Pole_Mass,\"e+\","<<i<<"): "<<mssm_spec.get(Par::Pole_Mass,"e+",i)<<std::endl;
    }
    std::cout<<"mssm_spec.get(Par::Pole_Mass,\"e-\"): "<<mssm_spec.get(Par::Pole_Mass,"e-")<<std::endl;
    std::cout<<"mssm_spec.get(Par::Pole_Mass,\"mu-\"): "<<mssm_spec.get(Par::Pole_Mass,"mu-")<<std::endl;
    std::cout<<"mssm_spec.get(Par::Pole_Mass,\"tau-\"): "<<mssm_spec.get(Par::Pole_Mass,"tau-")<<std::endl;
    std::cout<<"mssm_spec.get(Par::Pole_Mass,\"e+\"): "<<mssm_spec.get(Par::Pole_Mass,"e+")<<std::endl;
    std::cout<<"mssm_spec.get(Par::Pole_Mass,\"mu+\"): "<<mssm_spec.get(Par::Pole_Mass,"mu+")<<std::endl;
    std::cout<<"mssm_spec.get(Par::Pole_Mass,\"tau+\"): "<<mssm_spec.get(Par::Pole_Mass,"tau+")<<std::endl;
    std::cout<<"mssm_spec.get(Par::dimensionless,\"sinW2\"): "<<mssm_spec.get(Par::dimensionless,"sinW2")<<std::endl;
 
    std::cout<<"Changing some values and re-getting them..."<<std::endl;
    std::cout<<"mssm_spec.set(666,Par::Pole_Mass,\"e-\")"<<std::endl;
    mssm_spec.set(666,Par::Pole_Mass,"e-");
    std::ofstream ofm("mssm_raw_modified.slha2");
    ofm << mssm_spec.getRawSLHAea();
    ofm.close();

    std::cout<<"mssm_spec.get(Par::Pole_Mass,\"e-\","<<1<<"): "<<mssm_spec.get(Par::Pole_Mass,"e-",1)<<std::endl;
    std::cout<<"mssm_spec.get(Par::Pole_Mass,\"e-\"): "<<mssm_spec.get(Par::Pole_Mass,"e-")<<std::endl;

    std::cout<<"End of tests!"<<std::endl;
}
