//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple C++ wrapper for the MPI C bindings.
///  It is by no means comprehensive, and is just
///  intended to simplify some MPI commands within
///  Gambit.
///
///  Extend as needed.
///
///  Note: Some C++ bindings already exist, but
///  it appears that they are deprecated in really
///  new versions of the MPI standard, and don't
///  offer functionality over the C bindings
///  anyway. I have nevertheless mirrored the names
///  of some of the deprecated C++ bindings, in
///  case it helps some people who were used to
///  them.
///
///  There is also boost/mpi, but it is a compiled
///  library and we have been avoiding those.
///
///  You can remove the error handlers if you want
///  these wrappers to be independent of GAMBIT.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Apr
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jun
///
///  *********************************************

// The WITH_MPI macro determines whether MPI is used or not.
// It is defined at compile time by cmake with -DWITH_MPI.
// The contents of this file are ignored if MPI is disabled.

#ifdef WITH_MPI
#ifndef __mpiwrapper_hpp__
#define __mpiwrapper_hpp__

#include <sstream>
#include <iostream>
#include <type_traits>
#include <chrono>

#include "gambit/Utils/begin_ignore_warnings_mpi.hpp"
#include <mpi.h>
#include "gambit/Utils/end_ignore_warnings.hpp"


#include <boost/utility/enable_if.hpp>

#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/local_info.hpp"
#include "gambit/Utils/util_macros.hpp"

// I wanted to keep the GAMBIT logger separate from this code so that it
// would be more streamlined for using elsewhere. But the logger is very
// useful for debugging, so this preprocessor flag can be used to turn
// it on and off
// Though it might already be included via the error handlers anyway.
#define USE_GAMBIT_LOGGER

#ifdef USE_GAMBIT_LOGGER
  #include "gambit/Logs/logger.hpp"
  #define LOGGER logger() << LogTags::utils << LogTags::info
#else
  #define LOGGER std::cerr
  #define EOM std::endl
#endif


/// Provide template specialisation of get_mpi_data_type only if the requested type hasn't been used to define one already.
#define SPECIALISE_MPI_DATA_TYPE_IF_NEEDED(TYPEDEFD_TYPE, RETURN_MPI_TYPE)                                                   \
      template<typename T>                                                                                                   \
      struct get_mpi_data_type<T, typename boost::enable_if_c< std::is_same<T, TYPEDEFD_TYPE>::value                      && \
                                                               !std::is_same<char, TYPEDEFD_TYPE>::value                  && \
                                                               !std::is_same<short, TYPEDEFD_TYPE>::value                 && \
                                                               !std::is_same<int, TYPEDEFD_TYPE>::value                   && \
                                                               !std::is_same<long, TYPEDEFD_TYPE>::value                  && \
                                                               !std::is_same<long long, TYPEDEFD_TYPE>::value             && \
                                                               !std::is_same<unsigned char, TYPEDEFD_TYPE>::value         && \
                                                               !std::is_same<unsigned short, TYPEDEFD_TYPE>::value        && \
                                                               !std::is_same<unsigned int, TYPEDEFD_TYPE>::value          && \
                                                               !std::is_same<unsigned long, TYPEDEFD_TYPE>::value         && \
                                                               !std::is_same<unsigned long long, TYPEDEFD_TYPE>::value    && \
                                                               !std::is_same<float, TYPEDEFD_TYPE>::value                 && \
                                                               !std::is_same<double, TYPEDEFD_TYPE>::value                && \
                                                               !std::is_same<long double, TYPEDEFD_TYPE>::value           && \
                                                               !std::is_same<bool, TYPEDEFD_TYPE>::value>::type >            \
      {                                                                                                                      \
         static MPI_Datatype type() { return RETURN_MPI_TYPE; }                                                              \
      };                                                                                                                     \

/// Trigger debugging output when messages sent/recvd
//#define MPI_MSG_DEBUG

namespace Gambit
{

   namespace GMPI
   {

      /// Mapping from (basic) C++ types to MPI datatypes
      /// Based on of "get_hdf5_data_type" in hdf5tools.hpp
      /// Base template is left undefined in order to raise
      /// a compile error if specialisation doesn't exist.
      template<typename T, typename Enable=void>
      struct get_mpi_data_type;

      /// Overload to work with arrays
      template<typename T, size_t SIZE>
      struct get_mpi_data_type<T[SIZE]> { static MPI_Datatype type() { return get_mpi_data_type<T>::type(); } };

      /// True types
      /// @{
      template<> struct get_mpi_data_type<char>              { static MPI_Datatype type() { return MPI_CHAR;               } };
      template<> struct get_mpi_data_type<short>             { static MPI_Datatype type() { return MPI_SHORT;              } };
      template<> struct get_mpi_data_type<int>               { static MPI_Datatype type() { return MPI_INT;                } };
      template<> struct get_mpi_data_type<long>              { static MPI_Datatype type() { return MPI_LONG;               } };
      template<> struct get_mpi_data_type<long long>         { static MPI_Datatype type() { return MPI_LONG_LONG;          } };
      template<> struct get_mpi_data_type<unsigned char>     { static MPI_Datatype type() { return MPI_UNSIGNED_CHAR;      } };
      template<> struct get_mpi_data_type<unsigned short>    { static MPI_Datatype type() { return MPI_UNSIGNED_SHORT;     } };
      template<> struct get_mpi_data_type<unsigned int>      { static MPI_Datatype type() { return MPI_UNSIGNED;           } };
      template<> struct get_mpi_data_type<unsigned long>     { static MPI_Datatype type() { return MPI_UNSIGNED_LONG;      } };
      template<> struct get_mpi_data_type<unsigned long long>{ static MPI_Datatype type() { return MPI_UNSIGNED_LONG_LONG; } };
      template<> struct get_mpi_data_type<float>             { static MPI_Datatype type() { return MPI_FLOAT;              } };
      template<> struct get_mpi_data_type<double>            { static MPI_Datatype type() { return MPI_DOUBLE;             } };
      template<> struct get_mpi_data_type<long double>       { static MPI_Datatype type() { return MPI_LONG_DOUBLE;        } };
      /// @}

      /// Typedef'd types; enabled only where they differ from the true types, and where the relevant constants have been
      /// defined in the linked MPI implementation.
      /// @{
      #ifdef MPI_INT8_T
        SPECIALISE_MPI_DATA_TYPE_IF_NEEDED(int8_t,   MPI_INT8_T  )
      #endif
      #ifdef MPI_UINT8_T
        SPECIALISE_MPI_DATA_TYPE_IF_NEEDED(uint8_t,  MPI_UINT8_T )
      #endif
      #ifdef MPI_INT16_T
        SPECIALISE_MPI_DATA_TYPE_IF_NEEDED(int16_t,  MPI_INT16_T )
      #endif
      #ifdef MPI_UINT16_T
        SPECIALISE_MPI_DATA_TYPE_IF_NEEDED(uint16_t, MPI_UINT16_T)
      #endif
      #ifdef MPI_INT32_T
        SPECIALISE_MPI_DATA_TYPE_IF_NEEDED(int32_t,  MPI_INT32_T )
      #endif
      #ifdef MPI_UINT32_T
        SPECIALISE_MPI_DATA_TYPE_IF_NEEDED(uint32_t, MPI_UINT32_T)
      #endif
      #ifdef MPI_INT64_T
        SPECIALISE_MPI_DATA_TYPE_IF_NEEDED(int64_t,  MPI_INT64_T )
      #endif
      #ifdef MPI_UINT64_T
        SPECIALISE_MPI_DATA_TYPE_IF_NEEDED(uint64_t, MPI_UINT64_T)
      #endif
      /// @}

      /// Main "Communicator" class
      class EXPORT_SYMBOLS Comm
      {
         public:
            /// Default Constructor; attaches to MPI_COMM_WORLD
            Comm();

            /// Constructor which copies existing communicator into boundcomm
            Comm(const MPI_Comm& comm, const std::string& name);

            /// Constructor which creates a communicator gruop from WORLD containing
            /// only the specified processes
            Comm(std::vector<int> processes, const std::string& name);

            /// Destructor
            ~Comm();

            /// Create a new communicator group for the specified processes
            Comm spawn_new(const std::vector<int>& processes, const std::string& name);

            /// As name
            void check_for_undelivered_messages();

            /// Duplicate existing communicator
            /// (NOTE, this is a collective operation on all procceses)
            void dup(const MPI_Comm& comm, const std::string& newname);

            /// Get total number of MPI tasks in this communicator group
            int Get_size() const;

            /// Get "rank" (ID number) of current task in this communicator group
            int Get_rank() const;

            /// Get name of communicator group (for error messages)
            std::string Get_name() const;

            /// Prevent further executation until all members of the bound communicator group enter the call
            void Barrier()
            {
              #ifdef MPI_MSG_DEBUG
              std::cout<<"rank "<<Get_rank()<<": Barrier() called"<<std::endl;
              #endif

              int errflag;
              errflag = MPI_Barrier(boundcomm);
              if(errflag!=0) {
                 std::ostringstream errmsg;
                 errmsg << "Error performing MPI_Barrier! Received error flag: "<<errflag;
                 utils_error().raise(LOCAL_INFO, errmsg.str());
              }

              #ifdef MPI_MSG_DEBUG
              std::cout<<"rank "<<Get_rank()<<": Barrier() passed"<<std::endl;
              #endif
           }

            /// Blocking receive
            ///  void*        buf      - memory address in which to store received message
            ///  int          count    - number of elements in message
            ///  MPI_Datatype datatype - datatype of each message element
            ///  int          source   - rank of sending (receiving?) process
            ///  int          tag      - message tag
            ///  MPI_status*  status   - struct containing data about the received message
            /// Returns:
            ///  MPI_status - struct containing data about the received message
            void Recv(void *buf /*out*/, int count, MPI_Datatype datatype,
                                  int source, int tag,
                                  MPI_Status *in_status=NULL /*out*/)
            {
              #ifdef MPI_MSG_DEBUG
              std::cout<<"rank "<<Get_rank()<<": Recv() called (count="<<count<<", source="<<source<<", tag="<<tag<<")"<<std::endl;
              #endif
              int errflag;
              errflag = MPI_Recv(buf, count, datatype, source, tag, boundcomm, in_status == NULL ? MPI_STATUS_IGNORE : in_status);
              if(errflag!=0)
              {
                std::ostringstream errmsg;
                errmsg << "Error performing MPI_Recv! Received error flag: "<<errflag;
                utils_error().raise(LOCAL_INFO, errmsg.str());
              }
              #ifdef MPI_MSG_DEBUG
              std::cout<<"rank "<<Get_rank()<<": Recv() finished "<<std::endl;
              #endif
            }

            /// Templated blocking receive to automatically determine types
            template<class T>
            void Recv(T *buf /*out*/, int count,
                      int source, int tag,
                      MPI_Status *status=NULL /*out*/)
            {
               static const MPI_Datatype datatype = get_mpi_data_type<T>::type();
               Recv(buf, count, datatype, source, tag, status);
            }

            /// Blocking send
            void Send(void *buf, int count, MPI_Datatype datatype,
                                  int destination, int tag)
            {
               #ifdef MPI_MSG_DEBUG
               std::cout<<"rank "<<Get_rank()<<": Send() called (count="<<count<<", destination="<<destination<<", tag="<<tag<<")"<<std::endl;
               #endif
               int errflag;
               errflag = MPI_Send(buf, count, datatype, destination, tag, boundcomm);
               if(errflag!=0) {
                 std::ostringstream errmsg;
                 errmsg << "Error performing MPI_Send! Received error flag: "<<errflag;
                 utils_error().raise(LOCAL_INFO, errmsg.str());
               }
               #ifdef MPI_MSG_DEBUG
               std::cout<<"rank "<<Get_rank()<<": Send() finished"<<std::endl;
               #endif
            }

            /// Blocking synchronous send (will not return until matching Recv is posted)
            void Ssend(void *buf, int count, MPI_Datatype datatype,
                                  int destination, int tag)
            {
               #ifdef MPI_MSG_DEBUG
               std::cout<<"rank "<<Get_rank()<<": Ssend() called (count="<<count<<", destination="<<destination<<", tag="<<tag<<")"<<std::endl;
               #endif
               int errflag;
               errflag = MPI_Ssend(buf, count, datatype, destination, tag, boundcomm);
               if(errflag!=0) {
                 std::ostringstream errmsg;
                 errmsg << "Error performing MPI_Ssend! Received error flag: "<<errflag;
                 utils_error().raise(LOCAL_INFO, errmsg.str());
               }
               #ifdef MPI_MSG_DEBUG
               std::cout<<"rank "<<Get_rank()<<": Ssend() finished"<<std::endl;
               #endif
            }

            /// Templated blocking send
            template<class T>
            void Send(T *buf, int count,
                      int destination, int tag)
            {
               static const MPI_Datatype datatype = get_mpi_data_type<T>::type();
               Send(buf, count, datatype, destination, tag);
            }

            /// Templated blocking synchronous send
            template<class T>
            void Ssend(T *buf, int count,
                      int destination, int tag)
            {
               static const MPI_Datatype datatype = get_mpi_data_type<T>::type();
               Ssend(buf, count, datatype, destination, tag);
            }

            /// Non-blocking send
            void Isend(void *buf, int count, MPI_Datatype datatype,
                                  int destination, int tag,
                                  MPI_Request *request /*out*/)
            {
              #ifdef MPI_MSG_DEBUG
              std::cerr<<"rank "<<Get_rank()<<": Isend() called (count="<<count<<", destination="<<destination<<", tag="<<tag<<")"<<std::endl;
              #endif
              int errflag;
               errflag = MPI_Isend(buf, count, datatype, destination, tag, boundcomm, request);
               if(errflag!=0) {
                 std::ostringstream errmsg;
                 errmsg << "Error performing MPI_Isend! Received error flag: "<<errflag;
                 utils_error().raise(LOCAL_INFO, errmsg.str());
               }
            }

            /// Templated Non-blocking send
            template<class T>
            void Isend(T *buf, int count,
                      int destination, int tag,
                      MPI_Request *request /*out*/)
            {
               static const MPI_Datatype datatype = get_mpi_data_type<T>::type();
               Isend(buf, count, datatype, destination, tag, request);
            }

            /// Blocking wait for e.g. Isend to complete
            void Wait(MPI_Request *request)
            {
               MPI_Status status;
               int errflag = MPI_Wait(request, &status);
               if(errflag!=0) {
                 std::ostringstream errmsg;
                 errmsg << "Error performing MPI_Wait! Received error flag: "<<errflag;
                 utils_error().raise(LOCAL_INFO, errmsg.str());
               }
            }

            // Non-blocking probe for messages waiting to be delivered
            bool Iprobe(int source, int tag, MPI_Status* in_status=NULL /*out*/)
            {
              //#ifdef MPI_MSG_DEBUG
              //std::cout<<"rank "<<Get_rank()<<": Iprobe() called (source="<<source<<", tag="<<tag<<")"<<std::endl;
              //#endif
               int errflag;
               int you_have_mail; // C does not have a bool type...
               MPI_Status def_status;
               MPI_Status* status;
               if(in_status!=NULL) {
                 status = in_status;
               } else {
                 status = &def_status;
               }
               //MPI_Iprobe(source, 1, boundcomm, &you_have_mail, status);
               errflag = MPI_Iprobe(source, tag, boundcomm, &you_have_mail, status);
               if(errflag!=0) {
                 std::ostringstream errmsg;
                 errmsg << "Error performing MPI_Iprobe! Received error flag: "<<errflag;
                 utils_error().raise(LOCAL_INFO, errmsg.str());
               }
               #ifdef MPI_MSG_DEBUG
               if(you_have_mail!=0) {
                     std::cerr<<"rank "<<Get_rank()<<": Iprobe: Message waiting from process "<<status->MPI_SOURCE<<std::endl;
               }
               #endif
               return (you_have_mail != 0);
            }

            // Blocking probe for a message. Doesn't return until matching message found.
            // No point having default NULL status this time, because the only reason to
            // use this function is to inspect the message status.
            void Probe(int source, int tag, MPI_Status* status)
            {
               int errflag;
               errflag = MPI_Probe(source, tag, boundcomm, status);
               if(errflag!=0) {
                 std::ostringstream errmsg;
                 errmsg << "Error performing MPI_Probe! Received error flag: "<<errflag;
                 utils_error().raise(LOCAL_INFO, errmsg.str());
               }
            }

            // Perform an Isend to all other processes
            // (using templated non-blocking send repeatedly)
            template<class T>
            void IsendToAll(T *buf, int count, int tag,
                      MPI_Request *in_req=NULL /*out*/)
            {
               MPI_Request def_req;
               MPI_Request* req;
               if(in_req!=NULL) {
                 req = in_req;
               } else {
                 req = &def_req;
               }
               int rank = Get_rank();
               int size = Get_size();
               for(int i=0; i<size; i++)
               {
                  if(i!=rank) Isend(buf, count, i, tag, req);
               }
            }

            template <typename T>
            void Bcast (std::vector<T>& buffer, int count, int root)
            {
                static const MPI_Datatype datatype = get_mpi_data_type<T>::type();

                MPI_Bcast (&buffer[0], count, datatype, root, boundcomm);
            }

            template<typename T>
            void Scatter (std::vector<T> &sendbuf, T &recvbuf, int root)
            {
                static const MPI_Datatype datatype = get_mpi_data_type<T>::type();

                MPI_Scatter (&sendbuf[0], 1, datatype, &recvbuf, 1, datatype, root, boundcomm);
            }

            template<typename T>
            void Allreduce (T &sendbuf, T &recvbuf, MPI_Op op)
            {
                static const MPI_Datatype datatype = get_mpi_data_type<T>::type();

                MPI_Allreduce (&sendbuf, &recvbuf, 1, datatype, op, boundcomm);
            }

            template<typename T>
            void Gather(std::vector<T> &sendbuf, std::vector<T> &recvbuf, int root)
            {
                static const MPI_Datatype datatype = get_mpi_data_type<T>::type();

                int sendcount = sendbuf.size();
                int recvcount = sendbuf.size();
                //std::cerr<<"rank "<<Get_rank()<<": Gather pars: sendcount="<<sendcount<<std::endl;
                if(Get_rank()==0)
                {
                   if(recvbuf.size()<sendbuf.size()*Get_size())
                   {
                       std::ostringstream errmsg;
                       errmsg << "Error performing Gather! Recv buffer is not big enough to fit the expected data! We expect "<<Get_size()<<" messages of count "<<recvcount<<", (total size="<<recvcount*Get_size()<<") but the recv buffer only has size "<<recvbuf.size()<<"!";
                       utils_error().raise(LOCAL_INFO, errmsg.str());
                   }
                }
                int errflag = MPI_Gather(&sendbuf[0], sendcount, datatype,
                                         &recvbuf[0], recvcount, datatype,
                                         root, boundcomm);
                if(errflag!=0) {
                   std::ostringstream errmsg;
                   errmsg << "Error performing Gather! Received error flag: "<<errflag;
                   utils_error().raise(LOCAL_INFO, errmsg.str());
                }
            }

            template<typename T>
            void Gatherv(std::vector<T> &sendbuf, std::vector<T> &recvbuf, std::vector<int> recvcounts, int root)
            {
                static const MPI_Datatype datatype = get_mpi_data_type<T>::type();

                //std::cerr<<"rank "<<Get_rank()<<": Gatherv pars: recvcounts="<<recvcounts<<std::endl;

                // We will automatically calculate the displacements assuming that the incoming
                // data should just be stacked in the order of the process ranks
                std::vector<int> displs;
                displs.push_back(0);
                std::size_t totalsize = 0;
                for(auto it=recvcounts.begin(); it!=recvcounts.end(); ++it)
                {
                    if(std::next(it)!=recvcounts.end()) displs.push_back(*it + displs.back());
                    totalsize += (*it);
                }
                if(Get_rank()==0)
                {
                   if(recvbuf.size()<totalsize)
                   {
                       std::ostringstream errmsg;
                       errmsg << "Error performing Gatherv! Recv buffer is not big enough to fit the expected data! We expect messages with total size "<<totalsize<<" but the recv buffer only has size "<<recvbuf.size()<<"!";
                       utils_error().raise(LOCAL_INFO, errmsg.str());
                   }
                }
                //std::cerr<<"rank "<<Get_rank()<<": sendbuf.size()="<<sendbuf.size()<<", recvbuf.size()="<<recvbuf.size()<<", "<<"recvcounts="<<recvcounts<<", displs="<<displs<<std::endl;
                int sendcount = sendbuf.size();
                int errflag = MPI_Gatherv(&sendbuf[0], sendcount, datatype,
                                          &recvbuf[0], &recvcounts[0], &displs[0],
                                          datatype, root, boundcomm);
                if(errflag!=0) {
                 std::ostringstream errmsg;
                 errmsg << "Error performing MPI_Gatherv! Received error flag: "<<errflag;
                 utils_error().raise(LOCAL_INFO, errmsg.str());
               }
            }

            template<typename T>
            void AllGather(std::vector<T> &sendbuf, std::vector<T> &recvbuf)
            {
               static const MPI_Datatype datatype = get_mpi_data_type<T>::type();

               int sendcount = sendbuf.size();
               int recvcount = sendbuf.size();

               if(recvbuf.size()<sendbuf.size()*Get_size())
               {
                   std::ostringstream errmsg;
                   errmsg << "Error performing AllGather! Recv buffer is not big enough to fit the expected data! We expect "<<Get_size()<<" messages of count "<<recvcount<<", (total size="<<recvcount*Get_size()<<") but the recv buffer only has size "<<recvbuf.size()<<"!";
                   utils_error().raise(LOCAL_INFO, errmsg.str());
               }

               int errflag = MPI_Allgather(&sendbuf[0], sendcount, datatype,
                                           &recvbuf[0], recvcount, datatype, boundcomm);

               if(errflag!=0) {
                 std::ostringstream errmsg;
                 errmsg << "Error performing MPI_Allgather! Received error flag: "<<errflag;
                 utils_error().raise(LOCAL_INFO, errmsg.str());
               }
            }


            template<typename T>
            void AllGatherv(std::vector<T> &sendbuf, std::vector<T> &recvbuf, std::vector<int> recvcounts)
            {
               static const MPI_Datatype datatype = get_mpi_data_type<T>::type();

               // We will automatically calculate the displacements assuming that the incoming
               // data should just be stacked in the order of the process ranks
               std::vector<int> displs(Get_size());
               displs.push_back(0);
               for(size_t i=0; i<(recvcounts.size()-1); i++)
               {
                   displs.push_back(i);
               }

               int sendcount = sendbuf.size();
               int errflag = MPI_Allgatherv(&sendbuf[0], sendcount, datatype,
                                            &recvbuf[0], &recvcounts, &displs,
                                            datatype, boundcomm);
               if(errflag!=0) {
                 std::ostringstream errmsg;
                 errmsg << "Error performing MPI_Allgatherv! Received error flag: "<<errflag;
                 utils_error().raise(LOCAL_INFO, errmsg.str());
               }
            }

            // Force all processes in this group (possibly all processes in
            // the "WORLD"; implementation dependent) to stop executing.
            // Useful for abnormal termination (since if one processes throws
            // an exception then the others can easily get stuck waiting
            // for messages that will never arrive).
            void Abort()
            {
              std::cerr << "rank "<<Get_rank()<<": Issuing MPI_Abort command, attempting to terminate all processes..." << std::endl;
              MPI_Abort(boundcomm, 1);
            }

            /// Tells master to wait until all other processes pass this function, with the specified MPI tag
            void masterWaitForAll(int tag);

            /// Inverse of the above. Everyone waits for master to pass this (but not for anyone else)
            void allWaitForMaster(int tag);

            /// Everyone waits for master to pass this, and runs "func" periodically while waiting
            void allWaitForMasterWithFunc(int tag, void (*func)());

            /// An implementation of Barrier that will fall through if synchronisation takes too long
            /// Could modify to take a function pointer to run while waiting.
            /// Supply MPI tag to identify each particular barrier.
            /// Returns 'false' if barrier succeeds, 'true' if barrier times out (i.e. answers the question "did the barrier time out?")
            bool BarrierWithTimeout(const std::chrono::duration<double> timeout, const int tag);

            /// This is a fancy barrier that waits a certain amount of time after the FIRST process
            /// enters before unlocking (so that other action can be taken). This means that all the
            /// processes that enter the barrier *do* get synchronised, even if the barrier unlocks.
            /// This helps the synchronisation to be achieved next time.
            bool BarrierWithCommonTimeout(std::chrono::duration<double> timeout,
                                          const int tag_entered,
                                          const int tag_timeleft);

            /// This routine exists for MPI debugging purposes, to help make sure that
            /// all MPI messages are received before MPI_Finalize is called.
            /// It doesn't fix any problems, it just lets us notice if they exist.
            void check_for_unreceived_messages(int timeout);

            /// Receive any waiting messages with a given tag from a given source (possibly MPI_ANY_SOURCE)
            /// Need to know what the messages are in order to provide an appropriate Recv buffer (and size)
            /// The last message received will remain in the buffer and may be used (useful if several messages
            /// about the same thing are expected to pile up)
            template<class T>
            void Recv_all(T* buffer, int size, int source, int tag, int max_loops)
            {
              int loop = 0;

              MPI_Status status;
              while(loop<max_loops and Iprobe(source, tag, &status))
              {
                #ifdef SIGNAL_DEBUG
                LOGGER << "Detected message from process "<<status.MPI_SOURCE<<" with tag "<<status.MPI_TAG<<"; doing Recv" << EOM;
                #endif
                MPI_Status recv_status;
                Recv(buffer, size, status.MPI_SOURCE, status.MPI_TAG, &recv_status);
                #ifdef SIGNAL_DEBUG
                LOGGER << "Received message from process "<<status.MPI_SOURCE<<" with tag "<<status.MPI_TAG<<". Discarding any existing message in the output buffer as obsolete..." << EOM;
                #endif
                ++loop;
              }

              if(loop==max_loops)
              {
                std::ostringstream errmsg;
                errmsg << "Error while attempting to clean out unreceived messages from other processes! Received maximum allowed number of messages ("<<loop<<", note that MPI size is "<<Get_size()<<")";
                utils_error().raise(LOCAL_INFO, errmsg.str());
              }

              if(loop>0) LOGGER << "Communicator '"<<myname<<"' received "<<loop<<" messages with tag "<<tag<<". Only the last of these will be readable from the output buffer, the rest were discarded."<<EOM;
            }

            /// A generic place to store a tag commonly used by this communicator
            int mytag = 1;

            /// Get pointer to raw bound communicator
            MPI_Comm* get_boundcomm() { return &boundcomm; }

            /// Get the process ID of the master process (rank 0)
            long int MasterPID();

            /// Set the process ID of the master process (rank 0)
            void set_MasterPID(long int p);

         private:

            /// The MPI communicator to which the current object "talks".
            MPI_Comm boundcomm;

            /// A name to identify the communicator group to which this object is bound
            std::string myname;

            /// The process ID of the master process (rank 0)
            static long int pid;
      };

      /// Check if MPI_Init has been called (it is an error to call it twice)
      EXPORT_SYMBOLS bool Is_initialized();

      /// Initialise MPI
      EXPORT_SYMBOLS void Init();

      /// Check if MPI_Finalize has been called (it is an error to do anything else after this)
      EXPORT_SYMBOLS bool Is_finalized();

      /// Finalize MPI
      EXPORT_SYMBOLS void Finalize();

      /// Prepare for calling MPI_Finalize, but call MPI_abort and exit function if timeout is exceeded.
      EXPORT_SYMBOLS bool PrepareForFinalizeWithTimeout(bool use_mpi_abort);

      /// Nice wrapper for getting the message size from an MPI_status struct.
      /// Provide the type whose MPI_Datatype you want to retrieve as the
      /// template argument.
      template<class T>
      int Get_count(MPI_Status *status)
      {
         static const MPI_Datatype datatype = get_mpi_data_type<T>::type();
         int msgsize;
         MPI_Get_count(status, datatype, &msgsize);
         if(msgsize<0)
         {
            std::ostringstream errmsg;
            errmsg << "Error performing MPI_Get_count! Message size returned negative (value was "<<msgsize<<")! This can happen if the number of bytes received is not a multiple of the size of the specified MPI_Datatype. In other words you may have specified a type that doesn't match the type of the sent message; please double-check this.";
            utils_error().raise(LOCAL_INFO, errmsg.str());
         }
         return msgsize;
      }

      /// @{ Helpers for registration of compound datatypes

      /// Structure to hold an MPI startup function plus metadata
      class MpiIniFunc
      {
        private:
          std::string location;
          std::string name;
          void (*func)();
        public:
          MpiIniFunc(const std::string& l, const std::string& n, void(*f)())
            : location(l)
            , name(n)
            , func(f)
          {}
          void runme()
          {
            (*func)();
          }
          std::string mylocation(){return location;}
          std::string myname    (){return name;}
      };

      /// Struct for adding functions to the 'mpi_ini_functions' map
      ///
      /// This will add functions to the map when it is constructed. Works
      /// on the same idea as the "ini_code" struct, except it doesn't
      /// cause the functions to be run, just "queues them up" so to speak.
      // struct AddMpiIniFunc {
      //   AddMpiIniFunc(const std::string& local_info, const std::string& name, void(*func)());
      // };

      /// @}

   }
}


#endif // include guard
#endif // MPI

