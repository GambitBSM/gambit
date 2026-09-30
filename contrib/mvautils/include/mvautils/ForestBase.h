/*
  Copyright (C) 2002-2019 CERN for the benefit of the ATLAS collaboration
*/

#ifndef MVAUtils_ForestBase_H
#define MVAUtils_ForestBase_H

#include <vector>

class TTree;
class TString;

namespace MVAUtils
{
    /** Compute the response from the binary trees in the forest
     *
     * Concrete classes should store the trees of the forest with their nodes
     * and be able to compute the response, depending on the implementation.
     * Concrete classes should be constructable from TTree.
     **/

    class IForest
    {
    public:
      virtual ~IForest () noexcept = default;

        /** Return the response of one tree
         *  Must pass the features in a std::vector<float> values
         *  and the index of the tree.
         **/
        virtual float GetTreeResponse(const std::vector<float>& values, unsigned int itree) const = 0;
        virtual float GetTreeResponse(const std::vector<float*>& pointers, unsigned int itree) const = 0;
        /** Return the global offset. For many implementation this is just 0 **/
        virtual float GetOffset() const = 0;
        /** Return the response of the whole Forest. Raw is just the sum of all the trees **/
        virtual float GetRawResponse(const std::vector<float>& values) const = 0;
        virtual float GetRawResponse(const std::vector<float*>& pointers) const = 0;
        /** Compute the prediction of a classification **/
        virtual float GetClassification(const std::vector<float>& values) const = 0;
        virtual float GetClassification(const std::vector<float*>& pointers) const = 0;
        /** Compute the prediction for regression **/
        virtual float GetResponse(const std::vector<float>& values) const = 0;
        virtual float GetResponse(const std::vector<float*>& pointers) const = 0;
        /** Compute the prediction for multiclassification (a score for each class).
         * In addition to the input values need to pass the number of classes
         **/
        virtual std::vector<float> GetMultiResponse(const std::vector<float>& values,
                                                    unsigned int numClasses) const = 0;
        virtual std::vector<float>  GetMultiResponse(const std::vector<float*>& pointers,
                                                     unsigned int numClasses) const = 0;
        virtual unsigned int GetNTrees() const = 0;
        virtual void PrintForest() const = 0;
        virtual void PrintTree(unsigned int itree) const = 0;
        /** Return a TTree representing the BDT. The called is the owner of the returned TTree **/
        virtual TTree* WriteTree(TString) const = 0;
        /** Get the number of input variable to be passed with std::vector to Get* methods **/
        virtual int GetNVars() const = 0;
    };

}
#endif
