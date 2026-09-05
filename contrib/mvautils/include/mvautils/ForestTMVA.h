/*
  Copyright (C) 2002-2019 CERN for the benefit of the ATLAS collaboration
*/

#ifndef MVAUtils_ForestTMVA_H
#define MVAUtils_ForestTMVA_H

#include "gambit/ColliderBit/mvautils/Forest.h"
#include "TTree.h"
#include <vector>

namespace MVAUtils
{

    /** Implement a Forest with weighted nodes
     * This a general Forest class which implement the strategy used by TMVA
     * in some cases.
     * Each node has a weight that can be used to compute GetTreeResponseWeighted
     * In some cases an offset is needed, which is just the first weight (actually
     * in TMVA all the weights are identical when the offset is used).
     **/
    template<typename Node_t>
    class ForestWeighted : public Forest<Node_t>
    {
    public:
        ForestWeighted() : m_sumWeights(0.) { }

        float GetTreeResponseWeighted(const std::vector<float>& values, unsigned int itree) const
        {
            return Forest<Node_t>::GetTreeResponse(values, itree) * m_weights[itree];
        }

        float GetTreeResponseWeighted(const std::vector<float*>& pointers, unsigned int itree) const
        {
            return Forest<Node_t>::GetTreeResponse(pointers, itree) * m_weights[itree];
        }

        using Forest<Node_t>::GetNTrees;  // lookup is deferred until template paramers are known, force it
        using Forest<Node_t>::newTree;

        float GetWeightedResponse(const std::vector<float>& values) const;
        float GetWeightedResponse(const std::vector<float*>& pointers) const;
        virtual void newTree(const std::vector<Node_t>& nodes, float weight);
        float GetTreeWeight(unsigned int itree) const { return m_weights[itree]; }
        float GetSumWeights() const { return m_sumWeights; }

        virtual float GetOffset() const override { return m_weights[0]; }

        virtual void PrintTree(unsigned int itree) const override {
          std::cout << "weight: " << m_weights[itree] << std::endl;
          Forest<Node_t>::PrintTree(itree);
        }
 
    private:
        std::vector<float> m_weights; //!< boost weights
        float m_sumWeights; //!< the sumOfBoostWeights--no need to recompute each call
    };


    template<typename Node_t>
    float ForestWeighted<Node_t>::GetWeightedResponse(const std::vector<float>& values) const {
        float result = 0.;
        for (unsigned int itree = 0; itree != GetNTrees(); ++itree)
        {
            result += GetTreeResponseWeighted(values, itree);
        }
        return result;
    }

    template<typename Node_t>
    float ForestWeighted<Node_t>::GetWeightedResponse(const std::vector<float*>& pointers) const {
        float result = 0.;
        for (unsigned int itree = 0; itree != GetNTrees(); ++itree)
        {
            result += GetTreeResponseWeighted(pointers, itree);
        }
        return result;
    }

    template<typename Node_t>
    void ForestWeighted<Node_t>::newTree(const std::vector<Node_t>& nodes, float weight) {
        newTree(nodes);
        m_weights.push_back(weight);
        m_sumWeights += weight;
    }

    /*
     * Support TMVA processing
     * 
     * Forest implementing the TMVA forest.
     * 
     * Regression (GetResponse): offset + raw-response
     * Classification (GetClassification): weighted average of the nodes
     * MultiClassification: softmax of the raw-response
     */
    class ForestTMVA final : public ForestWeighted<NodeTMVA>
    {
    public:
        using ForestWeighted<NodeTMVA>::newTree;
        ForestTMVA(TTree* tree);
        ForestTMVA(TMVA::MethodBDT* bdt, bool isRegression, bool useYesNoLeaf);
        void newTree(const TMVA::DecisionTreeNode *node, float weight, bool isRegression, bool useYesNoLeaf);
        virtual TTree* WriteTree(TString name) const override;
        virtual float GetResponse(const std::vector<float>& values) const override ;
        virtual float GetResponse(const std::vector<float*>& pointers) const override;
        virtual float GetClassification(const std::vector<float>& values) const override;
        virtual float GetClassification(const std::vector<float*>& pointers) const override ;
        virtual void PrintForest() const override;
        virtual int GetNVars() const override { return m_max_var + 1; }
    private:
        int m_max_var;
    };

}

#endif
