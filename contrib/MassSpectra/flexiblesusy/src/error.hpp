// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

#ifndef ERROR_H
#define ERROR_H

#include <string>

namespace flexiblesusy {

class Error {
public:
   virtual ~Error() = default;
   virtual std::string what() const = 0;
};

class FatalError : public Error {
public:
   virtual ~FatalError() = default;
   virtual std::string what() const override { return "Fatal error."; };
};

/**
 * @class SetupError
 * @brief Spectrum generator was not setup correctly
 */
class SetupError : public Error {
public:
   explicit SetupError(const std::string& message_) : message(message_) {}
   virtual ~SetupError() = default;
   virtual std::string what() const override { return message; }
private:
   std::string message;
};

/**
 * @class NoConvergenceError
 * @brief No convergence while solving the RGEs
 */
class NoConvergenceError : public Error {
public:
   explicit NoConvergenceError(int number_of_iterations_, const std::string& msg = "")
      : message(msg), number_of_iterations(number_of_iterations_) {}
   virtual ~NoConvergenceError() = default;
   virtual std::string what() const override {
      if (!message.empty())
         return message;

      return "NoConvergenceError: no convergence after "
         + std::to_string(number_of_iterations) + " iterations";
   }
   int get_number_of_iterations() const { return number_of_iterations; }
private:
   std::string message;
   int number_of_iterations;
};

/**
 * @class NoSinThetaWConvergenceError
 * @brief No convergence while calculating the sinThetaW parameter
 */
class NoSinThetaWConvergenceError : public Error {
public:
   NoSinThetaWConvergenceError(int number_of_iterations_,
                               double sin_theta_)
      : number_of_iterations(number_of_iterations_)
      , sin_theta(sin_theta_)
      {}
   virtual ~NoSinThetaWConvergenceError() = default;
   virtual std::string what() const override {
      return "NoSinThetaWConvergenceError: no convergence after "
         + std::to_string(number_of_iterations) + " iterations (sin(theta)="
         + std::to_string(sin_theta) + ")";
   }
   int get_number_of_iterations() const { return number_of_iterations; }
   double get_sin_theta() const { return sin_theta; }
private:
   int number_of_iterations;
   double sin_theta;
};

/**
 * @class NonPerturbativeSinThetaW
 * @brief Calculation of sin(theta) became non-perturbative
 */
class NonPerturbativeSinThetaW : public Error {
public:
   NonPerturbativeSinThetaW() {}
   virtual ~NonPerturbativeSinThetaW() = default;
   virtual std::string what() const override {
      return "NonPerturbativeSinThetaW: sin(theta) non-perturbative";
   }
};

/**
 * @class NonPerturbativeRunningError
 * @brief Non-perturbative RG running
 */
class NonPerturbativeRunningError : public Error {
public:
   /**
    * Constructor.
    *
    * @param scale_ target renormalization scale
    * @param parameter_index_ index of parameter that becomes non-perturbative
    * @param value_ parameter value at scale_
    *
    * The parameter index can be set to -1 (default) to indicate that
    * something is wrong with the target renormalization scale.
    */
   explicit NonPerturbativeRunningError(double scale_, int parameter_index_ = -1, double value_ = 0)
      : scale(scale_)
      , value(value_)
      , parameter_index(parameter_index_)
      {}
   virtual ~NonPerturbativeRunningError() = default;
   virtual std::string what() const override {
      if (parameter_index == -1)
         return "NonPerturbativeRunningError: scale Q = " + std::to_string(value);

      return "NonPerturbativeRunningError: non-perturbative running of parameter "
         + std::to_string(parameter_index) + " to scale " + std::to_string(scale);
   }
   std::string what(const std::string& parameter_name) const {
      return "NonPerturbativeRunningError: non-perturbative running"
         " of " + parameter_name + " = " + std::to_string(value)
         + " to scale " + std::to_string(scale);
   }
   int get_parameter_index() const { return parameter_index; }
   double get_parameter_value() const { return value; }
   double get_scale() const { return scale; }
private:
   double scale; ///< renormalization scale
   double value; ///< value of parameter that becomes non-perturbative
   int parameter_index; ///< index of parameter that becomes non-perturbative
};

class NonPerturbativeRunningQedQcdError : public Error {
public:
   explicit NonPerturbativeRunningQedQcdError(const std::string& msg_)
      : msg(msg_)
      {}
   virtual ~NonPerturbativeRunningQedQcdError() = default;
   virtual std::string what() const override { return msg; }
private:
   std::string msg;
};

/**
 * @class OutOfMemoryError
 * @brief Not enough memory
 */
class OutOfMemoryError : public Error {
public:
   explicit OutOfMemoryError(const std::string& msg_)
      : msg(msg_)
      {}
   virtual ~OutOfMemoryError() = default;
   virtual std::string what() const override {
      return std::string("OutOfMemoryError: Not enought memory: ") + msg;
   }
private:
   std::string msg;
};

/**
 * @class OutOfBoundsError
 * @brief Out of bounds access
 */
class OutOfBoundsError : public Error {
public:
   OutOfBoundsError(const std::string& msg_)
      : msg(msg_)
      {}
   virtual ~OutOfBoundsError() = default;
   virtual std::string what() const override { return msg; }
private:
   std::string msg;
};

class ReadError : public Error {
public:
   explicit ReadError(const std::string& message_) : message(message_) {}
   virtual ~ReadError() = default;
   virtual std::string what() const override { return message; }
private:
   std::string message;
};

/**
 * @class PhysicalError
 * @brief Exception class to be used in the FlexibleSUSY model file
 */
class PhysicalError : public Error {
public:
   explicit PhysicalError(const std::string& message_) : message(message_) {}
   virtual ~PhysicalError() = default;
   virtual std::string what() const override { return message; }
private:
   std::string message;
};

class HimalayaError : public Error {
public:
   explicit HimalayaError(const std::string& message_) : message(message_) {}
   virtual ~HimalayaError() = default;
   virtual std::string what() const override { return message; }
private:
   std::string message;
};

} // namespace flexiblesusy

#endif
