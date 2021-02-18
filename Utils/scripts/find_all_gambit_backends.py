#!/usr/bin/env python

import os
import yaml
import argparse


def get_backends_from_directory_list(gambit_directory):
    """Get Gambit Backends.

    Return a dictionary which contains all Backends listed in "Backends/installed" with their available versions.
    This effectively generates a dictionary of all available Backends + Version in Gambit based on the established structure inside the Gambit repository.

    Args:
        gambit_directory (str): Directory to search in. To work properly this has to be the Gambit source directory.

    Returns:
        dict: dictionary with backends as key and a list with version as value

    """
    directory_with_available_backends = os.path.join(gambit_directory, "Backends", "installed")

    backends = {}
    for backend in os.listdir(directory_with_available_backends):
        directory_with_available_versions = os.path.join(directory_with_available_backends, backend)
        backends[backend] = [version for version in os.listdir(directory_with_available_versions)]

    return backends


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="""Generates a dictionary of all available Gambit Backends which can be used by the Gambit cmake and diagnostic systems.""")
    parser.add_argument("--source-dir", required=True, help="Source directory of the Gambit repository.")
    parser.add_argument("--output-file", required=True, help="Output path for the generated yaml file containing the list of Backends. Recommended to place the file in config/gambit_backends.yaml.")
    args = parser.parse_args()

    with open(args.output_file, "w+") as f:
        yaml.dump(get_backends_from_directory_list(args.source_dir), f)
