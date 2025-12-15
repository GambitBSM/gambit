#!/bin/bash
# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Script to copy downloaded tarballs to a central location.
#
#  This script automatically finds all downloaded_tarball_paths.txt
#  files in the repository, copies each tarball to the
#  downloaded_tarballs folder, and creates a single consolidated
#  downloaded_tarball_paths.txt file for later restoration.
#
#  Usage: ./copy_tarballs.sh [search_directory]
#
#  If search_directory is not provided, searches from current directory.
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

# Store the directory from which the script was run
BASE_DIR="$(pwd)"

# Search directory (default to current directory)
SEARCH_DIR="${1:-.}"

# Output directory
OUTPUT_DIR="downloaded_tarballs"

# Consolidated paths file
CONSOLIDATED_PATHS="${OUTPUT_DIR}/downloaded_tarball_paths_all.txt"

# Check if search directory exists
if [ ! -d "${SEARCH_DIR}" ]; then
  echo -e "${RED}ERROR: Directory ${SEARCH_DIR} not found.${NC}"
  echo "Usage: $0 [search_directory]"
  exit 1
fi

# Find all downloaded_tarball_paths.txt files
echo -e "${BLUE}Searching for downloaded_tarball_paths.txt files in ${SEARCH_DIR}...${NC}"
mapfile -t INPUT_FILES < <(find "${SEARCH_DIR}" -name "downloaded_tarball_paths.txt" -type f 2>/dev/null)

# Check if any files were found
if [ ${#INPUT_FILES[@]} -eq 0 ]; then
  echo -e "${YELLOW}WARNING: No downloaded_tarball_paths.txt files found in ${SEARCH_DIR}${NC}"
  exit 0
fi

echo -e "${GREEN}Found ${#INPUT_FILES[@]} file(s)${NC}"
echo ""

# Create output directory if it doesn't exist
if [ ! -d "${OUTPUT_DIR}" ]; then
  echo -e "${GREEN}Creating directory: ${OUTPUT_DIR}${NC}"
  mkdir -p "${OUTPUT_DIR}"
  if [ $? -ne 0 ]; then
    echo -e "${RED}ERROR: Failed to create directory ${OUTPUT_DIR}${NC}"
    exit 1
  fi
fi

# Initialize the consolidated paths file (empty it if it exists)
> "${CONSOLIDATED_PATHS}"

# Initialize total counters
total_copied=0
total_skipped=0
total_failed=0
total_paths_written=0

# Process each file
for INPUT_FILE in "${INPUT_FILES[@]}"; do
  echo -e "${BLUE}Processing: ${INPUT_FILE}${NC}"
  echo "---------------------------------------------------"

  # Check if input file is empty
  if [ ! -s "${INPUT_FILE}" ]; then
    echo -e "${YELLOW}  File is empty, skipping${NC}"
    echo ""
    continue
  fi

  # Initialize counters for this file
  copied=0
  skipped=0
  failed=0

  # Read file line by line
  while IFS= read -r tarball_path || [ -n "${tarball_path}" ]; do
    # Skip empty lines
    [ -z "${tarball_path}" ] && continue

    # Strip any trailing whitespace or carriage returns
    tarball_path=$(echo "${tarball_path}" | tr -d '\r' | sed 's/[[:space:]]*$//')

    # Check if file exists
    if [ ! -f "${tarball_path}" ]; then
      echo -e "${RED}  ✗ File not found: ${tarball_path}${NC}"
      ((failed++))
      continue
    fi

    # Get just the filename
    filename=$(basename "${tarball_path}")

    # Convert to relative path from the base directory
    relative_path=$(realpath --relative-to="${BASE_DIR}" "${tarball_path}")

    # Check if file already exists in destination
    if [ -f "${OUTPUT_DIR}/${filename}" ]; then
      echo -e "${YELLOW}  ⊙ Already exists: ${filename}${NC}"
      ((skipped++))
      # Still write to consolidated file since this path is valid
      echo "${relative_path}" >> "${CONSOLIDATED_PATHS}"
      ((total_paths_written++))
      continue
    fi

    # Copy the file
    cp "${tarball_path}" "${OUTPUT_DIR}/"
    if [ $? -eq 0 ]; then
      echo -e "${GREEN}  ✓ Copied: ${filename}${NC}"
      ((copied++))
      # Write the relative path to the consolidated file
      echo "${relative_path}" >> "${CONSOLIDATED_PATHS}"
      ((total_paths_written++))
    else
      echo -e "${RED}  ✗ Failed to copy: ${tarball_path}${NC}"
      ((failed++))
    fi

  done < "${INPUT_FILE}"

  # Update totals
  ((total_copied += copied))
  ((total_skipped += skipped))
  ((total_failed += failed))

  # Print file summary
  echo "  File summary: Copied: ${copied}, Skipped: ${skipped}, Failed: ${failed}"
  echo ""
done

# Print total summary
echo "==================================================="
echo -e "${GREEN}Total Summary:${NC}"
echo "  Files processed:       ${#INPUT_FILES[@]}"
echo "  Copied:                ${total_copied}"
echo "  Skipped:               ${total_skipped}"
echo "  Failed:                ${total_failed}"
echo ""
echo -e "${GREEN}Created consolidated paths file:${NC}"
echo "  ${CONSOLIDATED_PATHS}"
echo "  Paths recorded:        ${total_paths_written}"

if [ ${total_failed} -gt 0 ]; then
  exit 1
else
  exit 0
fi
