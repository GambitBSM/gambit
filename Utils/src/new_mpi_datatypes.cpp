//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Function definitions for new_mpi_datatypes.hpp
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

#include <sstream>

#include "gambit/Utils/new_mpi_datatypes.hpp"
#include "gambit/Utils/local_info.hpp"
#include "gambit/Utils/export_symbols.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#
// MPI bindings
#include "gambit/Utils/mpiwrapper.hpp"

// Code!
namespace Gambit
{
  namespace Printers {

     // Operators for (e.g. map) key comparisons

     bool operator<(const VBIDpair& l, const VBIDpair& r) {
        return (l.vertexID<r.vertexID || (l.vertexID==r.vertexID && l.index<r.index));
     }
     bool operator==( const VBIDpair& l, const VBIDpair& r) {
         return l.vertexID==r.vertexID && l.index==r.index;
     }
     bool operator!=( const VBIDpair& l, const VBIDpair& r) {
         return !( l == r );
     }

     bool operator<(const VBIDtrip& l, const VBIDtrip& r) {
        return (l.vertexID<r.vertexID || (l.vertexID==r.vertexID && l.index<r.index) || (l.vertexID==r.vertexID && l.index==r.index && l.first_tag<r.first_tag) );
     }
     bool operator==( const VBIDtrip& l, const VBIDtrip& r) {
         return l.vertexID==r.vertexID && l.index==r.index && l.first_tag==r.first_tag;
     }
     bool operator!=( const VBIDtrip& l, const VBIDtrip& r) {
         return !( l == r );
     }

     bool operator<(const PPIDpair& l, const PPIDpair& r) {
         // Raise error if either l or r flagged as invalid
         if(l.valid==0)
         {
             std::ostringstream errmsg;
             errmsg << "Error comparing PPIDpairs; the LHS object is flagged as invalid!";
             utils_error().raise(LOCAL_INFO, errmsg.str()); 
         }
         if(r.valid==0)
         {
             std::ostringstream errmsg;
             errmsg << "Error comparing PPIDpairs; the LHS object is flagged as invalid!";
             utils_error().raise(LOCAL_INFO, errmsg.str()); 
         }
         return (l.pointID<r.pointID || (l.pointID==r.pointID && l.rank<r.rank));
     }
     bool operator==( const PPIDpair& l, const PPIDpair& r) {
         return l.pointID==r.pointID && l.rank==r.rank && l.valid==r.valid;
     }
     bool operator!=( const PPIDpair& l, const PPIDpair& r) {
         return !( l == r );
     }

     #ifdef WITH_MPI
     MPI_Datatype mpi_HDF5bufferchunk_type;

     void define_mpiHDF5bufferchunk()
     {
         static const unsigned int SIZE = HDF5bufferchunk::SIZE;
         static const unsigned int NBUFFERS = HDF5bufferchunk::NBUFFERS;
         static bool defined(false);
         if(not defined)
         {
             int nblocks = 8;
             int blocklengths[8] = {1,1,NBUFFERS,SIZE,SIZE,NBUFFERS*SIZE,NBUFFERS*SIZE,NBUFFERS*SIZE};
             MPI_Datatype types[8];
             types[0] = MPI_UNSIGNED;
             types[1] = MPI_UNSIGNED;
             types[2] = MPI_INT;
             types[3] = MPI_UNSIGNED_LONG_LONG;
             types[4] = MPI_UNSIGNED;
             types[5] = MPI_DOUBLE;
             types[6] = MPI_LONG_LONG;
             types[7] = MPI_INT;
             MPI_Aint offsets[8];
             offsets[0] = offsetof(HDF5bufferchunk, used_size);
             offsets[1] = offsetof(HDF5bufferchunk, used_nbuffers);
             offsets[2] = offsetof(HDF5bufferchunk, name_id);
             offsets[3] = offsetof(HDF5bufferchunk, pointIDs);
             offsets[4] = offsetof(HDF5bufferchunk, ranks);
             offsets[5] = offsetof(HDF5bufferchunk, values);
             offsets[6] = offsetof(HDF5bufferchunk, values_int);
             offsets[7] = offsetof(HDF5bufferchunk, valid);
             MPI_Type_create_struct(nblocks, blocklengths, offsets, types, &mpi_HDF5bufferchunk_type);
             MPI_Type_commit(&mpi_HDF5bufferchunk_type);
             defined=true;
         }
     }
     #endif

     // DEPRECATED! We no longer actually send this stuff via MPI,
     // and there were slight issues with non-standards compliance
     // that generate warnings on some compilers, so I am flagging
     // this for deletion, though it was a bit complicated to
     // figure out so I can't bring myself to delete it yet.
     // #ifdef WITH_MPI
     // MPI_Datatype mpi_VBIDpair_type;
     // MPI_Datatype mpi_VBIDtrip_type;
     // MPI_Datatype mpi_PPIDpair_type;

     // void define_mpiVBIDpair()
     // {
     //    const int nitems=2;
     //    int          blocklengths[2] = {1,1};
     //    MPI_Datatype types[2] = {MPI_INT, MPI_INT};
     //    MPI_Aint     offsets[2];

     //    offsets[0] = offsetof(VBIDpair, vertexID);
     //    offsets[1] = offsetof(VBIDpair, index);

     //    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_VBIDpair_type);
     //    MPI_Type_commit(&mpi_VBIDpair_type);
     // }
     // void define_mpiVBIDtrip()
     // {
     //    const int nitems=3;
     //    int          blocklengths[3] = {1,1,1};
     //    MPI_Datatype types[3] = {MPI_INT, MPI_INT, MPI_INT};
     //    MPI_Aint     offsets[3];

     //    offsets[0] = offsetof(VBIDtrip, vertexID);
     //    offsets[1] = offsetof(VBIDtrip, index);
     //    offsets[2] = offsetof(VBIDtrip, first_tag);

     //    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_VBIDtrip_type);
     //    MPI_Type_commit(&mpi_VBIDtrip_type);
     // }
     // void define_mpiPPIDpair()
     // {
     //    const int nitems=2;
     //    int          blocklengths[2] = {1,1};
     //    MPI_Datatype types[2] = {MPI_LONG, MPI_INT};
     //    MPI_Aint     offsets[2];

     //    offsets[0] = offsetof(PPIDpair, pointID);
     //    offsets[1] = offsetof(PPIDpair, rank);

     //    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_PPIDpair_type);
     //    MPI_Type_commit(&mpi_PPIDpair_type);
     // }

     // /// Queue up these functions to run when MPI initialises
     // void queue_mpidefs()
     // {
     //    GMPI::AddMpiIniFunc prepare_mpiVBIDpair(LOCAL_INFO, "define_mpiVBIDpair", &define_mpiVBIDpair);
     //    GMPI::AddMpiIniFunc prepare_mpiVBIDtrip(LOCAL_INFO, "define_mpiVBIDtrip", &define_mpiVBIDtrip);
     //    GMPI::AddMpiIniFunc prepare_mpiPPIDpair(LOCAL_INFO, "define_mpiPPIDpair", &define_mpiPPIDpair);
     // }
     // #endif

     /// Stream operator overloads
     std::ostream& operator<<(std::ostream& stream, const PPIDpair& ppid)
     {
       stream << "(" << ppid.pointID << ", " << ppid.rank << ")";
       return stream;
     }

     /// Define 'nullpoint' const
     const PPIDpair nullpoint = PPIDpair();

  }

  // /// Definition needed for specialisation of GMPI::get_mpi_data_type<T>() to VBIDpair type
  // /// so that template MPI Send and Receive functions work.
  // //template<> MPI_Datatype GMPI::get_mpi_data_type<Printers::VBIDpair>() { return Printers::mpi_VBIDpair_type; }
  #ifdef WITH_MPI
  // MPI_Datatype GMPI::get_mpi_data_type<Printers::VBIDpair>::type()
  // { return Printers::mpi_VBIDpair_type; }

  // MPI_Datatype GMPI::get_mpi_data_type<Printers::VBIDtrip>::type()
  // { return Printers::mpi_VBIDtrip_type; }

  // MPI_Datatype GMPI::get_mpi_data_type<Printers::PPIDpair>::type()
  // { return Printers::mpi_PPIDpair_type; }

  MPI_Datatype GMPI::get_mpi_data_type<Printers::HDF5bufferchunk>::type()
  { return Printers::mpi_HDF5bufferchunk_type; }
  #endif

} // end namespace Gambit
