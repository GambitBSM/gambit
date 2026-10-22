/*
  Copyright (C) 2002-2020 CERN for the benefit of the ATLAS collaboration
*/

#ifndef MVAUtils_BDT_H
#define MVAUtils_BDT_H

#include "MVAUtilsDefs.h"
#include "TString.h"
#include <vector>
#include <map>
#include <cassert>
#include <memory>


namespace TMVA {
  class DecisionTreeNode;
  class MethodBDT;
}
class TTree;
namespace MVAUtils
{
  class IForest;

   /** Simplified Boosted Regression Tree, support TMVA, lgbm, and xgboost.
   * Holds a forest (vector of top nodes of each decision tree) and a
   * constant offset or set of weights (not always used).
   *
   * Can be constructed from TMVA::MethodBDT or a TTree. Each entry
   * of the TTree represents a binary tree and each element of the
   * vectors stored in the TTree represent a node.
   *
   * The response can be evaluated from a vector of floats or a vector
   * of pointers (to avoid creating vectors at each call) which can be
   * stored internally (m_pointers)
   **/

  class BDT
  {
  public:
    /** Constructor. The input tree must be created with
     *  convertLGBMToRootTree.py (for lgbm training) or with
     *  convertXGBoostToRootTree.py (for xgboost training) or with
     *  convertXmlToRootTree (for tmva training)
     **/
    explicit BDT(TTree *tree);//ctor TTree
    explicit BDT(TMVA::MethodBDT *bdt, bool isRegression = true, bool useYesNoLeaf = false);//TMVA...
    ~BDT(); //dtor

    /** Number of trees in the whole forest **/
    unsigned int GetNTrees() const ;
    /** Number of variables expected in the inputs **/
    int GetNVars() const ;
    /** Get the offset to the whole forest **/
    float GetOffset() const ;
    /** Get response of the forest, for regression **/
    float GetResponse(const std::vector<float>& values) const;
    float GetResponse(const std::vector<float*>& pointers) const;
    float GetResponse() const;

    /** Get response of the forest, for classification **/
    float GetClassification(const std::vector<float>& values) const;
    float GetClassification(const std::vector<float*>& pointers) const;
    float GetClassification() const;

    // TMVA specific: return 2.0/(1.0+exp(-2.0*sum))-1, with no offset.
    float GetGradBoostMVA(const std::vector<float>& values) const;
    float GetGradBoostMVA(const std::vector<float*>& pointers) const;

    /** Get response of the forest, for multiclassification (e.g. b-tagging) **/
    std::vector<float> GetMultiResponse(const std::vector<float>& values, unsigned int numClasses) const;
    std::vector<float> GetMultiResponse(const std::vector<float*>& pointers, unsigned int numClasses) const;
    std::vector<float> GetMultiResponse(unsigned int numClasses) const;

    /** Return the values corresponding to m_pointers (or an empty vector) **/
    std::vector<float> GetValues() const;
    /** Return stored pointers (which are used by methods with no args) **/
    const std::vector<float*>& GetPointers() const;
    /** Set the stored pointers so that one can use methods with no args */
    void SetPointers(const std::vector<float*>& pointers);

    /** Return a TTree representing the BDT:
    * each entry is a binary tree, each element of the vectors is a node
    **/
    TTree* WriteTree(TString name = "BDT") const;

    /** for debugging, print out tree or forest to stdout */
    void PrintForest() const;
    void PrintTree(unsigned int itree) const;

    /** for debugging, return the response of a sigle tree given the index of its top node **/
    float GetTreeResponse(const std::vector<float>& values, MVAUtils::index_t index) const;
    float GetTreeResponse(const std::vector<float*>& pointers, MVAUtils::index_t index) const;

  private:
    std::unique_ptr<IForest> m_forest;  //!< the implementation of the forest, doing the hard work
    std::vector<float*> m_pointers; //!< where vars to cut on can be set (but can also be passed)
  };


  inline float BDT::GetResponse() const {
    return (m_pointers.size() ? GetResponse(m_pointers) : -9999.);
  }

  inline float BDT::GetClassification() const {
    return (m_pointers.size() ? GetClassification(m_pointers) : -9999.);
  }

  inline std::vector<float> BDT::GetMultiResponse(unsigned int numClasses) const {
    return (m_pointers.size() ? GetMultiResponse(m_pointers, numClasses) : std::vector<float>());
  }

  inline std::vector<float> BDT::GetValues() const {
    std::vector<float> result;
    for (float* ptr : m_pointers)
    {
      assert (ptr);
      result.push_back(*ptr);
    }
    return result;
  }

  inline const std::vector<float*>& BDT::GetPointers() const { return m_pointers; }
  inline void BDT::SetPointers(const std::vector<float*>& pointers) { m_pointers = pointers; }

}

#endif
