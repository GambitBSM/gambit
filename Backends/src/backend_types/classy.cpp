//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of the Classy_input class used for
///  communicating with the backend classy.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2017 Nov
///  \date 2018 May
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 Oct
///  \date 2019 Mar
///  \date 2020 Aug
///
///  \author Sebastian Hoof
///          (hoof@uni-goettingen.de)
///  \date 2020 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Apr
///
///  *********************************************

#include "gambit/Backends/backend_types/classy.hpp"
#include "gambit/Utils/util_functions.hpp"

#include <boost/algorithm/string/predicate.hpp> // case-insensitive string comparison

namespace Gambit
{

  #ifdef HAVE_PYBIND11

    void Classy_input::add_entry(str key, double value) {input_dict[key.c_str()]=std::to_string(value).c_str();}
    void Classy_input::add_entry(str key, int    value) {input_dict[key.c_str()]=std::to_string(value).c_str();}
    void Classy_input::add_entry(str key, str    value) {input_dict[key.c_str()]=value.c_str();}
    void Classy_input::add_entry(str key, std::vector<double>& values)
    {
      // get pointers to arrays holding the information that needs
      // to be passed on to class, convert to uintptr_t (type large enough
      // to store memory address of the used system) and pass to class
      input_dict[key.c_str()] = std::to_string(memaddress_to_uint(&values[0])).c_str();
    }

    bool Classy_input::has_key(str key){return input_dict.contains(key.c_str());}

    /// CLASS specific function to merge python dictionary extra_dict into input_dict
    /// (member of Classy_input). If both dictionaries have the same key it decides
    /// on a case-by-case basis how to deal with that.
    /// Some examples are already implemented, might have to be extended in the future
    /// if more CLASS features are used.
    /// typical example for this would be the key 'output':
    ///    dict input_dict: 'output' : 'tCl nCl' and
    ///    dict extra_dict: 'output' : 'tCl mPk' => mPk has to be added
    ///    => results in    'output' : 'tCl nCl mPk'
    void Classy_input::merge_input_dicts(pybind11::dict extra_dict)
    {
      // Loop through extra_dict (should typically be the shorter one)
      for (auto item : extra_dict)
      {
        pybind11::str key = pybind11::str(item.first);
        pybind11::str arg = pybind11::str(item.second);

        // If item not contained in extra_dict but not in input_dict it
        // will be added to input_dict
        if(!input_dict.attr("__contains__")(key).cast<bool>())
        {
          input_dict[key] = arg;
        }

        // If item contained in both: have to decide on a case-by-case basis what to do!
        
        // 1) If 'output' or 'modes' is defined twice the entries have to be merged
        // e.g. input_dict['output'] = 'A B C'
        //      extra_dict['output'] = 'A B X Y'
        // should result in input_dict['output'] = 'A B C X Y'
        // (python string.find("x") returns -1 if "x" not contained)
        else if(key.attr("find")(pybind11::str("output")).cast<int>()!=-1 ||
          key.attr("find")(pybind11::str("modes")).cast<int>()!=-1)
        {
          // split string of extra_dict['output'] by spaces into list
          // (-> in the example above this would give list = ['A', 'B', 'X', 'Y'])
          pybind11::list list = extra_dict[key].attr("split")();
          // iterate through list and check if current item is also contained in input_dict['output']
          // if it is not it will be added
          for(auto it : list)
          {
            std::string list_entry = std::string(pybind11::str(it));
            // add entry if it is not already in input_dict['output']
            if(input_dict[key].attr("find")(pybind11::str(list_entry)).cast<int>()==-1)
            {
              // add part of extra_dict[key] string that is not contained in input_dict[key] string to input_dict[key]
              std::string new_arg=std::string(pybind11::str(input_dict[key]))+std::string(" ")+std::string(list_entry);
              input_dict[key]= new_arg;
            }
          }
        } 
        // 2) both dictionaries have entry for non-linear treatment
        else if(key.attr("find")(pybind11::str("non linear")).cast<int>()!=-1)
        {
          std::string nonlin_input_dict = (std::string(pybind11::str(input_dict[key])));
          std::string nonlin_extra_dict = (std::string(pybind11::str(extra_dict[key])));

          // throw error if the treatment of non-linearities disagree
          // (need case-insensitive comparison as CLASS accepts 'halofit' and 'HALOFIT' as input)
          if (not boost::iequals(nonlin_input_dict, nonlin_extra_dict))
          {
            std::ostringstream errormsg;
            errormsg << "A problem occurred when trying to compose the input dictionary for CLASS:" << std::endl;
            errormsg << "The included likelihoods requested contradicting treatments for non linearities:" << std::endl;
            errormsg << nonlin_input_dict << " and " << nonlin_extra_dict << std::endl;
            errormsg << "This will lead to inconsistent results, so we are stopping here now." << std::endl;
            backend_error().raise(LOCAL_INFO,errormsg.str());
          }
        }

        // 3) input parameter contained in the string set 'keep_larger_val' is set in both dictionaries,
        // keep the larger value.
        // e.g. input_dict['l_max_scalars'] = '500'
        //      extra_dict['l_max_scalars'] = '2500'
        // should result in input_dict['l_max_scalars'] = '2500'
        else if(keep_larger_val.count(key))
        {

          // cast pybind11::detail::item_accessor to pybind11::str, to c++ string and then to double
          //  (I know... the problem is that the yaml file entries are all parsed as strings so
          //  we don't have to distinguish between the different types of different CLASS input keys.
          //  The python wrapper parses everything as string so it is fine. But here, where we actually
          //  have to compare the passed numbers so we have to cast to double from a python
          //  string be able to tell which entry is the larger one. If you have an idea
          //  to make this nicer --> go for it!! :) )
          float val_input_dict = std::stof(std::string(pybind11::str(input_dict[key])));
          float val_extra_dict = std::stof(std::string(pybind11::str(extra_dict[key])));

          // if val_extra_dict is higher than the entry in the input_dict, replace it
          if (val_input_dict < val_extra_dict){input_dict[key] = extra_dict[key];}
          // if not 'input_dict'already contains the higher value and there is nothing to do here.
        }

        // 4) same as above, but for parameters for which we want to keep the smaller value
        else if(keep_smaller_val.count(key))
        {
          // cast pybind string to double
          float val_input_dict = std::stof(std::string(pybind11::str(input_dict[key])));
          float val_extra_dict = std::stof(std::string(pybind11::str(extra_dict[key])));
            
          // if val_extra_dict is smaller than the entry in the input_dict, replace it
          if (val_input_dict > val_extra_dict){input_dict[key] = extra_dict[key];}
          // if not 'input_dict' already contains the smaller value and there is nothing to do here.
        }

        // Throw an error if a key appears in both dictionaries that
        // should be merged, but no rule for this key is implemented.
        else
        {
          std::ostringstream errormsg;
          errormsg << "A problem occurred when trying to compose the input dictionary for CLASS:"<<std::endl;
          errormsg << "The entry '" << std::string(key) << "' was passed to the dictionary twice."<<std::endl;
          errormsg << "This can occur when: "<<std::endl;
          errormsg << "  1) You are either trying to overwrite a model parameter. If that is the case,"<<std::endl;
          errormsg << "     you should implement an extra function to set the CLASS input parameters for your model."<<std::endl;
          errormsg << "  2) Different (MontePython) likelihoods both set a value for one precision parameter."<<std::endl;
          errormsg << "     At the moment, GAMBIT does not how to handle this for this parameter. If you want to keep"<<std::endl;
          errormsg << "     the larger (smaller) value add the entry to the string set 'keep_larger_val'"<<std::endl;
          errormsg << "     ('keep_smaller_val') defined in Backends/backend_types/classy.hpp"<<std::endl;
          errormsg << "     If you need a more involved rule for that parameter, implement it in"<<std::endl;
          errormsg << "     'Classy_input::merge_input_dicts'"<<std::endl;
          backend_error().raise(LOCAL_INFO,errormsg.str());
        }
      }
    }

    // clears all entries from input_dict
    void Classy_input::clear(){input_dict.attr("clear")();}

    // return input_dict
    pybind11::dict Classy_input::get_input_dict(){return input_dict;}

  #endif

}
