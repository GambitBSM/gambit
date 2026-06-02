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
# Arguments:  1. project source directory
#             2. download_location
#             3. cmake command
#             4. cmake download flags (e.g. WITH_AXEL)
#             5. primary URL
#             6. expected md5 sum
#             7. install location
#             8. backend name
#             9. backend version
#             10. retain container folder flag (optional)
#             11. http POST data (optional)
#             12. secondary URL (optional)
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
  $3 -E cmake_echo_color --red --bold "ERROR: Tried to force use of multiple tools, select only one."
  exit 1
fi

# Download
axel_worked=0
suffix=$($3 -E echo $5 | grep -o '\(zip\|tar.gz\|tgz\)')
if [ ! -z ${sufix} ]; then
  suffix=$($3 -E echo $5 | sed 's#.*\.##g')
fi
filename=$8_$9.${suffix}
$3 -E make_directory $2 >/dev/null

# Perform download only if the tarball does not already exist (e.g. it was moved there manually)
if [ ! -f $2/${filename} ]; then
  with_axel=$($3 -E echo $4 | grep -o "WITH_AXEL")
  # Go to wget/curl if axel is not present
  if [ ! -z "${with_axel}" ] && [ "${force_wget}" = "0" ] && [ "${force_curl}" = "0" ]; then
    if command -v axel >/dev/null; then
      # Go to wget/curl if POST data have been provided
      if [ -z "${11}" ]; then
        if $3 -E chdir $2 axel $5 -o $filename; then
          axel_worked=1
        else
          $3 -E echo "Axel failed! The link probably redirects to https. Falling back to wget/curl..."
        fi
      fi
    fi
  fi
  if [ "${axel_worked}" = "0" ]; then
    if [ "${force_axel}" = "1" ]; then
      $3 -E cmake_echo_color --red --bold "ERROR: Forced to use Axel, but Axel is not present or not working. Try another tool."
      exit 1
    fi
    if [ "${force_curl}" = "0" ] && command -v wget >/dev/null; then
      if [ -z "${11}" ]; then
        # Skip certificate checking if requested because KIT, Hepforge, et al often haven't kept them updated
        if [ "${IGNORE_HTTP_CERTIFICATE}" = "1" ]; then
          wget --no-check-certificate $5 -O $2/${filename}
        else
          wget $5 -O $2/${filename}
        fi
      else
        wget --post-data "${11}" ${12} -O $2/${filename}
      fi
      wgetstatus=$?
      if [ ${wgetstatus} != 0 ]; then
        $3 -E cmake_echo_color --red --bold  "ERROR: wget failed to download file"
        case ${wgetstatus} in
          1) $3 -E cmake_echo_color --red --bold  "Generic error code" ;;
          2) $3 -E cmake_echo_color --red --bold  "Parse error" ;;
          3) $3 -E cmake_echo_color --red --bold  "File I/O error" ;;
          4) $3 -E cmake_echo_color --red --bold  "Network failure. Check URL of the backend/scanner." ;;
          5) $3 -E cmake_echo_color --red --bold  "Expired or wrong certificate. To download backend/scanner insecurely, use 'IGNORE_HTTP_CERTIFICATE=1 make <backend/scanner>'" ;;
          6) $3 -E cmake_echo_color --red --bold  "Authentication error" ;;
          7) $3 -E cmake_echo_color --red --bold  "Protocol error" ;;
          8) $3 -E cmake_echo_color --red --bold  "Server issued error response" ;;
        esac
        exit 1
      fi
    elif [ "${force_wget}" = "1" ]; then
      $3 -E cmake_echo_color --red --bold "ERROR: Forced to use wget, but wget is not present or not working. Try another tool."
      exit 1
    elif command -v curl >/dev/null; then
      if [ -z "${11}" ]; then
        $3 -E chdir $2 curl -L -o $2/${filename} $5
      else
        $3 -E chdir $2 curl -L -o $2/${filename} -c $cfile --data "${11}" ${12}
        $3 -E chdir $2 curl -L -o $2/${filename} -b $cfile $5
        $3 -E remove $2/$cfile
      fi
    elif [ "${force_curl}" = "1" ]; then
      $3 -E cmake_echo_color --red --bold "ERROR: Forced to use curl, but curl is not present or not working. Try another tool."
      exit 1
    else
      $3 -E cmake_echo_color --red --bold "ERROR: No axel, no wget, no curl?  What kind of OS are you running anyway?"
      exit 1
    fi
  fi
  # Record the path of the downloaded tarball
  $3 -E echo "$2/${filename}" >> $1/downloaded_tarball_paths.txt
fi
# Check the MD5 sum
if [ "$6" != "none" ]; then
  $3 -E md5sum $2/${filename} |
  {
    read md5 name;
    if [ "${md5}" != "$6" ]; then
      $3 -E cmake_echo_color --red --bold  "ERROR: MD5 sum of downloaded file $2/${filename} does not match"
      $3 -E cmake_echo_color --red --bold  "Expected: $6"
      $3 -E cmake_echo_color --red --bold  "Found:    ${md5}"
      $3 -E cmake_echo_color --red --bold  "Deleting downloaded file."
      # Delete the file if the md5 is bad, and make a stamp saying so, as cmake does not actually check if DOWNLOAD_COMMAND fails.
      $3 -E remove $2/${filename}
      $3 -E touch $8_$9-stamp/$8_$9-download-failed
      exit 1
    fi
  }
fi
# Do the extraction
cd $7
$3 -E tar -xf $2/${filename}
# Get rid of any internal 'container folder' from tarball, unless ${10} has been set
if [ "retain container folder" != "${10}" ]; then
  if [ $(ls -1 | wc -l) = "1" ]; then
    dirname=$(ls)
    if [ -d ${dirname} ]; then
      if cd ${dirname}; then
        mv * ../
        cd ../
        $3 -E remove_directory ${dirname}
      fi
    fi
  fi
fi
