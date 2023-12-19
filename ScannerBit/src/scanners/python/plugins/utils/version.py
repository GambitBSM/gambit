"""
Obtain version of a module
==========================

Expected usuage e.g.,

    import numpy as np
    version(np)
"""

import importlib.metadata

def version(mod):

    try:
        return importlib.metadata.version(mod)
    except TypeError:
        pass

    try:
        return importlib.metadata.version(mod.__name__)
    except (TypeError, importlib.metadata.PackageNotFoundError):
        pass

    try:
        return mod.__version__
    except AttributeError:
        pass

    return None
