#include "gambit/Elements/couplingtable.hpp"
#include "gambit/Utils/util_functions.hpp"

namespace Gambit
{
    bool ComparitorStruct::operator()(const std::vector<std::string>& a, const std::vector<std::string>& b) const
    {
        thread_local std::string full_a, full_b;
        full_a.clear(); full_b.clear();

        for (auto& i : a) 
        {
            full_a += i;
            full_a += '~';
        }
        for (auto& i : b)
        {
            full_b += i;
            full_b += '~';
        }

        return a < b;
    };

    void CouplingTable::init(const Spectrum& spec, const CalcFunc calc)
    {
        spectrum = spec;
        calculator = calc;
    }

    void CouplingTable::update()
    {
        calculator(spectrum, *this);
        needsRecalculating = false;
    }

    void CouplingTable::insert(const std::vector<std::string>& particles, const std::complex<double> coupling)
    {
        auto tmp = particles;
        std::sort(tmp.begin(), tmp.end());
        table[tmp] = coupling;
    }

    std::complex<double> CouplingTable::get(const std::vector<std::string>& particles)
    {
        // make sure it has been updated
        if (needsRecalculating) update();

        auto tmp = particles;
        std::sort(tmp.begin(), tmp.end());
        auto coup = table.find(tmp);

        // if not in table the assume coupling is 0.
        if (coup == table.end()) return {0.,0.};
        // otherwise return the coupling
        else return (*coup).second;
    }

    std::complex<double> CouplingTable::getSafe(const std::vector<std::string>& particles) const
    {
        // make sure it has been updated
        // if (needsRecalculating) update();

        auto tmp = particles;
        std::sort(tmp.begin(), tmp.end());
        auto coup = table.find(tmp);

        // if not in table the assume coupling is 0.
        if (coup == table.end())
        {
          std::cerr << "invalid coupling" << std::endl;
          exit(0);
        }
        // otherwise return the coupling
        else return (*coup).second;
    }

    void CouplingTable::runToScale(const double scale)
    {
        spectrum.RunBothToScale(scale);
        needsRecalculating = true;
    }

  std::map<std::string,double> to_map(const CouplingTable& tbl)
  {
    std::map<std::string,double> result;
    // tbl.update();
    for (const auto& pair : tbl.table)
    {
      std::string name = Utils::join(pair.first,",");
      result[name+"_real"] = pair.second.real();
      result[name+"_imag"] = pair.second.imag();
    }
    return result;
  }

  std::ostream& operator<< (std::ostream &os, const CouplingTable &tbl)
  {
    auto tmp = to_map(tbl);
    for (const auto& pair : tmp)
    {
      os << pair.first << ": " << pair.second << std::endl;
    }
    return os;
  }  

}
