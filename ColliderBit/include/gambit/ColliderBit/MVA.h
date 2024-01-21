#ifndef MVA_H
#define MVA_H

#include "TRandom3.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <limits.h>
#include <unistd.h>

#include "TMVA/MethodCuts.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"

#include "mvautils/BDT.h"
#include "TMVA/BDT.h"
#include "TFile.h"
#include "TTree.h"

class MVA {
public:
  MVA(const std::string &name, const std::vector<std::string> variableDefs = {}
      // specifies the order of variables in the input vector
      )
      : m_name(name), m_variableDefs(variableDefs){};

  void setEventNumber(int eventNumber) { m_eventNumber = eventNumber; };
  virtual double evaluate(const std::vector<double> &values,
                          const std::string nodeName = "") = 0;
  virtual std::vector<double>
  evaluateMulti(const std::vector<double> & /*values */, int /* numClasses */) {
    throw std::runtime_error("multi output not supported for this type of MVA");
  };
  virtual std::vector<float>
  evaluateMulti(const std::vector<float> & /*values */, int /* numClasses */) {
    throw std::runtime_error("multi output not supported for this type of MVA");
  };

protected:
  std::string m_name;
  std::vector<std::string> m_variableDefs;
  int m_eventNumber;
};

class TMVAReader : public MVA {
public:
  TMVAReader(const std::string &name,
             const std::vector<std::string> &variableDefs,
             const std::string fname1, const std::string fname2 = "");
  virtual double evaluate(const std::vector<double> &values,
                          const std::string nodeName = "");
  ~TMVAReader() {
    delete m_bdt1;
    delete m_bdt2;
  };

private:
  TMVA::Reader *m_bdt1; // for even eventnumber sample
  TMVA::Reader *m_bdt2; // for odd  eventnumber sample
  std::vector<Float_t> m_variables;
};

class MVAUtilsReader : public MVA {
public:
  MVAUtilsReader(const std::string &name, const std::string fname1,
                 const std::string fname2 = "");
  virtual double evaluate(const std::vector<double> &values,
                          const std::string nodeName = "");
  virtual std::vector<double> evaluateMulti(const std::vector<double> &values,
                                            int numClasses);
  // to avoid warnings about hidden virtual functions
  virtual std::vector<float>
  evaluateMulti(const std::vector<float> & /*values */, int /* numClasses */) {
    throw std::runtime_error(
        "multi output with floats not supported for this type of MVA");
  };

  ~MVAUtilsReader() {
    delete m_bdt1;
    delete m_bdt2;
  };

private:
  MVAUtils::BDT *m_bdt1;
  MVAUtils::BDT *m_bdt2;
};

/*
class BDTAnalysis : public MVA {
    
    private:
      std::map<std::string, MVA *> m_MVAs;
  
    public:
      void addMVABDT(const std::string &name, const std::string &fname1, const std::string &fname2) {
        if (m_MVAs.find(name) != m_MVAs.end())
            throw std::runtime_error("Duplicate MVA name");
        m_MVAs[name] = new MVAUtilsReader(name, fname1, fname2);
        // Assuming MVAUtilsReader returns a pointer to MVA
      }

    };
*/

#endif
