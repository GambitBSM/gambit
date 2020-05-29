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
#  \date 2020 May
#
#************************************************

# Constants
cfile=cookie

# Download
axel_worked=0
filename=$($2 -E echo $4 | sed 's#.*/##g')
$2 -E make_directory $1 >/dev/null
with_axel=$($2 -E echo $3 | grep -o "WITH_AXEL")
# Go to wget/curl if axel is not present
if [ ! -z "${with_axel}" ]; then
  if command -v axel >/dev/null; then
    # Go to wget/curl if POST data have been provided
    if [ -z "$10" ]; then
      if $2 -E chdir $1 axel $4 -o $filename; then
        axel_worked=1
      else
        $2 -E echo "Axel failed! The link probably redirects to https. Falling back to wget/curl..."
      fi
    fi
  fi
fi
if [ "${axel_worked}" = "0" ]; then
  if command -v wget >/dev/null; then
    if [ -z "$10" ]; then
      # Skip certificate checking if requested because KIT, Hepforge, et al often haven't kept them updated
      if [ "${IGNORE_HTTP_CERTIFICATE}" = "1" ]; then
        wget --no-check-certificate $4 -O $i/${filename}
      else
        wget $4 -O $1/${filename}
      fi
    else
      wget --post-data "$10" ${11} -O $1/${filename}
    fi
    wgetstatus=$?
    if [ ${wgetstatus} != 0 ]; then
      $2 -E cmake_echo_color --red --bold  "ERROR: wget failed to download file"
      case ${wgetstatus} in
        1) $2 -E cmake_echo_color --red --bold  "Generic error code" ;;
        2) $2 -E cmake_echo_color --red --bold  "Parse error" ;;
        3) $2 -E cmake_echo_color --red --bold  "File I/O error" ;;
        4) $2 -E cmake_echo_color --red --bold  "Network failure. Check url of the backend" ;;
        5) $2 -E cmake_echo_color --red --bold  "Expired or wrong certificate. To download backend insecurely, use 'IGNORE_HTTP_CERTIFICATE=1 make <backend>'" ;;
        6) $2 -E cmake_echo_color --red --bold  "Authentication error" ;;
        7) $2 -E cmake_echo_color --red --bold  "Protocol error" ;;
        8) $2 -E cmake_echo_color --red --bold  "Server issued error response" ;;
      esac
      exit 1
    fi
  elif command -v curl >/dev/null; then
    if [ -z "$10" ]; then
      $2 -E chdir $1 curl -L -O $4
    else
      $2 -E chdir $1 curl -L -O -c $cfile --data "$10" ${11}
      $2 -E chdir $1 curl -L -O -b $cfile $4
      $2 -E remove $1/$cfile
    fi
  else
    $2 -E cmake_echo_color --red --bold "ERROR: No axel, no wget, no curl?  What kind of OS are you running anyway?"
    exit 1
  fi
fi
# Check the MD5 sum
$2 -E md5sum $1/${filename} |
{
  read md5 name;
  if [ "${md5}" != "$5" ]; then
    $2 -E cmake_echo_color --red --bold  "ERROR: MD5 sum of downloaded file $1/${filename} does not match"
    $2 -E cmake_echo_color --red --bold  "Expected: $5"
    $2 -E cmake_echo_color --red --bold  "Found:    ${md5}"
    $2 -E cmake_echo_color --red --bold  "Deleting downloaded file."
    # Delete the file if the md5 is bad, and make a stamp saying so, as cmake does not actually check if DOWNLOAD_COMMAND fails.
    $2 -E remove $1/${filename}
    $2 -E touch $7_$8-stamp/$7_$8-download-failed
    exit 1
  fi
}
# Do the extraction
cd $6
$2 -E tar -xf $1/${filename}
# Get rid of any internal 'container folder' from tarball, unless $9 has been set
if [ "retain container folder" != "$9" ]; then
  if [ $(ls -1 | wc -l) = "1" ]; then
    dirname=$(ls)
    if cd ${dirname}; then
      mv * ../
      cd ../
      $2 -E remove_directory ${dirname}
    fi
  fi
fi
