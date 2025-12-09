# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Custom CMake download script for GAMBIT.
#
#  This script serves 2 purposes:
#  1. Gets us around a bug in some versions of
#     cmake distributed in Debian derivatives,
#     which were linked to a version of libcurl
#     compiled without OpenSSL support (and hence
#     fail to download from https addresses).
#  2. Does the download with axel if possible,
#     which is faster than wget or curl because
#     if opens multiple connections to the file
#     server.
#
# Arguments:  1. download_location
#             2. cmake command
#             3. cmake download flags (e.g. WITH_AXEL)
#             4. primary URL
#             5. expected md5 sum
#             6. install location
#             7. backend name
#             8. backend version
#             9. retain container folder flag (optional)
#             10. http POST data (optional)
#             11. secondary URL (optional)
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2016 Jul
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu
#  \date 2019 Feb
#  \date 2020 Feb, May
#
#  \author Patrick Stoecker
#          (stoecker@physik.rwth-aachen.de)
#  \date 2020 Aug
#
#************************************************

# Constants
cfile=cookie

# Force the use of a specific download tool
force_axel=0
force_wget=0
force_curl=0
[ "${FORCE_AXEL}" = "1" ] &&  force_axel=1
[ "${FORCE_WGET}" = "1" ] &&  force_wget=1
[ "${FORCE_CURL}" = "1" ] &&  force_curl=1

if [ $(( ${force_axel} + ${force_wget} + ${force_curl})) -gt 1 ]; then
  $2 -E cmake_echo_color --red --bold "ERROR: Tried to force use of multiple tools, select only one."
  exit 1
fi

download_location=$1
cmake_cmd=$2
download_flags=$3
download_url=$4
download_md5=$5
install_location=$6
package_name=$7
package_version=$8
retain_flag=$9
post_data=${10}
secondary_url=${11}
max_retries=3

suffix=$(${cmake_cmd} -E echo ${download_url} | grep -o '\(zip\|tar.gz\|tgz\)')
if [ -z "${suffix}" ]; then
  suffix=$(${cmake_cmd} -E echo ${download_url} | sed 's#.*\.##g')
fi
filename=${package_name}_${package_version}.${suffix}
target_file=${download_location}/${filename}
${cmake_cmd} -E make_directory ${download_location} >/dev/null

download_file() {
  local url="$1"
  local outfile="$2"
  local post_data="$3"
  local post_url="$4"
  local axel_worked=0
  local with_axel=$(${cmake_cmd} -E echo ${download_flags} | grep -o "WITH_AXEL")

  if [ -n "${with_axel}" ] && [ "${force_wget}" = "0" ] && [ "${force_curl}" = "0" ]; then
    if command -v axel >/dev/null; then
      if [ -z "${post_data}" ]; then
        if ${cmake_cmd} -E chdir ${download_location} axel ${url} -o ${filename}; then
          return 0
        else
          ${cmake_cmd} -E echo "Axel failed! The link probably redirects to https. Falling back to wget/curl..."
        fi
      fi
    fi
  fi

  if [ "${force_axel}" = "1" ]; then
    ${cmake_cmd} -E cmake_echo_color --red --bold "ERROR: Forced to use Axel, but Axel is not present or not working. Try another tool."
    return 1
  fi

  if [ "${force_curl}" = "0" ] && command -v wget >/dev/null; then
    if [ -z "${post_data}" ]; then
      # Skip certificate checking if requested because KIT, Hepforge, et al often haven't kept them updated
      if [ "${IGNORE_HTTP_CERTIFICATE}" = "1" ]; then
        wget --no-check-certificate ${url} -O ${outfile}
      else
        wget ${url} -O ${outfile}
      fi
    else
      wget --post-data "${post_data}" ${post_url} -O ${outfile}
    fi
    wgetstatus=$?
    if [ ${wgetstatus} != 0 ]; then
      ${cmake_cmd} -E cmake_echo_color --red --bold  "ERROR: wget failed to download file"
      case ${wgetstatus} in
        1) ${cmake_cmd} -E cmake_echo_color --red --bold  "Generic error code" ;;
        2) ${cmake_cmd} -E cmake_echo_color --red --bold  "Parse error" ;;
        3) ${cmake_cmd} -E cmake_echo_color --red --bold  "File I/O error" ;;
        4) ${cmake_cmd} -E cmake_echo_color --red --bold  "Network failure. Check URL of the backend/scanner." ;;
        5) ${cmake_cmd} -E cmake_echo_color --red --bold  "Expired or wrong certificate. To download backend/scanner insecurely, use 'IGNORE_HTTP_CERTIFICATE=1 make <backend/scanner>'" ;;
        6) ${cmake_cmd} -E cmake_echo_color --red --bold  "Authentication error" ;;
        7) ${cmake_cmd} -E cmake_echo_color --red --bold  "Protocol error" ;;
        8) ${cmake_cmd} -E cmake_echo_color --red --bold  "Server issued error response" ;;
      esac
      return 1
    fi
    return 0
  elif [ "${force_wget}" = "1" ]; then
    ${cmake_cmd} -E cmake_echo_color --red --bold "ERROR: Forced to use wget, but wget is not present or not working. Try another tool."
    return 1
  elif command -v curl >/dev/null; then
    if [ -z "${post_data}" ]; then
      ${cmake_cmd} -E chdir ${download_location} curl -L -o ${outfile} ${url}
      curlstatus=$?
    else
      ${cmake_cmd} -E chdir ${download_location} curl -L -o ${outfile} -c $cfile --data "${post_data}" ${post_url}
      curlstatus=$?
      if [ ${curlstatus} != 0 ]; then
        return 1
      fi
      ${cmake_cmd} -E chdir ${download_location} curl -L -o ${outfile} -b $cfile ${url}
      curlstatus=$?
      ${cmake_cmd} -E remove ${download_location}/$cfile
    fi
    [ ${curlstatus} = 0 ] && return 0
    return 1
  elif [ "${force_curl}" = "1" ]; then
    ${cmake_cmd} -E cmake_echo_color --red --bold "ERROR: Forced to use curl, but curl is not present or not working. Try another tool."
    return 1
  else
    ${cmake_cmd} -E cmake_echo_color --red --bold "ERROR: No axel, no wget, no curl?  What kind of OS are you running anyway?"
    return 1
  fi
}

attempt_downloads() {
  local url="$1"
  local retries="$2"
  local attempt=1
  while [ ${attempt} -le ${retries} ]; do
    if download_file "${url}" "${target_file}" "${post_data}" "${secondary_url}"; then
      return 0
    fi
    ${cmake_cmd} -E echo "Download attempt ${attempt}/${retries} failed for ${url}"
    ${cmake_cmd} -E remove -f ${target_file}
    attempt=$((attempt + 1))
  done
  return 1
}

# Perform download only if the tarball does not already exist (e.g. it was moved there manually)
if [ ! -f ${target_file} ]; then
  download_success=0

  if attempt_downloads "${download_url}" "${max_retries}"; then
    download_success=1
  elif [ ! -z "${ARCHIVE_URL}" ]; then
    download_url=${ARCHIVE_URL}
    [ ! -z "${ARCHIVE_MD5}" ] && download_md5=${ARCHIVE_MD5}
    ${cmake_cmd} -E echo "Using archived backup: ${download_url}"
    if attempt_downloads "${download_url}" "${max_retries}"; then
      download_success=1
    fi
  fi

  if [ "${download_success}" -ne 1 ]; then
    ${cmake_cmd} -E cmake_echo_color --red --bold "ERROR: Failed to download file after ${max_retries} attempt(s)."
    exit 1
  fi
fi
# Check the MD5 sum
if [ "${download_md5}" != "none" ]; then
  ${cmake_cmd} -E md5sum ${target_file} |
  {
    read md5 name;
    if [ "${md5}" != "${download_md5}" ]; then
      ${cmake_cmd} -E cmake_echo_color --red --bold  "ERROR: MD5 sum of downloaded file ${target_file} does not match"
      ${cmake_cmd} -E cmake_echo_color --red --bold  "Expected: ${download_md5}"
      ${cmake_cmd} -E cmake_echo_color --red --bold  "Found:    ${md5}"
      ${cmake_cmd} -E cmake_echo_color --red --bold  "Deleting downloaded file."
      # Delete the file if the md5 is bad, and make a stamp saying so, as cmake does not actually check if DOWNLOAD_COMMAND fails.
      ${cmake_cmd} -E remove ${target_file}
      ${cmake_cmd} -E touch ${package_name}_${package_version}-stamp/${package_name}_${package_version}-download-failed
      exit 1
    fi
  }
fi
# Do the extraction
cd ${install_location}
${cmake_cmd} -E tar -xf ${target_file}
# Get rid of any internal 'container folder' from tarball, unless $9 has been set
if [ "retain container folder" != "${retain_flag}" ]; then
  if [ $(ls -1 | wc -l) = "1" ]; then
    dirname=$(ls)
    if [ -d ${dirname} ]; then
      if cd ${dirname}; then
        mv * ../
        cd ../
        ${cmake_cmd} -E remove_directory ${dirname}
      fi
    fi
  fi
fi
