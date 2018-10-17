
# Arguments:
#   1. BOSS directory
#   2. cmake command
#   3. primary URL
#   4. file name of downloaded file

# Source for prebuilt castxml binaries
#  https://data.kitware.com/api/v1/file/57b5dea08d777f10f2696379/download  (castxml-linux.tar.gz)
#  https://data.kitware.com/api/v1/file/57b5de9f8d777f10f2696378/download  (castxml-macosx.tar.gz)



if ! [ -d $1/castxml ] ; then

  echo "Did not find the castxml directory in ${1}/castxml. Will try to download castxml now."

  # Download
  axel_worked=0
  $2 -E make_directory $1 >/dev/null
  # Go to wget/curl if axel is not present
  if command -v axel >/dev/null; then
    if $2 -E chdir $1 axel --output=$1/$4 $3; then
      axel_worked=1
    else
      $2 -E echo "Axel failed! The link probably redirects to https. Falling back to wget/curl..."
    fi
  fi
  if [ "${axel_worked}" = "0" ]; then
    if command -v wget >/dev/null; then
      wget --output-document=$1/$4 $3 
    elif command -v curl >/dev/null; then
      $2 -E chdir $1 curl -o $1/$4 $3
    else
      $2 -E cmake_echo_color --red --bold "ERROR: No axel, no wget, no curl?  What kind of OS are you running anyway?"
      exit 1
    fi
  fi

  # Do the extraction
  $2 -E echo "Extracting $1/$4"
  cd $1
  $2 -E tar -xf $1/$4

fi


