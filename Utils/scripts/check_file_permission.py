#!/usr/bin/env python

import os
import sys
import argparse

FILE_EXTENSIONS = ['.c', '.h', '.C', '.H', '.cpp', '.hpp', '.cc', '.hh', '.c++', '.h++', '.cxx', '.hxx']
PERMISSION = 0o100664  # Commonly known as 664


def extract_extension_and_permission(path_to_file):
    """Get the file extension and permission in octal representation from the given file.

    Args:
        path_to_file (str): Absolute file path.

    Returns:
        tuple: file extension .xyz, file permission in octal representation
    """
    octal_permission = oct(os.stat(path_to_file).st_mode)
    _, file_extension = os.path.splitext(path_to_file)
    return file_extension, octal_permission


def fix_file(path_to_file, verbose):
    """Fix the file permission to 664.

    Args:
        path_to_file (str): Absolute file path.
        verbose (bool): Print user information

    Returns:
        0
    """
    file_extension, octal_permission = extract_extension_and_permission(path_to_file)
    if (file_extension in FILE_EXTENSIONS) and (octal_permission != oct(PERMISSION)):
        if verbose:
            print("Changing file permission of {} to 664".format(path_to_file))
        os.chmod(path_to_file, PERMISSION)
    else:
        if verbose:
            print("File permission of {} already set to 664".format(path_to_file))
    return 0


def check_file(path_to_file, verbose):
    """Fix the file permission to 664.

    Args:
        path_to_file (str): Absolute file path.
        verbose (bool): Print user information

    Returns:
        bool: 1 if file has not correct permission, 0 if file has correct permission.
    """
    file_extension, octal_permission = extract_extension_and_permission(path_to_file)
    if (file_extension in FILE_EXTENSIONS) and (octal_permission != oct(PERMISSION)):
        if verbose:
            print("{} has wrong file permission. Please run chmod 664 {}".format(path_to_file, path_to_file))
        return 1
    return 0


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="""Check the file permission of the given file and exit with error code in case it is not set properly.""")
    parser.add_argument('file', nargs='+')
    parser.add_argument("--fix-permission", action="store_true", help="Automatically fix file permission.")
    parser.add_argument("--verbose", action="store_true", help="Print user help message.")
    args = parser.parse_args()

    if args.fix_permission:
        sys.exit(any([fix_file(f, args.verbose) for f in args.file]))
    else:
        sys.exit(any([check_file(f, args.verbose) for f in args.file]))
