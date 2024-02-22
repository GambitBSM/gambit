/*
  Copyright (C) 2002-2020 CERN for the benefit of the ATLAS collaboration
*/

#ifndef MVAUtils_NodeImpl_H
#define MVAUtils_NodeImpl_H

#include "gambit/ColliderBit/mvautils/MVAUtilsDefs.h"
#include <vector>
#include <cstdint>
#include <cmath>

namespace TMVA{
  class MethodBDT;
  class DecisionTreeNode;
}

namespace MVAUtils
{

  // classes do not inherit from a common note. Different Node classes
  // are used as template argument for Forest classes. Forest classes will
  // hold vector of Nodes, so it is important to avoid overhead when calling
  // Node methods -> no polymoriphis

  // The main differences between Node classes is the logic to get the next
  // node, depending on the input values

  /**
   * Node for TMVA implementation
   *
   * This follows the implementation in TMVA.
   * next = value >= cut ? left : right
   **/
  class NodeTMVA
  {
  public:
    /** The constructor gets the index of the variable to cut on (-1 if leaf),
        the index of the right child (value not used if a leaf), and the value to
        cut on (if not leaf) or the respons (if leaf).
    */
    NodeTMVA(const int ivar, const float val, const index_t right):
      m_cut(val), m_right(right), m_var(ivar) { }

    /** For debugging only: print the node values */
    void Print(index_t index) const;

    /** Based on the value of the variable that's passed in,
        return the index of the appropriate child. Assumes the node is not a leaf
        (i.e., there is no check). Must also pass the current node index.
    */
    index_t GetNext(const float value, index_t index) const;

    bool IsLeaf() const { return m_var < 0; } //!< is the current node a leaf node

    /** The variable index to cut on (or -1 if leaf, but use IsLeaf instead if checking for leaf) */
    var_t GetVar() const { return m_var; }

    /** The value to cut on (if not leaf), or the response (if leaf). */
    float GetVal() const { return m_cut; }

    /** For debugging: returns the index of the left node; is passed the current node index.
     */
    index_t GetLeft(index_t index) const { return index + 1; }

    /** For debugging: returns the index of the right node; is passed the current node index.
     */
    index_t GetRight(index_t index) const { return index + m_right; }

  private:
    // the order is important to have the optimal memory usage
    float m_cut; //!< cut value for internal nodes or response for leaf nodes
    int16_t m_right; //!< right relative index (to be added to current) (left is always current + 1)
    var_t m_var; //!< index of the variable to cut for internal nodes, -1 for leaf nodes
  };

  // inline speedup ~15%
  inline index_t NodeTMVA::GetNext(const float value, index_t index) const {
    return (value >= m_cut) ? GetLeft(index) : GetRight(index);
  }


  /**
   * Node for LGBM without nan implementation
   *
   * This follow the implementation in LGBM
   * next = value <= cut ? left : right
   *
   * Does not support nan or categorical inputs.
   **/
  class NodeLGBMSimple
  {
  public:
    NodeLGBMSimple(const int ivar, const float val, const index_t right)
    : m_cut(val), m_right(right), m_var(ivar) { }
    void Print(index_t index) const;
    index_t GetNext(const float value, index_t index) const;
    bool IsLeaf() const { return m_var < 0; } //!< is the current node a leaf node

    /** The variable index to cut on (or -1 if leaf, but use IsLeaf instead if checking for leaf) */
    var_t GetVar() const { return m_var; }

    /** The value to cut on (if not leaf), or the response (if leaf). */
    float GetVal() const { return m_cut; }

    /** For debugging: returns the index of the left node; is passed the current node index.
     */
    index_t GetLeft(index_t index) const { return index + 1; }

    /** For debugging: returns the index of the right node; is passed the current node index.
     */
    index_t GetRight(index_t index) const { return index + m_right; }

  private:
    float m_cut; //!< cut value for internal nodes or response for leaf nodes
    int16_t m_right; //!< right relative index (to be added to current) (left is always current + 1)
    var_t m_var; //!< index of the variable to cut for internal nodes, -1 for leaf nodes
  };

  inline index_t NodeLGBMSimple::GetNext(const float value, index_t index) const {
    // note that this is different from TMVA (and not the opposite, e.g. cannot simply invert left/right)
    return (value <= m_cut) ? GetLeft(index) : GetRight(index);
  }

  /**
   * Node for LGBM with nan implementation
   *
   * This follow the implementation in LGBM
   * next = value != nan ? (value <= cut ? left : right) : (default_left ? left : right)
   *
   * default_left is stored for each node (can be different)
   * Does not support categorical inputs.
   **/
  class NodeLGBM
  {
  public:
    NodeLGBM(const int ivar, const float val, const index_t right, const int8_t default_left)
    : m_cut(val), m_right(right), m_var(ivar), m_default_left(default_left) { }
    void Print(index_t index) const;
    index_t GetNext(const float value, index_t index) const;
    bool GetDefaultLeft() const { return m_default_left; }
    bool IsLeaf() const { return m_var < 0; } //!< is the current node a leaf node

    var_t GetVar() const { return m_var; }
    float GetVal() const { return m_cut; }
    index_t GetLeft(index_t index) const { return index + 1; }
    index_t GetRight(index_t index) const { return index + m_right; }

  private:
    float m_cut; //!< cut value for internal nodes or response for leaf nodes
    int16_t m_right; //!< right relative index (to be added to current) (left is always current + 1)
    var_t m_var; //!< index of the variable to cut for internal nodes, -1 for leaf nodes
    int8_t m_default_left;  //< if to go left in case of nan input
  };


  inline index_t NodeLGBM::GetNext(const float value, index_t index) const {
    if (not std::isnan(value)) {
      return (value <= m_cut) ? GetLeft(index) : GetRight(index);
    }
    else {
      return (m_default_left) ? GetLeft(index) : GetRight(index);
    }
  }

  /**
   * Node for XGBoost with nan implementation
   *
   * This follow the implementation in XGBoost
   * next = value != nan ? (value < cut ? left : right) : (default_left ? left : right)
   * left are assigned to be "YES"
   * right are assigned to be "NO" in XGBoost
   * default_left is stored for each node (can be different)
   * Does not support categorical inputs.
   **/
  class NodeXGBoost
  {
  public:
    NodeXGBoost(const int ivar, const float val, const index_t right, const int8_t default_left)
    : m_cut(val), m_right(right), m_var(ivar), m_default_left(default_left) { }
    void Print(index_t index) const;
    index_t GetNext(const float value, index_t index) const;
    bool GetDefaultLeft() const { return m_default_left; }
    bool IsLeaf() const { return m_var < 0; } //!< is the current node a leaf node

    var_t GetVar() const { return m_var; }
    float GetVal() const { return m_cut; }
    index_t GetLeft(index_t index) const { return index + 1; }
    index_t GetRight(index_t index) const { return index + m_right; }

  private:
    float m_cut; // cut value for internal nodes or response for leaf nodes
    int16_t m_right; // right relative index (to be added to current) (left is always current + 1)
    var_t m_var; // index of the variable to cut for internal nodes, -1 for leaf nodes
    int8_t m_default_left;  //default if to go left in case of nan input
  };


  inline index_t NodeXGBoost::GetNext(const float value, index_t index) const {
    if (not std::isnan(value)) {
      return (value < m_cut) ? GetLeft(index) : GetRight(index);
    }
    else {
      return (m_default_left) ? GetLeft(index) : GetRight(index);
    }
  }

}
#endif
