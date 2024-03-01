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

#ifndef EXCLUDE_ONNXRUNTIME

#include "gambit/ColliderBit/onnx_rt_wrapper.hpp"

using namespace std;

namespace Gambit
{

  namespace ColliderBit
  {

    onnx_rt_wrapper::onnx_rt_wrapper(const string & filename, const string& runname)
    {
      // Set some ORT variables that need to be kept in memory
      _env = std::make_unique<Ort::Env>(ORT_LOGGING_LEVEL_WARNING,runname.c_str() );
      Ort::SessionOptions sessionopts; //todo - check this is allowed to go out of scope.
      _session = std::make_unique<Ort::Session> (*_env, filename.c_str(), sessionopts);

      // Get network hyper-params and store them (input, output shape, etc.) in the class members.
      getNetworkInfo();
    }


    /// Given a multi-node input vector, populate and return the multi-node output vector
    void onnx_rt_wrapper::compute(std::vector<std::vector<float>> &inputs, std::vector<std::vector<float>>& outputs) const
    {
      /// Check that number of input nodes matches what the model expects
      if (inputs.size() != _inDims.size())
      {
        throw("Expected " + to_string(_inDims.size())
              + " input nodes, received " + to_string(inputs.size()));
      }

      // Create input tensor objects from input data
      vector<Ort::Value> ort_input;
      ort_input.reserve(_inDims.size());
      auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
      for (size_t i=0; i < _inDims.size(); ++i)
      {

        // Check that input data matches expected input node dimension
        if (inputs[i].size() != (size_t) _inDimsFlat[i])
        {
          throw("Expected flattened input node dimension " + to_string(_inDimsFlat[i])
                  + ", received " + to_string(inputs[i].size()));
        }

        ort_input.emplace_back(Ort::Value::CreateTensor<float>(memory_info,
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
        float* floatarr = ort_output[i].GetTensorMutableData<float>();
        outputs[i].assign(floatarr, floatarr + _outDimsFlat[i]);
      }                                             
    }


    /// Given a single-node input vector, populate and return the single-node output vector
    void onnx_rt_wrapper::compute(vector<float>& inputs, vector<float> & outputs)
    {
      if (_inDims.size() != 1 || _outDims.size() != 1)
      {
        throw("This method assumes a single input/output node!");
      }
      vector<vector<float>> wrapped_inputs = { inputs };
      vector<vector<float>> wrapped_outputs;
      compute(wrapped_inputs, wrapped_outputs);
      outputs = wrapped_outputs[0];
    }


    /// Printing function for debugging.
    std::ostream& operator <<(std::ostream& os, const onnx_rt_wrapper& rort)
    {
      os << "RivetONNXrt Network Summary: \n";
      for (size_t i=0; i < rort._inNames.size(); ++i)
      {
        os << "- Input node " << i << " name: " << rort._inNames[i];
        os << ", dimensions: (";
        for (size_t j=0; j < rort._inDims[i].size(); ++j)
        {
          if (j)  os << ", ";
          os << rort._inDims[i][j];
        }
        os << "), type (as ONNX enums): " << rort._inTypes[i] << "\n";
      }
      for (size_t i=0; i < rort._outNames.size(); ++i)
      {
        os << "- Output node " << i << " name: " << rort._outNames[i];
        os << ", dimensions: (";
        for (size_t j=0; j < rort._outDims[i].size(); ++j)
        {
          if (j)  os << ", ";
          os << rort._outDims[i][j];
        }
        os << "), type (as ONNX enums): (" << rort._outTypes[i] << "\n";
      }
      return os;
    }


    // Check the ONNX file to get hyperparameters etc.
    void onnx_rt_wrapper::getNetworkInfo()
    {
      Ort::AllocatorWithDefaultOptions allocator;

      // Retrieve network metadat
      _metadata = std::make_unique<Ort::ModelMetadata>(_session->GetModelMetadata());

      // Find out how many input nodes the model expects
      const size_t num_input_nodes = _session->GetInputCount();
      _inDimsFlat.reserve(num_input_nodes);
      _inTypes.reserve(num_input_nodes);
      _inDims.reserve(num_input_nodes);
      _inNames.reserve(num_input_nodes);
      _inNamesPtr.reserve(num_input_nodes);
      for (size_t i = 0; i < num_input_nodes; ++i)
      {
        // Retrieve input node name
        auto input_name = _session->GetInputNameAllocated(i, allocator);
        _inNames.push_back(input_name.get());
        _inNamesPtr.push_back(std::move(input_name));

        // Retrieve input node type
        auto in_type_info = _session->GetInputTypeInfo(i);
        auto in_tensor_info = in_type_info.GetTensorTypeAndShapeInfo();
        _inTypes.push_back(in_tensor_info.GetElementType());
        _inDims.push_back(in_tensor_info.GetShape());
      }

      // Fix negative shape values - appears to be an artefact of batch size issues.
      for (auto& dims : _inDims)
      {
        int64_t n = 1;
        for (auto& dim : dims)
        {
          if (dim < 0)  dim = abs(dim);
          n *= dim;
        }
        _inDimsFlat.push_back(n);
      }

      // Find out how many output nodes the model expects
      const size_t num_output_nodes = _session->GetOutputCount();
      _outDimsFlat.reserve(num_output_nodes);
      _outTypes.reserve(num_output_nodes);
      _outDims.reserve(num_output_nodes);
      _outNames.reserve(num_output_nodes);
      _outNamesPtr.reserve(num_output_nodes);
      for (size_t i = 0; i < num_output_nodes; ++i)
      {
        // Retrieve output node name
        auto output_name = _session->GetOutputNameAllocated(i, allocator);
        _outNames.push_back(output_name.get());
        _outNamesPtr.push_back(std::move(output_name));

        // Retrieve input node type
        auto out_type_info = _session->GetOutputTypeInfo(i);
        auto out_tensor_info = out_type_info.GetTensorTypeAndShapeInfo();
        _outTypes.push_back(out_tensor_info.GetElementType());
        _outDims.push_back(out_tensor_info.GetShape());
      }

      // Fix negative shape values - appears to be an artefact of batch size issues.
      for (auto& dims : _outDims)
      {
        int64_t n = 1;
        for (auto& dim : dims)
        {
          if (dim < 0)  dim = abs(dim);
          n *= dim;
        }
        _outDimsFlat.push_back(n);
      }
    }

  }

}

#endif