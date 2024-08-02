
#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Elements/sminputs.hpp"

namespace Gambit
{

void add_Yukawas(const int type, const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP);

void generic_to_generic(const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP);

void physical_to_generic(const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP);

void higgs_to_generic(const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP);

void hybrid_lam1_to_generic(const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP);

void hybrid_lam2_to_generic(const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP);

void hybrid_higgs_to_generic(bool tree, const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP);

void hybrid_higgs2_to_generic(const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP);

} // namespace Gambit
