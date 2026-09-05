//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Wrapper class for interfacing to ONNXRunTime
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomasz Procter
///  \date 2023 August
///
///  *********************************************
#include "gambit/cmake/cmake_variables.hpp"

#ifndef EXCLUDE_ONNXRUNTIME

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "onnxruntime_cxx_api.h"

#pragma once

namespace Gambit
{

  namespace ColliderBit
  {

    // Very heavily inspired/copied from Rivet (to be fair, I wrote that too)
    // TODO: Exactly how we handle onnx files is probably a WiP - class name, where it belongs, etc.
    class onnx_rt_wrapper
    {

    public:

      onnx_rt_wrapper(const std::string& filename, const std::string& runname = "GambitONNXrt");

      onnx_rt_wrapper() = delete;

      /// Given a multi-node input vector, populate and return the multi-node output vector
      void compute(std::vector<std::vector<float>> &inputs, std::vector<std::vector<float>>& outputs) const;

      /// Given a single-node input vector, populate and return the single-node output vector
      void compute(std::vector<float>& inputs, std::vector<float> & outputs);

      /// Printing function for debugging.
      friend std::ostream& operator <<(std::ostream& os, const onnx_rt_wrapper& rort);

    private:

      // Check the ONNX file to get hyperparameters etc.
      void getNetworkInfo();
        
        
      // Member variables

      /// ONNXrt environment for this session
      std::unique_ptr<Ort::Env> _env;

      /// ONNXrt session holiding the network
      std::unique_ptr<Ort::Session> _session;

      /// Network metadata
      std::unique_ptr<Ort::ModelMetadata> _metadata;

      /// Input/output node dimensions - could be a multidimensional tensor
      std::vector<std::vector<int64_t>> _inDims, _outDims;

      /// Equivalent length for flattened input/ouput node structure
      std::vector<int64_t> _inDimsFlat, _outDimsFlat;

      /// Types of input/output nodes (as ONNX enums)
      std::vector<ONNXTensorElementDataType> _inTypes, _outTypes;

      /// Pointers to the ONNXrt input/output node names
      std::vector<Ort::AllocatedStringPtr> _inNamesPtr, _outNamesPtr;

      /// C-style arrays of the input/output node names
      std::vector<const char*> _inNames, _outNames;

    };

  }

}

#endif  // EXCLUDE_ONNXRUNTIME
