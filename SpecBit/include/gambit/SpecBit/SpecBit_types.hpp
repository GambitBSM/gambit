//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Type definition header for module SpecBit.
///
///  Compile-time registration of type definitions
///  required for the rest of the code to
///  communicate with SpecBit.
///
///  Add to this if you want to define a new type
///  for the functions in SpecBit to return, but
///  you don't expect that type to be needed by
///  any other modules.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2019 July, Dec
///
///  *********************************************


#ifndef __SpecBit_types_hpp__
#define __SpecBit_types_hpp__

#include <string>
#include <vector>
#include "gambit/Utils/util_types.hpp"

namespace Gambit
{

  namespace SpecBit
  {

    // this vector of <int,double> pairs is the type the routine 'ReadLhaBlock' of vevacious uses to read
    // in the passed parameters
    typedef std::vector<std::pair<int,double>> vec_pair_int_dbl;

    // create a spectrum entry type storing all information necessary for the vevacious function 'ReadLhaBlock'
    // => store name, parameters & dimension of an entry
    struct SpectrumEntry
    {
        std::string name;
        vec_pair_int_dbl parameters;
        int dimension;
    };

    // typdef to avoid having to use 'struct SpectrumEntry' every time
    typedef struct SpectrumEntry SpectrumEntry;

    /// map mapping the name of a spectrum entry to the SpectrumEntry type.
    /// In principle one could just use a vector instead of a map. However,
    /// this requires a lot of caution to avoid filling up the vector with
    /// more & more entries with the same name but different parameters
    /// after one point is run so I thought this was the safer option
    typedef std::map<std::string,SpectrumEntry> map_str_SpectrumEntry;


    /// class for setting & storing all spectrum entries of type SpectrumEntry
    /// that need to be passed to vevacious (scale, input filenames & paths as
    /// well as spectrum entries)
    /// passed to vevacious before calling it
    class SpectrumEntriesForVevacious
    {
        public:
            SpectrumEntriesForVevacious(){};

            // setter functions for scale, inputPath and input Filenames
            void set_scale (double inScale) {scale = inScale;};
            void set_inputPath (std::string inPath) {inputPath = inPath;};
            void set_inputFilename (std::string inFile) {inputFilename = inFile;};

            // getter functions for scale, inputPath and input Filenames
            double get_scale () {return scale;};
            std::string get_inputFilename () {return inputFilename;};
            std::string get_inputPath () {return inputPath;};

            // adds an entry to the spec_entry_map
            void add_entry (std::string name, vec_pair_int_dbl vec, int dimension);

            // return spec_entry_map -> iterate through it to pass all entries to vevacious
            map_str_SpectrumEntry get_spec_entry_map() {return spec_entry_map;};

        private:
            double scale;
            std::string inputFilename;
            std::string inputPath;
            map_str_SpectrumEntry spec_entry_map;
    };


    /* Class that stores the results computed by vevacious that will be
    needed by other capabilites in GAMBIT  */
    class VevaciousResultContainer
    {

      public:
        // constructor initialises every member to -1 to avoid
        // problems when printing results when vevacious did not run
        VevaciousResultContainer(){};

        // clear all maps and set value of lifetime and thermalProbability to -1
        void clear_results(const str panic_vaccum, int pathFinder_number);

        // setter functions for results lifetime, thermal probability & bounce action vectors
        // straightPathGoodEnough checks wethere the action of drawing a straigh path between the
        // physical & panic vacuum is already below the action threshold.
        void set_results (str panic_vaccum, str name, double val);
        void add_straightPathGoodEnough(str panic_vacuum);

        // return map containing results for nearest/global run
        map_str_dbl get_nearest_results() {return result_map["nearest"];}
        map_str_dbl get_global_results() {return result_map["global"];}

        // return width, lifetime for nearest/global minimum
        double get_width(str panic_vacuum) { return result_map[panic_vacuum]["width"]; }
        double get_lifetime(str panic_vaccum) {return result_map[panic_vaccum]["lifetime"]; }

        // return thermal probability and width for nearest/global minimum
        double get_thermalProbability(str panic_vaccum) { return result_map[panic_vaccum]["thermalProbability"]; }
        double get_thermalWidth(str panic_vacuum) { return result_map[panic_vacuum]["thermalWidth"]; }

      private:
        map_str_map_str_dbl result_map;
    };
  }
}

#endif // defined __SpecBit_types_hpp__
