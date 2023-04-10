#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/pbarlike_1_0.hpp"


#ifdef HAVE_PYBIND11

    #include "gambit/Utils/begin_ignore_warnings_pybind11.hpp"
    #include <pybind11/pybind11.h>
    #include <pybind11/stl.h>
    #include <pybind11/stl_bind.h>
    #include <pybind11/functional.h>
    #include <pybind11/numpy.h>
    #include "gambit/Utils/end_ignore_warnings.hpp"

    // Backend functions
    BE_NAMESPACE
    {
        std::string static DM_ID ;
        std::string static DMbar_ID ;
        pybind11::list static obj_list;

        pybind11::list c_pbarlike_initialization(const bool& prevent_extrapolation,const std::string& propagation_model,const mat_dbl& propagation_parameters)
        {
            obj_list = pbarlike.attr("DRN_initialization")(propagation_parameters,propagation_model,prevent_extrapolation);
            return obj_list;
        }
                
        map_str_dbl c_pbar_logLikes(double& DM_mass, map_str_dbl& channel_dict, double& sv)
        {   
            pybind11::dict inputs = pybind11::cast(channel_dict);
            pybind11::dict del_chi2 = pbarlike.attr("py_pbar_logLikes")(obj_list,DM_mass,inputs,sv);
            map_str_dbl c_del_chi2 = del_chi2.cast<map_str_dbl>();
            return c_del_chi2;
        }

    }
    END_BE_NAMESPACE
#endif

BE_INI_FUNCTION
{
    #ifdef HAVE_PYBIND11
        static bool scan_level = true;
        if(scan_level)
        {
            const bool prevent_extrapolation = runOptions->getValue<bool>("PreventExtrapolation");
            const std::string propagation_model = runOptions->getValue<std::string>("PropagationModel");
            const mat_dbl propagation_parameters = runOptions->getValue<mat_dbl>("PropagationParameters");
            obj_list = c_pbarlike_initialization(prevent_extrapolation,propagation_model,propagation_parameters);
        }
        scan_level = false;
    #endif
}
END_BE_INI_FUNCTION

