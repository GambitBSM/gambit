/*
  Copyright (C) 2002-2019 CERN for the benefit of the ATLAS collaboration
*/

#ifndef MVAUtils_Forest_H
#define MVAUtils_Forest_H

#include "gambit/ColliderBit/mvautils/ForestBase.h"
#include "gambit/ColliderBit/mvautils/NodeImpl.h"
#include <stack>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>


namespace MVAUtils { namespace detail { // helpers

    template<typename T>
    inline T sigmoid(T x) { return 1. / (1. + exp(-x)); }

     /**
      * apply softmax to the input: {exp[xi] / sum(exp[xj]) for xi in x}
      **/
    template<typename Container_t> void applySoftmax(Container_t& x);

    /**
     * Compute the offsets between the nodes to their right children from a 
     * serialized representation of the tree with preoder traversal.
     * Returns 0 for leafs.
     * This function is used in the constructors of the Forest* classes
     **/
    inline std::vector<index_t> computeRight(const std::vector<int>& vars);
 } }

namespace MVAUtils
{
    /**
     * Generic Forest base class. It implements only the non-specific methods.
     * It implement a representation of the forest and basic methods that
     * are common to the other implementations. It does not provide a 
     * contructor since that is specific to derived classes. Concrete classes
     * should derive from this.
     * 
     * The goal of this class is to manage the creation and the computation of the 
     * raw-response of the trees. Derived class should implement how the raw-response
     * of the trees are used to compute the final predictions.
     * Some prediction methods (e.g. GetResponseMulticlass) are implemented here
     * since they are common to the present final concrete classes (TMVA/lgbm)
     **/
    template<typename Node_t>
    class Forest : public IForest
    {
    public:

        virtual float GetTreeResponse(const std::vector<float>& values, unsigned int itree) const override;
        virtual float GetTreeResponse(const std::vector<float*>& pointers, unsigned int itree) const override;

        /** Return the offset of the forest. Since by default there is no offset, return 0 */
        virtual float GetOffset() const override { return 0.; }

        /** Return the response of the whole Forest. Raw is just the sum of all the trees **/
        //  The method is not `final`, but it is very unlikely the derived class
        //  will redefine this (since it is "raw")
        virtual float GetRawResponse(const std::vector<float>& values) const override;
        virtual float GetRawResponse(const std::vector<float*>& pointers) const override;

        /** Compute the prediction for regression **/
        // In this class it is equal to the raw-reponse. Derived class should
        // override this.
        virtual float GetResponse(const std::vector<float>& values) const override;
        virtual float GetResponse(const std::vector<float*>& pointers) const override;

        /** Compute the prediction for multiclassification (a score for each class).
         * In addition to the input values need to pass the number of classes
         **/
        // Since TMVA and lgbm are identical the common implementation is here:
        // Return the softmax of the sub-forest raw-response
        virtual std::vector<float> GetMultiResponse(const std::vector<float>& values,
                                                    unsigned int numClasses) const override;
        virtual std::vector<float> GetMultiResponse(const std::vector<float*>& pointers,
                                                    unsigned int numClasses) const override;

        virtual unsigned int GetNTrees() const final { return m_forest.size(); }

        virtual void PrintForest() const override;

        virtual void PrintTree(unsigned int itree) const override;

        /** Return the vector of nodes for the tree itree **/
        virtual std::vector<Node_t> GetTree(unsigned int itree) const final;

    protected:
        /** Get the response of a tree. Instead of specifying the index of the tree
         * (as in GetTreeResponse) the index of the top node of the tree should be specified
         **/
        float GetTreeResponseFromNode(const std::vector<float>& values, index_t index) const;
        float GetTreeResponseFromNode(const std::vector<float*>& pointers, index_t index) const;

        /** append a new tree (defined by a vector of nodes serialized in preorder) to the forest **/
        void newTree(const std::vector<Node_t>& nodes);

    private:
        std::vector<index_t> m_forest; //!< indices of the top-level nodes of each tree
        std::vector<Node_t> m_nodes; //!< where the nodes of the forest are stored
    };

}

#include "Forest.icc"

#endif
