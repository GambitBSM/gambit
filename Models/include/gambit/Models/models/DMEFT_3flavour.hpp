//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
/// Header file for DMEFT_3flavour
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 12:32PM on October 15, 2019
///
///  \author Sanjay Bloor
///         (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 Oct
///
///  \author Patrick Stöcker
///          (patrick.stoecker@kit.edu)
///  \date 2021 Mar, Sep
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 Sep
///
///  \author Felix Kahlhoefer
///          (kahlhoefer@kit.edu)
///  \date 2022 Apr
///
///  ********************************************* 

#ifndef __DMEFT_3flavour_hpp__
#define __DMEFT_3flavour_hpp__

#define MODEL DMEFT_3flavour
  START_MODEL

  DEFINEPARS(C51, C52, C61u, C61d, C62u, C62d, C63u, C63d, C64u, C64d, mchi)

#undef MODEL

#endif
