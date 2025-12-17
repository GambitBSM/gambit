# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake configuration scripts for downloading
#  datasets required by GAMBIT modules
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Anders Kvellestad
#          (anderkve@fys.uio.no)
#  \date 2022 Feb
#
#************************************************

# Define the download command to use for datasets
set(DL_DATASET "${PROJECT_SOURCE_DIR}/cmake/scripts/safe_dl.sh" "${CMAKE_BINARY_DIR}" "${CMAKE_COMMAND}" "${CMAKE_DOWNLOAD_FLAGS}")

# Define a macro and function for adding nuke targets for downloaded datasets
macro(get_dataset_paths dataset_name build_path nuke_stamps)
  set(stamp_path "${CMAKE_BINARY_DIR}/${dataset_name}-prefix/src/${dataset_name}-stamp/${dataset_name}")
  set(${build_path} "${CMAKE_BINARY_DIR}/${dataset_name}-prefix/src/${dataset_name}-build")
  set(${nuke_stamps} ${stamp_path}-download ${stamp_path}-mkdir ${stamp_path}-patch ${stamp_path}-update)
endmacro()

function(add_dataset_nuke dataset_name dir)
  get_dataset_paths(${dataset_name} build_path nuke-stamps)
  add_custom_target(nuke-${dataset_name} COMMAND ${CMAKE_COMMAND} -E remove -f ${nuke-stamps}
                                    COMMAND ${CMAKE_COMMAND} -E remove_directory "${build_path}"
                                    COMMAND ${CMAKE_COMMAND} -E remove_directory "${dir}")
  add_dependencies(nuke-datasets nuke-${dataset_name})
  add_dependencies(nuke-all nuke-${dataset_name})
endfunction()

# A function to check whether or not a given GAMBIT module has been ditched
function(check_module_ditch_status module_name)
  foreach(ditch_command ${itch})
    execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "print(\"${module_name}\".lower().startswith(\"${ditch_command}\".lower()))"
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                    RESULT_VARIABLE result
                    OUTPUT_VARIABLE output)
    if (output STREQUAL "True\n")
      if(NOT ditched_${module_name})
        set(ditched_${module_name} TRUE)
        set(ditched_${module_name} TRUE PARENT_SCOPE)
      endif()
    endif()
  endforeach()
endfunction()


# ===== Add entries for downloadable datasets below ====


# Best-fit SLHA files from the GAMBIT GUT-SUSY study in https://arxiv.org/abs/1705.07935
set(name "best_fits_SLHA_1705_07935")
set(ver "none")
set(dl "https://zenodo.org/record/843496/files/best_fits_SLHA.tar.gz")
set(md5 "none")
set(for_module "ExampleBit_A")
set(dir "${PROJECT_SOURCE_DIR}/${for_module}/data/${name}")
set(dataset_name "dataset-${name}")
check_module_ditch_status(${for_module})
if(NOT ditched_${for_module})
  ExternalProject_Add(${dataset_name}
    DOWNLOAD_COMMAND ${DL_DATASET} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
  )
  add_dataset_nuke(${dataset_name} ${dir})
endif()


