//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
/// \file
///  Utility Functions for the Gambit Scanner
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2023 Jan
///
///  *********************************************

#ifndef __scanner_util_types_hpp__
#define __scanner_util_types_hpp__

#include <Eigen/Dense>

namespace Gambit
{
    
    namespace Scanner
    {

        /****************************************/
        /********* Eigen3 definitions ***********/
        /****************************************/
        
        /// \brief A vector.
        ///
        template <typename T>
        using vector = Eigen::Matrix<T, Eigen::Dynamic, 1>;
        
        /// \brief A row vector.
        ///
        template <typename T>
        using row_vector = Eigen::Matrix<T, 1, Eigen::Dynamic>;
        
        /// \brief A matrix.
        ///
        template <typename T>
        using matrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;
        
        /// \brief Represents the unit hypercube.
        ///
        template <typename T>
        using hyper_cube_ref = Eigen::Ref<vector<T>, 0, Eigen::Stride<Eigen::Dynamic, Eigen::Dynamic>>;
        
        /// \brief Vector using raw data.
        ///
        template <typename T>
        using map_vector = Eigen::Map<vector<T>, Eigen::Unaligned, Eigen::Stride<1, 1>>;
        
    }
    
}

#endif
