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

#ifndef ScalarSingletDM_Z3_TWO_SCALE_MATCHING_H
#define ScalarSingletDM_Z3_TWO_SCALE_MATCHING_H

#include "single_scale_matching.hpp"
#include <functional>

namespace flexiblesusy {

class Model;
class Two_scale;

template <class T> class ScalarSingletDM_Z3;
template <class T> class ScalarSingletDM_Z3_standard_model_matching_up;
template <class T> class ScalarSingletDM_Z3_standard_model_matching_down;

namespace standard_model {
template <class T> class StandardModel;
}

template<>
class ScalarSingletDM_Z3_standard_model_matching_up<Two_scale> : public Single_scale_matching
{
public:
   using Scale_getter = std::function<double()>;

   ScalarSingletDM_Z3_standard_model_matching_up() = default;

   ScalarSingletDM_Z3_standard_model_matching_up(standard_model::StandardModel<Two_scale>*,
                                          ScalarSingletDM_Z3<Two_scale>*,
                                          const Scale_getter&,
                                          int, int);

   virtual ~ScalarSingletDM_Z3_standard_model_matching_up() = default;

   virtual double get_scale() const override;
   virtual void set_models(Model*, Model*) override;
   virtual void match() override;

   int get_higgs_index() const;
   int get_loop_order() const;
   void set_higgs_index(int);
   void set_loop_order(int);
   void set_scale(double);
   void set_scale(const Scale_getter&);
   void set_scale(Scale_getter&&);
   void match_tree_level();

private:
   ScalarSingletDM_Z3<Two_scale>* model{nullptr};
   standard_model::StandardModel<Two_scale>* eft{nullptr};
   Scale_getter scale_getter{};
   double scale{0.};
   int loop_order{0};
   int higgs_idx{0}; ///< Higgs index
};

template<>
class ScalarSingletDM_Z3_standard_model_matching_down<Two_scale> : public Single_scale_matching
{
public:
   using Scale_getter = std::function<double()>;

   ScalarSingletDM_Z3_standard_model_matching_down() = default;

   ScalarSingletDM_Z3_standard_model_matching_down(standard_model::StandardModel<Two_scale>*,
                                            ScalarSingletDM_Z3<Two_scale>*,
                                            const Scale_getter&,
                                            int, int);

   virtual ~ScalarSingletDM_Z3_standard_model_matching_down() = default;

   virtual double get_scale() const override;
   virtual void set_models(Model*, Model*) override;
   virtual void match() override;

   int get_higgs_index() const;
   int get_loop_order() const;
   void set_higgs_index(int);
   void set_loop_order(int);
   void set_scale(double);
   void set_scale(const Scale_getter&);
   void set_scale(Scale_getter&&);
   void match_tree_level();

private:
   ScalarSingletDM_Z3<Two_scale>* model{nullptr};
   standard_model::StandardModel<Two_scale>* eft{nullptr};
   Scale_getter scale_getter{};
   double scale{0.};
   int loop_order{0};
   int higgs_idx{0}; ///< Higgs index
};

} // namespace flexiblesusy

#endif
