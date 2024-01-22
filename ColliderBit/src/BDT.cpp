#include "gambit/cmake/cmake_variables.hpp"
#ifndef EXCLUDE_ROOT

#include "gambit/ColliderBit/BDT.h"
#include "gambit/ColliderBit/mvautils/NodeImpl.h"
#include "gambit/ColliderBit/mvautils/ForestLGBM.h"
#include "gambit/ColliderBit/mvautils/ForestXGBoost.h"
#include "gambit/ColliderBit/mvautils/ForestTMVA.h"

#include "TMVA/MethodBDT.h"
#include "TMVA/DecisionTree.h"

#include "TTree.h"
#include <stack>
#include <string>
#include <sstream>
#include <set>
#include <memory>
#include <stdexcept>

using namespace MVAUtils;


void NodeTMVA::Print(index_t index) const
{
  std::cout << "     Variable: " << int(m_var) << ", Cut: " << m_cut
            << " (index = " << index << ")" << std::endl;
}


void NodeLGBMSimple::Print(index_t index) const
{
  std::cout << "     Variable: " << int(m_var) << ", Cut: " << m_cut
            << " (index = " << index << ")" << std::endl;
}


void NodeLGBM::Print(index_t index) const
{
  std::cout << "     Variable: " << int(m_var) << ", Cut: " << m_cut << ", DefaultLeft: " << (int)m_default_left
            << " (index = " << index << ")" << std::endl;
}

void NodeXGBoost::Print(index_t index) const
{
  std::cout << "     Variable: " << int(m_var) << ", Cut: " << m_cut << ", DefaultLeft: " << (int)m_default_left
            << " (index = " << index << ")" << std::endl;
}


namespace{
 
/*  utility functions : to split option (e.g. "creator=lgbm;node=lgbm_simple")
 *  in a std::map {{"creator", "lgbm"}, {"node", "lgbm_simple"}}
 */

std::string get_default_string_map(const std::map <std::string, std::string> & m,
                                   const std::string& key, const std::string & defval="")
{
   std::map<std::string, std::string>::const_iterator it = m.find(key);
   if (it == m.end()) { return defval; }
   else { return it->second; }
}

std::map<std::string, std::string> parseOptions(std::string raw_options)
{
  std::stringstream ss(raw_options);
  std::map<std::string, std::string> options;
  std::string item;
  while (std::getline(ss, item, ';')) {
    auto pos = item.find_first_of('=');
    const auto right = item.substr(pos+1);
    const auto left = item.substr(0, pos);
    if (!options.insert(std::make_pair(left, right)).second)
    {
      throw std::runtime_error(std::string("option ") + left + " duplicated in title of TTree used as input");
    }
  }

  return options;
}


}


/** c-tor from TTree **/
BDT::BDT(::TTree *tree)
{
  // at runtime decide which flavour of BDT we need to build
  // the information is coming from the title of the TTree
  std::map<std::string, std::string> options = parseOptions(tree->GetTitle());
  std::string creator = get_default_string_map(options, std::string("creator"));
  if (creator == "lgbm")
  {
    std::string node_type = get_default_string_map (options, std::string("node_type"));
    if (node_type == "lgbm") {
      m_forest = std::make_unique<ForestLGBM>(tree);
    }
    else if (node_type == "lgbm_simple") {
      m_forest = std::make_unique<ForestLGBMSimple>(tree);  // this do not support nan as inputs
    }
    else
    {
      throw std::runtime_error("the title of the input tree is misformatted: cannot understand which BDT implementation to use");
    }
  }
  else if (creator == "xgboost")
  {
    //this do support nan as inputs
    m_forest = std::make_unique<ForestXGBoost>(tree);
  }
  else {
    // default for compatibility: old TTree (based on TMVA) don't have a special title
    m_forest = std::make_unique<ForestTMVA>(tree);
  }
}

BDT::~BDT(){}

unsigned int BDT::GetNTrees() const { return m_forest->GetNTrees(); }
int BDT::GetNVars() const { return m_forest->GetNVars(); }
float BDT::GetOffset() const { return m_forest->GetOffset(); }


/** c-tor from TMVA::MethodBDT **/
BDT::BDT(TMVA::MethodBDT* bdt, bool isRegression, bool useYesNoLeaf)
{
  if (!bdt) { throw std::runtime_error("bdt pointer to BDT contructor is null"); }
  m_forest = std::make_unique<ForestTMVA>(bdt, isRegression, useYesNoLeaf);
}


/** Return offset + the sum of the response of each tree  **/
float BDT::GetResponse(const std::vector<float>& values) const
{
  return m_forest->GetResponse(values);
}


/** Return offset + the sum of the response of each tree  **/
float BDT::GetResponse(const std::vector<float*>& pointers) const
{
  return m_forest->GetResponse(pointers);
}


float BDT::GetClassification(const std::vector<float>& values) const
{
  return m_forest->GetClassification(values);
}


float BDT::GetClassification(const std::vector<float*>& pointers) const
{
  return m_forest->GetClassification(pointers);
}

float BDT::GetGradBoostMVA(const std::vector<float>& values) const
{
  const float sum = m_forest->GetRawResponse(values);  // ignores the offset
  return 2. / (1 + exp(-2 * sum)) - 1;  //output shaping for gradient boosted decision tree (-1,1)
}

float BDT::GetGradBoostMVA(const std::vector<float*>& pointers) const
{
  const float sum = m_forest->GetRawResponse(pointers);  // ignores the offset
  return 2. / (1 + exp(-2 * sum)) - 1;  //output shaping for gradient boosted decision tree (-1,1)
}


std::vector<float> BDT::GetMultiResponse(const std::vector<float>& values,
                                         unsigned int numClasses) const
{
  return m_forest->GetMultiResponse(values, numClasses);
}


std::vector<float> BDT::GetMultiResponse(const std::vector<float*>& pointers,
                                         unsigned int numClasses) const
{
  return m_forest->GetMultiResponse(pointers, numClasses);
}


float BDT::GetTreeResponse(const std::vector<float>& values, MVAUtils::index_t index) const
{
  return m_forest->GetTreeResponse(values, index);
}


float BDT::GetTreeResponse(const std::vector<float*>& pointers, MVAUtils::index_t index) const
{
  return m_forest->GetTreeResponse(pointers, index);
}

TTree* BDT::WriteTree(TString name) const { return m_forest->WriteTree(name); }

void BDT::PrintForest() const { m_forest->PrintForest(); }
void BDT::PrintTree(unsigned int itree) const { m_forest->PrintTree(itree); }

ForestLGBMSimple::ForestLGBMSimple(TTree* tree) : ForestLGBMBase<NodeLGBMSimple>()
{
    m_max_var = 0;

    // variables read from the TTree
    std::vector<int> *vars = nullptr;
    std::vector<float> *values = nullptr;

    std::vector<NodeLGBMSimple> nodes;

    tree->SetBranchAddress("vars", &vars);
    tree->SetBranchAddress("values", &values);

    for (int i = 0; i < tree->GetEntries(); ++i)
    {
        // each entry in the TTree is a decision tree
        tree->GetEntry(i);
        if (!vars) { throw std::runtime_error("vars pointer is null in ForestLGBMSimple constructor"); }
        if (!values) { throw std::runtime_error("values pointers is null in ForestLGBMSimple constructor"); }
        if (vars->size() != values->size()) { throw std::runtime_error("inconsistent size for vars and values in ForestLGBMSimple constructor"); }

        nodes.clear();

        std::vector<MVAUtils::index_t> right = detail::computeRight(*vars);

        for (size_t i = 0; i < vars->size(); ++i) {
            nodes.emplace_back(vars->at(i), values->at(i), right[i]);
            if (vars->at(i) > m_max_var) { m_max_var = vars->at(i); }
        }
        newTree(nodes);
    }  // end loop on TTree, all decision tree loaded
    delete vars;
    delete values;
}


TTree* ForestLGBMSimple::WriteTree(TString name) const
{
    TTree *tree = new TTree(name.Data(), "creator=lgbm;node_type=lgbm_simple");

    std::vector<int> vars;
    std::vector<float> values;

    tree->Branch("vars", &vars);
    tree->Branch("values", &values);

    for (size_t itree = 0; itree < GetNTrees(); ++itree) {
        vars.clear();
        values.clear();
        for(const auto& node : GetTree(itree)) {
            vars.push_back(node.GetVar());
            values.push_back(node.GetVal());
        }
        tree->Fill();
    }
    return tree;
}

void ForestLGBMSimple::PrintForest() const
{
    std::cout << "***BDT LGBMSimple: Printing entire forest***" << std::endl;
    Forest::PrintForest();
}


ForestLGBM::ForestLGBM(TTree* tree) : ForestLGBMBase<NodeLGBM>()
{
    m_max_var = 0;

    // variables read from the TTree
    std::vector<int> *vars = nullptr;
    std::vector<float> *values = nullptr;
    std::vector<bool> *default_left = nullptr;

    std::vector<NodeLGBM> nodes;

    tree->SetBranchAddress("vars", &vars);
    tree->SetBranchAddress("values", &values);
    tree->SetBranchAddress("default_left", &default_left);

    for (int i = 0; i < tree->GetEntries(); ++i)
    {
        // each entry in the TTree is a decision tree
        tree->GetEntry(i);
        if (!vars) { throw std::runtime_error("vars pointer is null in ForestLGBM constructor"); }
        if (!values) { throw std::runtime_error("values pointers is null in ForestLGBM constructor"); }
        if (!default_left) { throw std::runtime_error("default_left pointers is null in ForestLGBM constructor"
); }
        if (vars->size() != values->size()) { throw std::runtime_error("inconsistent size for vars and values in ForestLGBM constructor"); }
        if (default_left->size() != values->size()) { throw std::runtime_error("inconsistent size for default_left and values in ForestLGBM constructor"); }

        nodes.clear();

        std::vector<MVAUtils::index_t> right = detail::computeRight(*vars);

        for (size_t i = 0; i < vars->size(); ++i) {
            nodes.emplace_back(vars->at(i), values->at(i), right[i], default_left->at(i));
            if (vars->at(i) > m_max_var) { m_max_var = vars->at(i); }
        }
        newTree(nodes);
    }  // end loop on TTree, all decision tree loaded
    delete vars;
    delete values;
    delete default_left;
}


TTree* ForestLGBM::WriteTree(TString name) const
{
    TTree *tree = new TTree(name.Data(), "creator=lgbm;node_type=lgbm");

    std::vector<int> vars;
    std::vector<float> values;
    std::vector<bool> default_left;

    tree->Branch("vars", &vars);
    tree->Branch("values", &values);
    tree->Branch("default_left", &default_left);

    for (size_t itree = 0; itree < GetNTrees(); ++itree) {
        vars.clear();
        values.clear();
        default_left.clear();
        for(const auto& node : GetTree(itree)) {
            vars.push_back(node.GetVar());
            values.push_back(node.GetVal());
            default_left.push_back(node.GetDefaultLeft());
        }
        tree->Fill();
    }
    return tree;
}

void ForestLGBM::PrintForest() const
{
    std::cout << "***BDT LGBM: Printing entire forest***" << std::endl;
    Forest::PrintForest();
}

ForestTMVA::ForestTMVA(TTree* tree) : ForestWeighted<NodeTMVA>()
{
    m_max_var = 0;

    // variables read from the TTree
    std::vector<int> *vars = nullptr;
    std::vector<float> *values = nullptr;
    float offset;  // the offset is the weight

    std::vector<NodeTMVA> nodes;

    tree->SetBranchAddress("vars", &vars);
    tree->SetBranchAddress("values", &values);
    tree->SetBranchAddress("offset", &offset);

    for (int i = 0; i < tree->GetEntries(); ++i)
    {
        // each entry in the TTree is a decision tree
        tree->GetEntry(i);
        if (!vars) { throw std::runtime_error("vars pointer is null in ForestTMVA constructor"); }
        if (!values) { throw std::runtime_error("values pointers is null in ForestTMVA constructor"); }
        if (vars->size() != values->size()) { throw std::runtime_error("inconsistent size for vars and values in ForestTMVA constructor"); }

        nodes.clear();

        std::vector<MVAUtils::index_t> right = detail::computeRight(*vars);

        for (size_t i = 0; i < vars->size(); ++i) {
            nodes.emplace_back(vars->at(i), values->at(i), right[i]);
            if (vars->at(i) > m_max_var) { m_max_var = vars->at(i); }
        }
        newTree(nodes, offset);
    }  // end loop on TTree, all decision tree loaded
    delete vars;
    delete values;
}

ForestTMVA::ForestTMVA(TMVA::MethodBDT* bdt, bool isRegression, bool useYesNoLeaf)
{
    m_max_var = 0;
    std::vector<TMVA::DecisionTree*>::const_iterator it;
    for(it = bdt->GetForest().begin(); it != bdt->GetForest().end(); ++it) {
        uint index = it - bdt->GetForest().begin();
        float weight = 0.;
        if(bdt->GetBoostWeights().size() > index) {
            weight = bdt->GetBoostWeights()[index];
        }

        newTree((*it)->GetRoot(), weight, isRegression, useYesNoLeaf);
    }
}

/**
 * Creates the full tree structure from TMVA::DecisionTree node.
 **/
void ForestTMVA::newTree(const TMVA::DecisionTreeNode *node, float weight, bool isRegression, bool useYesNoLeaf
)
{
    // index is relative to the current node
    std::vector<MVAUtils::index_t> right;
    {
        // not strictly parent if doing a right node
        std::stack<const TMVA::DecisionTreeNode *> parent;
        std::stack<MVAUtils::index_t> parentIndex;

        parentIndex.push(-1);
        parent.push(nullptr);

        auto currNode = node;
        int i = -1;
        while (currNode) {
            ++i;
            right.push_back(-1);
            if (!currNode->GetLeft()) {
                // a leaf
                auto currParent = parent.top();
                auto currParentIndex = parentIndex.top();
                // if right has not been visited, next will be right
                if (currParentIndex >= 0) {
                    right[currParentIndex] = i + 1 - currParentIndex;
                    currNode = currParent->GetCutType() ? currParent->GetLeft() : currParent->GetRight();
                } else {
                    currNode = nullptr;
                }
                parent.pop();
                parentIndex.pop();
            } else {
                // not a leaf
                parent.push(currNode);
                parentIndex.push(i);
                currNode = currNode->GetCutType() ? currNode->GetRight() : currNode->GetLeft();
            }
        }
    }
    {
        std::stack<const TMVA::DecisionTreeNode *> parent; // not strictly parent if doing a right node

        parent.push(nullptr);

        auto currNode = node;
        int i = -1;
        std::vector<NodeTMVA> nodes;
        while (currNode) {
            ++i;
            if (!currNode->GetLeft()) {
                // a leaf
                nodes.emplace_back(-1,
                            isRegression ?
                            currNode->GetResponse() : useYesNoLeaf ? currNode->GetNodeType() : currNode->GetPurity(),
                            right[i]);
                auto currParent = parent.top();
                // if right has not been visited, next will be right
                if (currParent) {
                    currNode = currParent->GetCutType() ? currParent->GetLeft() : currParent->GetRight();
                } else {
                    currNode = nullptr;
                }
                parent.pop();
            } else {
                // not a leaf
                parent.push(currNode);

                if (currNode->GetSelector() > m_max_var) { m_max_var = currNode->GetSelector(); }

                nodes.emplace_back(currNode->GetSelector(), currNode->GetCutValue(), right[i]);

                currNode = currNode->GetCutType() ? currNode->GetRight() : currNode->GetLeft();
            }
        }
        newTree(nodes, weight);
    }
}

TTree* ForestTMVA::WriteTree(TString name) const
{
    TTree *tree = new TTree(name.Data(), "creator=TMVA");

    std::vector<int> vars;
    std::vector<float> values;
    float offset;

    tree->Branch("offset", &offset);
    tree->Branch("vars", &vars);
    tree->Branch("values", &values);

    for (size_t itree = 0; itree < GetNTrees(); ++itree) {
        vars.clear();
        values.clear();
        for(const auto& node : GetTree(itree)) {
            vars.push_back(node.GetVar());
            values.push_back(node.GetVal());
        }
        offset = GetTreeWeight(itree);
        tree->Fill();
    }
    return tree;
}

float ForestTMVA::GetResponse(const std::vector<float>& values) const {
    return GetRawResponse(values) + GetOffset();
}

float ForestTMVA::GetResponse(const std::vector<float*>& pointers) const {
    return GetRawResponse(pointers) + GetOffset();
}

float ForestTMVA::GetClassification(const std::vector<float>& values) const
{
    float result = GetWeightedResponse(values);
    return result / GetSumWeights();
}

float ForestTMVA::GetClassification(const std::vector<float*>& pointers) const
{
    float result = GetWeightedResponse(pointers);
    return result / GetSumWeights();
}

void ForestTMVA::PrintForest() const
{
    std::cout << "***BDT TMVA: Printing entire forest***" << std::endl;
    Forest::PrintForest();
}

ForestXGBoost::ForestXGBoost(TTree* tree) : ForestXGBoostBase<NodeXGBoost>()
{
    m_max_var = 0;

    // variables read from the TTree
    std::vector<int> *vars = nullptr;
    std::vector<float> *values = nullptr;
    std::vector<bool> *default_left = nullptr;

    std::vector<NodeXGBoost> nodes;

    tree->SetBranchAddress("vars", &vars);
    tree->SetBranchAddress("values", &values);
    tree->SetBranchAddress("default_left", &default_left);

    for (int i = 0; i < tree->GetEntries(); ++i)
    {
        // each entry in the TTree is a decision tree
        tree->GetEntry(i);
        if (!vars) { throw std::runtime_error("vars pointer is null in ForestXGBoost constructor"); }
        if (!values) { throw std::runtime_error("values pointers is null in ForestXGBoost constructor"); }
        if (!default_left) { throw std::runtime_error("default_left pointers is null in ForestXGBoost constructor"); }
        if (vars->size() != values->size()) { throw std::runtime_error("inconsistent size for vars and values in ForestXGBoost constructor"); }
        if (default_left->size() != values->size()) { throw std::runtime_error("inconsistent size for default_left and values in ForestXGBoost constructor"); }

        nodes.clear();

        std::vector<MVAUtils::index_t> right = detail::computeRight(*vars);

        for (size_t i = 0; i < vars->size(); ++i) {
            nodes.emplace_back(vars->at(i), values->at(i), right[i], default_left->at(i));
            if (vars->at(i) > m_max_var) { m_max_var = vars->at(i); }
        }
        newTree(nodes);
    }  // end loop on TTree, all decision tree loaded
    delete vars;
    delete values;
    delete default_left;
}


TTree* ForestXGBoost::WriteTree(TString name) const
{
    TTree *tree = new TTree(name.Data(), "creator=xgboost");

    std::vector<int> vars;
    std::vector<float> values;
    std::vector<bool> default_left;

    tree->Branch("vars", &vars);
    tree->Branch("values", &values);
    tree->Branch("default_left", &default_left);

    for (size_t itree = 0; itree < GetNTrees(); ++itree) {
        vars.clear();
        values.clear();
        default_left.clear();
        for(const auto& node : GetTree(itree)) {
            vars.push_back(node.GetVar());
            values.push_back(node.GetVal());
            default_left.push_back(node.GetDefaultLeft());
        }
        tree->Fill();
    }
    return tree;
}

void ForestXGBoost::PrintForest() const
{
    std::cout << "***BDT XGBoost: Printing entire forest***" << std::endl;
    Forest::PrintForest();
}

#endif
