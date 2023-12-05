"""
Copy documentation
==================

This helps document our code, as we wrap around libraries
that are already documented.
"""


class copydoc:
    def __init__(self, func, prefix=""):
        self.doc = func.__doc__
        self.prefix = prefix

    def __call__(self, func):
        if not self.doc:
            return func

        if not func.__doc__:
            func.__doc__ = self.doc
            return func

        func.__doc__ = ("\n\n").join([func.__doc__, self.prefix + self.doc])
        return func
