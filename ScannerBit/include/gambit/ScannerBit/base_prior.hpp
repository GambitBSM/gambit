//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Abstract base class for a prior
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///      (benjamin.farmer@monash.edu.au)
///  \date 2013 Dec
///
///  \author Gregory Martinez
///      (gregory.david.martinez@gmail.com)
///  \date 2014 Feb
///
///  \author Andrew Fowlie
///    (andrew.j.fowlie@qq.com)
///  \date August 2020
///
///  *********************************************

#ifndef __BASE_PRIORS_HPP__
#define __BASE_PRIORS_HPP__

#include <string>
#include <unordered_map>
#include <vector>


namespace Gambit
{
  namespace Priors
  {
    /**
     * @brief Abstract base class for priors
     */
    class BasePrior
    {
     private:
      unsigned int param_size;

     protected:
      std::vector<std::string> param_names;

     public:
      virtual ~BasePrior() = default;

      BasePrior() : param_size(0), param_names(0) {}

      explicit BasePrior(const int param_size) :
        param_size(param_size), param_names(0) {}

      explicit BasePrior(const std::vector<std::string> &param_names, const int param_size = 0) :
        param_size(param_size), param_names(param_names) {}

      explicit BasePrior(const std::string &param_name, const int param_size = 0) :
        param_size(param_size), param_names(1, param_name) {}

      /** @brief Transform from unit hypercube to parameter */
      virtual void transform(const std::vector<double> &, std::unordered_map<std::string, double> &) const = 0;

      /** @brief Transform from parameter back to unit hypercube */
      virtual std::vector<double> inverse_transform(const std::unordered_map<std::string, double> &) const = 0;

      /** @brief Log of PDF density */
      virtual double operator()(const std::vector<double> &) const
      {
        Scanner::scan_error().raise(LOCAL_INFO, "operator() not implemented");
        return 0.;
      }

      virtual std::vector<std::string> getShownParameters() const { return param_names; }

      inline unsigned int size() const { return param_size; }

      inline void setSize(const unsigned int size) { param_size = size; }

      inline unsigned int & sizeRef() { return param_size; }

      inline std::vector<std::string> getParameters() const { return param_names; }
    };

  }  // namespace Priors
}  // namespace Gambit

#endif  // __BASE_PRIORS_HPP__
