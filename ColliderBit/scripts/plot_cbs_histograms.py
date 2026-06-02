#!/usr/bin/env python3
"""
Plot histograms from CBS (ColliderBit Solo) JSON output.

Reads the structured JSON output produced by CBS and creates
matplotlib plots for all 1D and 2D histograms.

Usage:
    python plot_cbs_histograms.py CBS_output.json
    python plot_cbs_histograms.py CBS_output.json --analysis ATLAS_EXOT_2019_04
    python plot_cbs_histograms.py CBS_output.json --outdir plots/ --format png --dpi 200

Requirements:
    matplotlib, numpy
"""

import argparse
import json
import os
import sys

try:
    import matplotlib.pyplot as plt
    import numpy as np
except ImportError as e:
    print(f"Error: {e}")
    print("Please install matplotlib and numpy: pip install matplotlib numpy")
    sys.exit(1)


def plot_histogram_1d(h_data, analysis_name, outdir, fmt, dpi):
    """Plot a single 1D histogram."""
    edges = np.array(h_data["edges"])
    nbins = len(edges) - 1

    counts = np.array([b["count"] for b in h_data["bins"][:nbins]])
    errors = np.array([b["error"] for b in h_data["bins"][:nbins]])

    centers = 0.5 * (edges[:-1] + edges[1:])
    widths = edges[1:] - edges[:-1]

    fig, ax = plt.subplots(figsize=(8, 6))

    # Draw histogram as step plot with error bars
    ax.bar(centers, counts, width=widths, edgecolor="black",
           linewidth=0.5, alpha=0.7, color="steelblue", label="Signal (scaled)")
    ax.errorbar(centers, counts, yerr=errors, fmt="none", ecolor="black",
                elinewidth=1, capsize=2)

    x_label = h_data.get("x_label", "")
    ax.set_xlabel(x_label if x_label else h_data["name"], fontsize=13)
    ax.set_ylabel("Events", fontsize=13)
    ax.set_title(f"{analysis_name}: {h_data['name']}", fontsize=14)

    # Annotate under/overflow and integral
    uf = h_data.get("underflow", 0.0)
    of = h_data.get("overflow", 0.0)
    integral = h_data.get("integral", 0.0)
    info_lines = [f"Integral: {integral:.2f}"]
    if uf > 0:
        info_lines.append(f"Underflow: {uf:.2f}")
    if of > 0:
        info_lines.append(f"Overflow: {of:.2f}")
    ax.text(0.97, 0.95, "\n".join(info_lines),
            transform=ax.transAxes, fontsize=9,
            verticalalignment="top", horizontalalignment="right",
            bbox=dict(boxstyle="round,pad=0.3", facecolor="wheat", alpha=0.5))

    ax.set_xlim(edges[0], edges[-1])
    ax.set_ylim(bottom=0)
    ax.legend(loc="upper left", fontsize=10)

    safe_name = h_data["name"].replace("/", "_").replace(" ", "_")
    outpath = os.path.join(outdir, f"{analysis_name}_{safe_name}.{fmt}")
    fig.savefig(outpath, dpi=dpi, bbox_inches="tight")
    plt.close(fig)
    return outpath


def plot_histogram_2d(h_data, analysis_name, outdir, fmt, dpi):
    """Plot a single 2D histogram as a color mesh."""
    x_edges = np.array(h_data["x_edges"])
    y_edges = np.array(h_data["y_edges"])
    counts = np.array(h_data["counts"])

    fig, ax = plt.subplots(figsize=(8, 6))
    mesh = ax.pcolormesh(x_edges, y_edges, counts.T, cmap="viridis", shading="flat")
    fig.colorbar(mesh, ax=ax, label="Events")

    x_label = h_data.get("x_label", "x")
    y_label = h_data.get("y_label", "y")
    ax.set_xlabel(x_label, fontsize=13)
    ax.set_ylabel(y_label, fontsize=13)
    ax.set_title(f"{analysis_name}: {h_data['name']}", fontsize=14)

    integral = h_data.get("integral", 0.0)
    ax.text(0.97, 0.95, f"Integral: {integral:.2f}",
            transform=ax.transAxes, fontsize=9,
            verticalalignment="top", horizontalalignment="right",
            bbox=dict(boxstyle="round,pad=0.3", facecolor="wheat", alpha=0.5))

    safe_name = h_data["name"].replace("/", "_").replace(" ", "_")
    outpath = os.path.join(outdir, f"{analysis_name}_{safe_name}_2d.{fmt}")
    fig.savefig(outpath, dpi=dpi, bbox_inches="tight")
    plt.close(fig)
    return outpath


def main():
    parser = argparse.ArgumentParser(
        description="Plot CBS histogram output",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    parser.add_argument("json_file", help="CBS JSON output file")
    parser.add_argument("--analysis", default=None,
                        help="Plot only this analysis (default: all)")
    parser.add_argument("--outdir", default="plots",
                        help="Output directory (default: plots/)")
    parser.add_argument("--format", default="pdf",
                        choices=["pdf", "png", "svg"],
                        help="Output image format (default: pdf)")
    parser.add_argument("--dpi", type=int, default=150,
                        help="DPI for raster formats (default: 150)")
    parser.add_argument("--list", action="store_true",
                        help="List available histograms and exit")
    args = parser.parse_args()

    with open(args.json_file) as f:
        data = json.load(f)

    analyses = data.get("analyses", {})

    if args.list:
        for aname, adata in analyses.items():
            histograms = adata.get("histograms", {})
            h1ds = histograms.get("1d", [])
            h2ds = histograms.get("2d", [])
            if h1ds or h2ds:
                print(f"\n{aname}:")
                for h in h1ds:
                    print(f"  [1D] {h['name']}  ({h['nbins']} bins, "
                          f"integral={h.get('integral', 0):.2f})")
                for h in h2ds:
                    print(f"  [2D] {h['name']}  ({h['nx_bins']}x{h['ny_bins']} bins, "
                          f"integral={h.get('integral', 0):.2f})")
        return

    os.makedirs(args.outdir, exist_ok=True)

    n_plotted = 0
    for analysis_name, analysis_data in analyses.items():
        if args.analysis and analysis_name != args.analysis:
            continue

        histograms = analysis_data.get("histograms", {})

        for h1d in histograms.get("1d", []):
            if not h1d.get("bins"):
                continue
            path = plot_histogram_1d(h1d, analysis_name, args.outdir, args.format, args.dpi)
            print(f"  Wrote: {path}")
            n_plotted += 1

        for h2d in histograms.get("2d", []):
            if not h2d.get("counts"):
                continue
            path = plot_histogram_2d(h2d, analysis_name, args.outdir, args.format, args.dpi)
            print(f"  Wrote: {path}")
            n_plotted += 1

    if n_plotted == 0:
        print("No histograms found in JSON output.")
        print("Make sure check_histogram: true is set in your CBS YAML.")
    else:
        print(f"\nPlotted {n_plotted} histogram(s) to {args.outdir}/")


if __name__ == "__main__":
    main()
