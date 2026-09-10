/*
  Copyright (C) 2002-2020 CERN for the benefit of the ATLAS collaboration
*/

#ifndef MVAUtils_ForestXGBOOST_H
#define MVAUtils_ForestXGBOOST_H

#include "gambit/ColliderBit/mvautils/Forest.h"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>


namespace MVAUtils
{
    /*
     * Support XGBoost processing of the forest response.
     *
     * User should use ForestXGBoost (for nan input support)
     *
     * Implement only the classification as: sigmoid(raw-reponse)
     * Other methods are from Forest:
     * Regression (GetResponse) as raw-response. 
     * Global bias 'base_score' is not included [default=0.5] 
     * */
    template<typename Node_t>
    class ForestXGBoostBase : public Forest<Node_t>
    {
    public:
        using Forest<Node_t>::GetResponse;

        virtual float GetClassification(const std::vector<float>& values) const final
        {
            return detail::sigmoid(GetResponse(values));
        }
        virtual float GetClassification(const std::vector<float*>& pointers) const final
        {
            return detail::sigmoid(GetResponse(pointers));
        }
    };

    /** Implement XGBoost with nan support **/
    class ForestXGBoost final : public ForestXGBoostBase<NodeXGBoost>
    {
    public:
        ForestXGBoost(TTree* tree);
        virtual TTree* WriteTree(TString name) const override;
        virtual void PrintForest() const override;
        virtual int GetNVars() const override { return m_max_var + 1; }
    private:
        int m_max_var;
    };
}

#endif
