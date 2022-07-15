//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Prior object construction routines
///
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2013 Dec
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date Feb 2014
///
///  *********************************************

#ifndef PRIOR_DEFS_HPP
#define PRIOR_DEFS_HPP

#include <cmath>
#include "gambit/ScannerBit/priors.hpp"

   /// Registry of priors
   /// Here we specify mappings from strings to prior objects.
   /// We need this so that strings in the inifile can be used to choose
   /// which prior objects and which combinations of them we want.


   // let us imagine that the user wants to specify something like this in the inifile:
   // log; M0; lower=x; upper=y
   // log; M12; lower=x; upper=y
   // flat; A0; lower=x; upper=y

   // or something worse;
   // log; p1; lower=x; upper=y
   // custom2D; p2,p3; lower1=x2; lower2=x2; upper1=x1; upper2=x2; extrapar=z

   // (where custom2D is a 2D prior over p2 and p3, with some specified ranges,
   // but also an extra parameter which controls some aspect of the prior shape

   // Need to create the appropriate prior objects based on this information.
   // Will have to communicate to the primary parameter object to get the correct
   // ordering of parameters.

   // Lets make some fake structure to hold this information, to be replaced by
   // output of the yaml file parser.
   // Ahh ok I have added a proposal to gambit.yaml for the sort of thing we need.
   // Looks like, for every prior object we want to create, there should be 3 things:
   // prior name (string, identifies factory function to use)
   // parameters list (strings, identifes parameters to associate with this prior)
   // ranges (optional but common; pair of doubles to supply to priors)
   // options (set of key,value pairs for any custom input needed to fancy priors)
   // e.g. an entry in the yaml file might look like this:
   //  custom2D:
   //    parameters: A0, Mstop
   //    options:
   //      lower1: -1000
   //      upper1: 1000
   //      correlation: 0.5

   // We need a factory system of some kind.
   // Factory functions need to be able to pass a variety of arguments to the
   // constructors of the priors, sometimes doubles, but also other prior objects!
   // CHANGE: ok, I think it is safe to treat the "composite" prior class as
   // special, and used only for putting all the individual priors together
   // (if number of sub-priors > 1). This prior is not accessible to the user
   // directly. All user accessible priors can take only the wrapped YAML::Node object
   // as an argument.

   // All priors (except for CompositePrior) take their options as an Options object
   // (which wraps a YAML::Node object). They have to extract the options they need
   // from this structure. The options present there are passed directly from the inifile,

   /// Map in which to keep factory functions for the priors
   // Whenever you add a new prior, you need to add an entry here in order to
   // have it accessible via the inifile (by whatever name you specify here).

namespace Gambit
{
   namespace Priors
   {
        // ------------------1D prior function library------------------------
        // If you add anything here, don't forget to declare it in the header as well!

        // Simple single parameter priors.
        // In all cases input x is a variate from the unit uniform distribution [0,1].

        // 'flat' prior
        // Transforms x to a sample from the uniform interval [a,b].

        struct flatprior
        {
            static double limits(double x) {return x;}
            static double inv(double x) {return x;}
            static double prior (double) {return 0;}
        };

        struct logprior
        {
            static double limits(double x) {return std::log(x);}
            static double inv(double x) {return std::exp(x);}
            static double prior(double x){return -std::log(x);}
        };

        struct sinprior
        {
            static double limits(double x) {return std::cos(x);}
            static double inv(double x) {return std::acos(x);}
            static double prior(double x){return std::log(std::sin(x));}
        };

        struct cosprior
        {
            static double limits(double x) {return std::sin(x);}
            static double inv(double x) {return std::asin(x);}
            static double prior(double x){return std::log(std::cos(x));}
        };

        struct tanprior
        {
            inline static double SQR(double x){return x*x;}
            static double limits(double x) {return 1.0/SQR(std::cos(x));}
            static double inv(double x) {return std::acos(1.0/std::sqrt(x));}
            static double prior(double x){return std::log(std::tan(x));}
        };

        struct cotprior
        {
            inline static double SQR(double x){return x*x;}
            static double limits(double x) {return 1.0/SQR(std::sin(x));}
            static double inv(double x) {return std::asin(1.0/std::sqrt(x));}
            static double prior(double x){return -std::log(std::tan(x));}
        };
        
        struct arccosprior
        {
            inline static double SQR(double x){return x*x;}
            static double limits(double x) {return std::acos(x);}
            static double inv(double x) {return std::cos(x);}
            static double prior(double x) { return 1.0/std::sqrt(1-SQR(x));}
        };

        /// Template class for 1d priors which need only a "range" option in their constructor
        // See factory function map to see how to use this class to quickly create new priors of this kind
        template <class T>
        class RangePrior1D : public BasePrior
        {
        private:
            // Name of the parameter that this prior is supposed to transform
            std::string &myparameter;
            // Ranges for parameters
            double lower;
            double upper;
            double scale;
            double shift;
            double scale_out;
            double shift_out;

        public:

            // Constructor
            RangePrior1D(const std::vector<std::string>& param, const Options& options) : BasePrior(param, 1), myparameter(param_names[0]), scale(1.0), shift(0.0), scale_out(1.0), shift_out(0.0)
            {
                // Read the entries we need from the options
                if ( not options.hasKey("range") )
                {
                    scan_err << "Error! No 'range' keyword found in options supplied for building RangePrior1D prior (i.e. some instance of this, probably 'flat' or 'log')" << scan_end;
                }
                std::pair<double, double> range = options.getValue< std::pair<double, double> >("range");
                if (range.first > range.second)
                {
                    double temp = range.first;
                    range.first = range.second;
                    range.second = temp;
                }

                if (param.size()!=1)
                {
                    scan_err << "Invalid input to some prior derived from RangePrior1D (in constructor): 'myparameters' must be a vector of size 1! (has size=" << param.size() << ")" << scan_end;
                }

                if (options.hasKey("scale"))
                {
                    if (options.getValue<std::string>("scale") == "degrees")
                    {
                        scale = 0.0174532925199;
                    }
                    else
                    {
                        scale = options.getValue<double>("scale");
                    }
                }

                if (options.hasKey("shift"))
                {
                    shift = options.getValue<double>("shift");
                }

                // If the user has specifically set output_scaled_values = false, then remove any scale and shift before outputting.
                if (options.hasKey("output_scaled_values") and not options.getValue<bool>("output_scaled_values"))
                {
                    scale_out = scale;
                    shift_out = shift;
                }

                lower = T::limits(range.first*scale + shift);
                upper = T::limits(range.second*scale + shift);
            }

            // Transformation from unit interval to specified range
            // (need to use vectors to be compatible with BasePrior virtual function)
            void transform(const std::vector<double> &unitpars, std::unordered_map<std::string,double> &output) const override
            {
                output[myparameter] = (T::inv(unitpars[0]*(upper-lower) + lower)-shift_out)/scale_out;
            }

            std::vector<double> inverse_transform(const std::unordered_map<std::string, double> &physical) const override
            {
                const double p = physical.at(myparameter);
                const double x = T::limits(scale_out * p + shift_out);
                const double u = (x - lower) / (upper - lower);
                return {u};
            }

            double operator()(const std::vector<double> &vec) const override {return T::prior(vec[0]*scale+shift)*scale;}
        };

        LOAD_PRIOR(log, RangePrior1D<logprior>)
        LOAD_PRIOR(flat, RangePrior1D<flatprior>)
        LOAD_PRIOR(cos, RangePrior1D<cosprior>)
        LOAD_PRIOR(sin, RangePrior1D<sinprior>)
        LOAD_PRIOR(tan, RangePrior1D<tanprior>)
        LOAD_PRIOR(cot, RangePrior1D<cotprior>)
        LOAD_PRIOR(arccos, RangePrior1D<arccosprior>) 
   }
}

#endif
