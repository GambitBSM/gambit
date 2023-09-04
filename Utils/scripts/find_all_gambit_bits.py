#!/usr/bin/env python

import os
import yaml
import argparse


def get_bits_from_directory_list(gambit_directory):
    """Get Gambit Bits.

    Return a sorted list of directory names with "Bit" in the name. 
    This effectively generates a list of all available Bits in Gambit based on the established nameing scheme inside the Gambit repository.

    Args:
        gambit_directory (str): Directory to search in. To work properly this has to be the Gambit source directory.

    Returns:
        list: sorted list of Gambit Bits, except ScannerBit
    """
    return sorted(set([directory for directory in os.listdir(gambit_directory) if "Bit" in directory and "ScannerBit" not in directory and os.path.isdir(directory)]))


def write_list_to_yaml(list_of_bits, output_file, yaml_key="gambit_bits"):
    """Write given list to a yaml file.

    Args:
        list_of_bits list(str): List of Gambit Bits.
        output_file (str): Path/name for the output file.
        yaml_key (str): Key which is used to write the yaml file.
    """
    with open(output_file, "w+") as f:
        yaml.dump({
            yaml_key: list_of_bits
        }, f)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="""Generates a list of all available Gambit Bits which can be used by the Gambit cmake and diagnostic systems.""")
    parser.add_argument("--source-dir", required=True, help="Source directory of the Gambit repository.")
    parser.add_argument("--output-file", required=True, help="Output path for the generated yaml file containing the list of Bits. Recommended to place the file in config/gambit_bits.yaml.")
    args = parser.parse_args()

    write_list_to_yaml(
        get_bits_from_directory_list(args.source_dir),
        args.output_file
        )
