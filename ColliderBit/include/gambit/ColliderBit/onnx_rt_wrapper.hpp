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

      /// Given a multi-node input std::vector, populate and return the multi-node output std::vector
      /// Apologies for the SFINAE, needed to deal with vec<vec<float>> and vec<vec<double>> seperately
      /// to vec<float> and vec<double>
      template<typename Tin = float, typename Tout =  float, 
                std::enable_if_t<std::is_arithmetic_v<Tin> && std::is_arithmetic_v<Tout>, int> = 0 > 
      void compute(std::vector<std::vector<Tin>> &inputs, std::vector<std::vector<Tout>>& outputs) const
      {
        /// Check that number of input nodes matches what the model expects
        if (inputs.size() != _inDims.size())
        {
          throw("Expected " + std::to_string(_inDims.size())
                + " input nodes, received " + std::to_string(inputs.size()));
        }

        // Create input tensor objects from input data
        std::vector<Ort::Value> ort_input;
        ort_input.reserve(_inDims.size());
        auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
        for (size_t i=0; i < _inDims.size(); ++i)
        {

          // Check that input data matches expected input node dimension
          if (inputs[i].size() != (size_t) _inDimsFlat[i])
          {
            throw("Expected flattened input node dimension " + std::to_string(_inDimsFlat[i])
                    + ", received " + std::to_string(inputs[i].size()));
          }

          ort_input.emplace_back(Ort::Value::CreateTensor<Tin>(memory_info,
                                                                  inputs[i].data(), inputs[i].size(),
                                                                  _inDims[i].data(), _inDims[i].size()));
        }

        // Retrieve output tensors
        auto ort_output = _session->Run(Ort::RunOptions{nullptr}, _inNames.data(),
                                        ort_input.data(), ort_input.size(),
                                        _outNames.data(), _outNames.size());

        // Construct flattened values and return
        outputs.clear();
        outputs.resize(_outDims.size());
        for (size_t i = 0; i < _outDims.size(); ++i)
        {
          Tout* floatarr = ort_output[i].GetTensorMutableData<Tout>();
          outputs[i].assign(floatarr, floatarr + _outDimsFlat[i]);
        }                                             
      }

      /// Given a single-node input std::vector, populate and return the single-node output std::vector
      template<typename Tin = float, typename Tout = float,
              std::enable_if_t<std::is_arithmetic_v<Tin> && std::is_arithmetic_v<Tout>, int> = 0> 
      void compute(const std::vector<Tin>& inputs, std::vector<Tout> & outputs) const
      {
        if (_inDims.size() != 1 || _outDims.size() != 1)
        {
          throw("This method assumes a single input/output node!");
        }
        std::vector<std::vector<Tin>> wrapped_inputs = { inputs };
        std::vector<std::vector<Tout>> wrapped_outputs;
        compute(wrapped_inputs, wrapped_outputs);
        outputs = wrapped_outputs[0];
      }

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
