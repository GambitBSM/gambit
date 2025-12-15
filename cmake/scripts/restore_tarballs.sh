#!/bin/bash
# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Script to restore downloaded tarballs from a central location.
#
#  This script reads paths from the consolidated
#  downloaded_tarballs/downloaded_tarball_paths_all.txt file and
#  copies each tarball from the downloaded_tarballs folder
#  back to its original location.
#
#  Usage: ./restore_tarballs.sh
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Claude Code
#  \date 2025 Dec
#
#************************************************

# Set colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Source directory
SOURCE_DIR="downloaded_tarballs"

# Consolidated paths file
PATHS_FILE="${SOURCE_DIR}/downloaded_tarball_paths_all.txt"

# Check if source directory exists
if [ ! -d "${SOURCE_DIR}" ]; then
  echo -e "${RED}ERROR: Source directory ${SOURCE_DIR} not found.${NC}"
  echo "Please ensure the downloaded_tarballs folder exists."
  echo "Run copy_tarballs.sh first to create it."
  exit 1
fi

# Check if paths file exists
if [ ! -f "${PATHS_FILE}" ]; then
  echo -e "${RED}ERROR: Paths file ${PATHS_FILE} not found.${NC}"
  echo "Please run copy_tarballs.sh first to create the consolidated paths file."
  exit 1
fi

# Check if paths file is empty
if [ ! -s "${PATHS_FILE}" ]; then
  echo -e "${YELLOW}WARNING: Paths file ${PATHS_FILE} is empty. No tarballs to restore.${NC}"
  exit 0
fi

echo -e "${BLUE}Restoring tarballs from ${SOURCE_DIR}/ to original locations${NC}"
echo -e "${BLUE}Using paths file: ${PATHS_FILE}${NC}"
echo "---------------------------------------------------"

# Initialize counters
copied=0
skipped=0
failed=0
missing=0

# Read file line by line
while IFS= read -r tarball_path || [ -n "${tarball_path}" ]; do
  # Skip empty lines
  [ -z "${tarball_path}" ] && continue

  # Strip any trailing whitespace or carriage returns
  tarball_path=$(echo "${tarball_path}" | tr -d '\r' | sed 's/[[:space:]]*$//')

  # Get just the filename
  filename=$(basename "${tarball_path}")

  # Get the directory path
  dest_dir=$(dirname "${tarball_path}")

  # Source file in the downloaded_tarballs folder
  source_file="${SOURCE_DIR}/${filename}"

  # Check if source file exists in downloaded_tarballs
  if [ ! -f "${source_file}" ]; then
    echo -e "${YELLOW}⊘ Not in backup: ${filename}${NC}"
    ((missing++))
    continue
  fi

  # Check if destination file already exists
  if [ -f "${tarball_path}" ]; then
    echo -e "${YELLOW}⊙ Already exists: ${tarball_path}${NC}"
    ((skipped++))
    continue
  fi

  # Create destination directory if it doesn't exist
  if [ ! -d "${dest_dir}" ]; then
    echo -e "${GREEN}  Creating directory: ${dest_dir}${NC}"
    mkdir -p "${dest_dir}"
    if [ $? -ne 0 ]; then
      echo -e "${RED}✗ Failed to create directory: ${dest_dir}${NC}"
      ((failed++))
      continue
    fi
  fi

  # Copy the file to its original location
  cp "${source_file}" "${tarball_path}"
  if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Restored: ${tarball_path}${NC}"
    ((copied++))
  else
    echo -e "${RED}✗ Failed to restore: ${tarball_path}${NC}"
    ((failed++))
  fi

done < "${PATHS_FILE}"

# Print summary
echo "---------------------------------------------------"
echo -e "${GREEN}Summary:${NC}"
echo "  Restored:      ${copied}"
echo "  Skipped:       ${skipped}"
echo "  Missing:       ${missing}"
echo "  Failed:        ${failed}"

if [ ${failed} -gt 0 ]; then
  exit 1
else
  exit 0
fi
