//   GUM: GAMBIT Universal Model Machine
//   ************************************
///  \file
///
///  Contains all routines for interface
///  between C++ and Mathematica packages
///
///  **********************************
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2018, 2019
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
//   \date 2019 July
///
///  ***********************************


#include <iostream>

#include "options.hpp"
#include "feynrules.hpp"
#include "sarah.hpp"

int main(int argc, char** argv)
{
    
    // Initialise options for input.
    std::vector<Particle> partlist;
    std::vector<Parameter> paramlist;
    std::map<std::string, bool> flags;
    std::vector<std::string> backends;
    std::map<std::string, std::string> mixings;
    std::map<std::string, std::string> bcs;
    std::vector<Parameter> sphenodeps;
    Error error;

    // Attempt to parse the user's command line input...
    try
    {
        Options options = parse(argc, argv);
        Outputs outputs;
            
        // Pick FeynRules or SARAH, then crack on.
        if (options.package() == "feynrules")
        {
            #ifndef HAVE_FEYNRULES
            std::cerr << "\n ERROR: GUM can't find FeynRules... please try rebuilding.\n\n";
            return 0;
            #endif
            
            GUM::all_feynrules(options, partlist, paramlist, outputs, backends, error);
        }
        else if (options.package() == "sarah")
        {
        
            #ifndef HAVE_SARAH
            std::cerr << "\n ERROR: GUM can't find SARAH... please try rebuilding.\n\n";
            return 0;
            #endif
        
            GUM::all_sarah(options, partlist, paramlist, outputs, backends, flags, mixings, bcs, sphenodeps, error);
        }
    }
    catch(const char* e)
    {
        std::cerr << e << std::endl << std::endl;
        usage(argv[0]);
        return 0;
    }

    std::cout << "C++ to Mathematica interface finished." << std::endl;
        
    return 0;
}
