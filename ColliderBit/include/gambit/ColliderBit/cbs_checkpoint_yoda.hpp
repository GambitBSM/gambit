//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Scale and merge per-file CBS checkpoint YODA files.
///
///  *********************************************

#pragma once

#include <string>
#include <vector>

namespace Gambit
{
  namespace ColliderBit
  {
    /// Copy a checkpoint YODA and scale its /RAW/ fillable objects by @a scale.
    /// Cross-section and beam-info objects are left unchanged. The source file
    /// is not modified.
    void scale_checkpoint_yoda(const std::string& source,
                               const std::string& destination,
                               double scale);

    /// Equivalently merge scaled YODA files, pin the collider cross section,
    /// finalize, and write one YODA file. Each entry of @a scaled_files may
    /// already carry Rivet's file.yoda:=xsec_pb suffix.
    void merge_checkpoint_yodas(const std::vector<std::string>& scaled_files,
                                const std::string& destination,
                                double cross_section_pb,
                                double cross_section_uncert_pb);
  }
}
