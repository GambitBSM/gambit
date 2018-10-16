//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A collection of tools for interacting with
///  HDF5 databases.
///
///  Currently I am using the C++ bindings for
///  HDF5, however they are a bit crap and it may
///  be better to just write our own.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 May
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jul
///
///  *********************************************

#ifndef __hdf5tools_hpp__
#define __hdf5tools_hpp__

// Standard library
#include <cstdint>
#include <memory>
#include <sstream>
#include <iostream>
#include <algorithm>

// GAMBIT
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/mpiwrapper.hpp"

// HDF5
#include <hdf5.h>

// Boost
#include <boost/utility/enable_if.hpp>


/// Provide template specialisation of get_hdf5_data_type only if the requested type hasn't been used to define one already.
#define SPECIALISE_HDF5_DATA_TYPE_IF_NEEDED(TYPEDEFD_TYPE, RETURN_HDF5_TYPE)                                  \
      template<typename T>                                                                                                   \
      struct get_hdf5_data_type<T, typename boost::enable_if_c< std::is_same<T, TYPEDEFD_TYPE>::value                     && \
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
         static hid_t type() { return RETURN_HDF5_TYPE; }                                                            \
      };                                                                                                                     \


namespace Gambit
{

  namespace Printers
  {

      namespace HDF5
      {

         /// @{ File and group manipulation

         /// Create or open hdf5 file
         // If overwrite=true then any existing file will be deleted and replaced. USE CAREFULLY!!!
         // third argument "oldfile" is used to report whether an existing file was opened (true if yes)
         hid_t openFile(const std::string& fname, bool overwrite, bool& oldfile, const char access_type='r');
         hid_t openFile(const std::string& fname, bool overwrite=false, const char access_type='r');

         /// Close hdf5 file
         hid_t closeFile(hid_t file);

         /// Check if hdf5 file exists and can be opened in read/write mode
         bool checkFileReadable(const std::string& fname, std::string& msg);
         /// Thin wrapper for the above to discard failure message
         inline bool checkFileReadable(const std::string& fname)
         { std::string garbage; return checkFileReadable(fname, garbage); }

         /// Check if a group exists and can be accessed
         bool checkGroupReadable(hid_t location, const std::string& groupname, std::string& msg);
         /// Thin wrapper for the above to discard failure message
         inline bool checkGroupReadable(hid_t location, const std::string& groupname)
         { std::string garbage; return checkGroupReadable(location, groupname, garbage); }

         /// Create hdf5 file (always overwrite existing files)
         hid_t createFile(const std::string& fname);

         /// Create a group inside the specified location
         // Argument "location" can be a pointer to either a file or another group
         hid_t createGroup(hid_t location, const std::string& name);

         /// Silence error report (e.g. while probing for file existence)
         void errorsOff();

         /// Restore error report
         void errorsOn();

         // Modified minimally from https://github.com/gregreen/h5utils/blob/master/src/h5utils.cpp#L92
         // Credit: Gregory Green 2012
         /*
          * Opens a group, creating it if it does not exist. Nonexistent parent groups are also
          * created. This works similarly to the Unix/Linux command
          * mkdir -p /parent/subgroup/group
          * in that if /parent and /parent/subgroup do not exist, they will be created.
          *
          * If no accessmode has H5Utils::DONOTCREATE flag set, then returns NULL if group
          * does not yet exist.
          *
          */
         hid_t openGroup(hid_t file_id, const std::string& name, bool nocreate=false);

         /// Close group
         hid_t closeGroup(hid_t group);

         /// List object names in a group
         std::vector<std::string> lsGroup(hid_t group_id);

         /// Get type of an object in a group
         hid_t getH5DatasetType(hid_t group_id, const std::string& dset_name);

         /// Release datatype identifier
         hid_t closeType(hid_t type_id);

         /// @}

         /// @{ Dataset and dataspace manipulation

         /// Open dataset
         hid_t openDataset(hid_t dset_id, const std::string& name, bool error_off=false);

         /// Close dataset
         hid_t closeDataset(hid_t dset_id);

         /// Get dataspace
         hid_t getSpace(hid_t dset_id);

         /// Close dataspace
         hid_t closeSpace(hid_t space_id);

         /// Get simple dataspace extent
         hssize_t getSimpleExtentNpoints(hid_t dset_id);

         /// Get name of dataset
         std::string getName(hid_t dset_id);

         /// Select a simple hyperslab in a 1D dataset
         std::pair<hid_t,hid_t> selectChunk(const hid_t dset_id, std::size_t offset, std::size_t length);
  
         /// @}

      }

      /// Base template is left undefined in order to raise
      /// a compile error if specialisation doesn't exist.
      template<typename T, typename Enable=void>
      struct get_hdf5_data_type;

      /// True types
      /// @{
      template<> struct get_hdf5_data_type<char>              { static hid_t type() { return H5T_NATIVE_CHAR   ; } };
      template<> struct get_hdf5_data_type<short>             { static hid_t type() { return H5T_NATIVE_SHORT  ; } };
      template<> struct get_hdf5_data_type<int>               { static hid_t type() { return H5T_NATIVE_INT    ; } };
      template<> struct get_hdf5_data_type<long>              { static hid_t type() { return H5T_NATIVE_LONG   ; } };
      template<> struct get_hdf5_data_type<long long>         { static hid_t type() { return H5T_NATIVE_LLONG  ; } };
      template<> struct get_hdf5_data_type<unsigned char>     { static hid_t type() { return H5T_NATIVE_UCHAR  ; } };
      template<> struct get_hdf5_data_type<unsigned short>    { static hid_t type() { return H5T_NATIVE_USHORT ; } };
      template<> struct get_hdf5_data_type<unsigned int>      { static hid_t type() { return H5T_NATIVE_UINT   ; } };
      template<> struct get_hdf5_data_type<unsigned long>     { static hid_t type() { return H5T_NATIVE_ULONG  ; } };
      template<> struct get_hdf5_data_type<unsigned long long>{ static hid_t type() { return H5T_NATIVE_ULLONG ; } };
      template<> struct get_hdf5_data_type<float>             { static hid_t type() { return H5T_NATIVE_FLOAT  ; } };
      template<> struct get_hdf5_data_type<double>            { static hid_t type() { return H5T_NATIVE_DOUBLE ; } };
      template<> struct get_hdf5_data_type<long double>       { static hid_t type() { return H5T_NATIVE_LDOUBLE; } };
      template<> struct get_hdf5_data_type<bool>              { static hid_t type() { return H5T_NATIVE_UINT8  ; } };
      // Bools are a bit trickier because C has no built-in boolean type (until recently; anyway
      // the HDF5 libraries were written in C before this existed). We also want something that
      // will be recognised as a bool by h5py. For now we just use an unsigned int.

      // Macro sequence for iterating over all allowed output types
      #define H5_OUTPUT_TYPES \
        (char) \
        (short) \
        (int) \
        (long) \
        (long long) \
        (unsigned char) \
        (unsigned short) \
        (unsigned int) \
        (unsigned long) \
        (unsigned long long) \
        (float) \
        (double) \
        (long double) \
        (bool)

      /// DEBUG: print to stdout all HDF5 type IDs
      void printAllH5Types(void);

      /// @}

      /// Typedef'd types; enabled only where they differ from the true types.
      /// @{
      SPECIALISE_HDF5_DATA_TYPE_IF_NEEDED(int8_t,   H5T_NATIVE_INT8)
      SPECIALISE_HDF5_DATA_TYPE_IF_NEEDED(uint8_t,  H5T_NATIVE_UINT8)
      SPECIALISE_HDF5_DATA_TYPE_IF_NEEDED(int16_t,  H5T_NATIVE_INT16)
      SPECIALISE_HDF5_DATA_TYPE_IF_NEEDED(uint16_t, H5T_NATIVE_UINT16)
      SPECIALISE_HDF5_DATA_TYPE_IF_NEEDED(int32_t,  H5T_NATIVE_INT32)
      SPECIALISE_HDF5_DATA_TYPE_IF_NEEDED(uint32_t, H5T_NATIVE_UINT32)
      SPECIALISE_HDF5_DATA_TYPE_IF_NEEDED(int64_t,  H5T_NATIVE_INT64)
      SPECIALISE_HDF5_DATA_TYPE_IF_NEEDED(uint64_t, H5T_NATIVE_UINT64)
      /// @}

      //!_______________________________________________________________________________________

  }
}

#endif

