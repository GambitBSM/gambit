//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of new MPI datatypes needed by
///  printers.
///
///  NOTE: These have been moved out of Printers,
///  and not all names reflect this yet.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 May
///
///  *********************************************


#ifndef __new_mpi_datatypes_hpp__
#define __new_mpi_datatypes_hpp__

// MPI bindings
#include "gambit/Utils/mpiwrapper.hpp"
#include <ostream>

// Code!
namespace Gambit
{
  namespace Printers 
  {
    /// vertexID / sub-print index pair
    /// Identifies individual buffers (I call them VertexBuffer, but actually there can be more than one per vertex) 
    //typedef std::pair<int,unsigned int> VBIDpair;
    struct VBIDpair {
      int vertexID;
      int index;
      VBIDpair() = default; // Want the trivial default constructor to make this class "POD" so that calls to 'offsetof' are allowed.
      VBIDpair(const int v, const int i)
        : vertexID(v)
        , index(i)
      {}
    };
  
    // Needed by std::map for comparison of keys of type VBIDpair
    bool operator<(const VBIDpair& l, const VBIDpair& r);
    bool operator==(const VBIDpair& l, const VBIDpair& r);
    bool operator!=(const VBIDpair& l, const VBIDpair& r);

    // Same as VBIDpair, but plus the "first_tag" value (association with MPI tag)
    struct VBIDtrip {
      int vertexID;
      int index;
      int first_tag; 
      VBIDtrip() 
        : vertexID(0)
        , index(0)
        , first_tag(0)
      {}
      VBIDtrip(const int v, const int i, const int t)
        : vertexID(v)
        , index(i)
        , first_tag(t)
      {}
      VBIDtrip(const VBIDpair p, const int t)
        : vertexID(p.vertexID)
        , index(p.index)
        , first_tag(t)
      {}
    };
  
    // Needed by std::map for comparison of keys of type VBIDpair
    bool operator<(const VBIDtrip& l, const VBIDtrip& r);
    bool operator==(const VBIDtrip& l, const VBIDtrip& r);
    bool operator!=(const VBIDtrip& l, const VBIDtrip& r);

    /// pointID / process number pair
    /// Used to identify a single parameter space point
    //typedef std::pair<unsigned long int, unsigned int> PPIDpair;
    struct PPIDpair
    {
      unsigned long long int pointID;
      unsigned int rank;
      PPIDpair() 
        : pointID(0)
        , rank(0)
      {}
      PPIDpair(const unsigned long long int p, const int r)
        : pointID(p)
        , rank(r)
      {}
      friend std::ostream& operator<<(std::ostream&, const PPIDpair&);
    };

    // Needed by std::map for comparison of keys of type VBIDpair
    bool operator<(const PPIDpair& l, const PPIDpair& r);
    bool operator==(const PPIDpair& l, const PPIDpair& r);
    bool operator!=(const PPIDpair& l, const PPIDpair& r);

    // To use PPIDpairs in std::unordered_map/set, need to provide hashing and equality functions
    struct PPIDHash{ 
      size_t operator()(const PPIDpair &key) const { 
        return std::hash<long int>()(key.pointID) ^ std::hash<unsigned int>()(key.rank);
      }
    };

    struct PPIDEqual{
      bool operator()(const PPIDpair &lhs, const PPIDpair &rhs) const {
        return lhs == rhs; // use the operator we already defined (why doesn't the STL do this?)
      }
    };

    // stream overloads (for easy std::out)
    // Null pointID object, use for unassigned pointIDs
    const PPIDpair nullpoint;

  } // end namespace Printers

  // DEPRECATED! We no longer actually send this stuff via MPI, 
  // and there were slight issues with non-standards compliance
  // that generate warnings on some compilers, so I am flagging
  // this for deletion, though it was a bit complicated to
  // figure out so I can't bring myself to delete it yet.
  //
  // #ifdef WITH_MPI
  // /// Declarations needed for specialisation of GMPI::get_mpi_data_type<T>::type() to VBIDpair and PPIDpair types
  // namespace GMPI { 
  //    template<> 
  //    struct get_mpi_data_type<Printers::VBIDpair> 
  //    { 
  //      static MPI_Datatype type();
  //    }; 
  //    template<> 
  //    struct get_mpi_data_type<Printers::VBIDtrip> 
  //    { 
  //      static MPI_Datatype type();
  //    }; 
  //    template<> 
  //    struct get_mpi_data_type<Printers::PPIDpair> 
  //    { 
  //      static MPI_Datatype type();
  //    }; 
  // }
  // /// Declare MPI datatype for structs VBIDpair and PPIDpair (which is what the above functions will 'get')
  // extern MPI_Datatype mpi_VBIDpair_type;
  // extern MPI_Datatype mpi_VBIDtrip_type;
  // extern MPI_Datatype mpi_PPIDpair_type;

  // /// Need declaration in order to use these in mpiwrapper.cpp (Init function)
  // namespace Printers {
  //    void queue_mpidefs();
  // }
  //
  // #endif

} // end namespace Gambit


#endif
