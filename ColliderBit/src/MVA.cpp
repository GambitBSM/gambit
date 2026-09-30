#include "gambit/cmake/cmake_variables.hpp"
#ifndef EXCLUDE_ROOT

#include "gambit/ColliderBit/MVA.h"

std::string FindFile(const std::string& filename) {
    // Check if file exists in the current working directory
    std::ifstream file(filename.c_str());
    if (!file.good()) {
        throw std::runtime_error("File not found: " + filename);
    }

    // Get the absolute path
    char absolutePath[PATH_MAX];
    if (realpath(filename.c_str(), absolutePath) == NULL) {
        throw std::runtime_error("Error obtaining the absolute path for: " + filename);
    }

    return std::string(absolutePath);
}

TMVAReader::TMVAReader(const std::string &name,
                       const std::vector<std::string> &variableDefs,
                       const std::string fname1, const std::string fname2)
    : MVA(name, variableDefs) {

  // This loads the library
  TMVA::Tools::Instance();

  // Initialize reader(s)
  m_bdt1 = new TMVA::Reader("!Color:Silent");
  if (fname2 != "")
    m_bdt2 = new TMVA::Reader("!Color:Silent");
  else
    m_bdt2 = 0;

  m_variables.resize(variableDefs.size(), 0);

  int idx = 0;
  for (auto label : variableDefs) {
    std::string var = label + " := " + label;
    m_bdt1->AddVariable(var, &m_variables[idx]);
    if (m_bdt2)
      m_bdt2->AddVariable(var, &m_variables[idx]);
    idx++;
  }

  m_bdt1->BookMVA(name, FindFile(fname1));
  if (m_bdt2)
    m_bdt2->BookMVA(name, FindFile(fname2));
}

double TMVAReader::evaluate(const std::vector<double> &values,
                            const std::string /* nodeName */) {
  TMVA::Reader *bdt = m_bdt1;
  if (m_bdt2 && ((m_eventNumber % 2) == 1))
    bdt = m_bdt2;

  if (values.size() != m_variables.size())
    throw std::runtime_error("Wrong number of variables into TMVAReader");
  for (size_t ii = 0; ii < values.size(); ii++)
    m_variables[ii] = values[ii];
  return bdt->EvaluateMVA(m_name);
}

MVAUtilsReader::MVAUtilsReader(const std::string &name,
                               const std::string fname1,
                               const std::string fname2)
    : MVA(name, {}) {
  TFile *f1 = TFile::Open(FindFile(fname1).c_str(), "READ");
  TTree *tree1 = nullptr;
  f1->GetObject(name.c_str(), tree1);
  if (tree1 == nullptr)
    throw std::runtime_error("Did not find MVA tree");
  m_bdt1 = new MVAUtils::BDT(tree1);
  m_bdt2 = nullptr;
  if (fname2 != "") {
    TFile *f2 = TFile::Open(FindFile(fname2).c_str(), "READ");
    TTree *tree2 = nullptr;
    f2->GetObject(name.c_str(), tree2);
    if (tree2 == nullptr)
      throw std::runtime_error("Did not find MVA tree");
    m_bdt2 = new MVAUtils::BDT(tree2);
  }
}

double MVAUtilsReader::evaluate(const std::vector<double> &values,
                                const std::string /* nodeName */) {
  MVAUtils::BDT *bdt = m_bdt1;
  if (m_bdt2 && ((m_eventNumber % 2) == 1))
    bdt = m_bdt2;
  std::vector<float> floatValues(values.begin(), values.end());

  return bdt->GetResponse(floatValues);
}

std::vector<double>
MVAUtilsReader::evaluateMulti(const std::vector<double> &values,
                              int numClasses) {
  MVAUtils::BDT *bdt = m_bdt1;
  if (m_bdt2 && ((m_eventNumber % 2) == 1))
    bdt = m_bdt2;

  std::vector<float> floatValues(values.begin(), values.end());
  auto results = bdt->GetMultiResponse(floatValues, numClasses);

  std::vector<double> doubleResult(results.begin(), results.end());
  return doubleResult;
}
#endif
