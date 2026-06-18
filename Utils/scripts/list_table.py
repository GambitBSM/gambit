"""Shared formatting helpers for `make list-backends` / `make list-scanners`.
ANSI codes carry no visible width, so callers that pad table columns around
make_tag()/tag_for_kind() must compute padding from the visible labels."""
import sys


_use_color = sys.stdout.isatty()

YELLOW = "\033[33m" if _use_color else ""
GREEN  = "\033[32m" if _use_color else ""
CYAN   = "\033[36m" if _use_color else ""
DIM    = "\033[2m"  if _use_color else ""
BOLD   = "\033[1m"  if _use_color else ""
RESET  = "\033[0m"  if _use_color else ""

# Status column width: fits the longest label, "[not installed]".
TAG_W = len("[not installed]")

_TAG_LABEL = {
    "disabled":      "[disabled]",
    "installed":     "[installed]",
    "not_installed": "[not installed]",
    "":              "",
}
_TAG_COLOR = {
    "disabled":      YELLOW,
    "installed":     GREEN,
    "not_installed": CYAN,
    "":              "",
}


def make_tag(label, color):
    if not label:
        return " " * TAG_W
    return color + label + RESET + " " * (TAG_W - len(label))


def tag_for_kind(kind):
    return make_tag(_TAG_LABEL[kind], _TAG_COLOR[kind])
