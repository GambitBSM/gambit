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


def _safe_histogram_name(name):
    return name.replace("/", "_").replace(" ", "_")


def _step_values(values):
    if len(values) == 0:
        return values
    return np.r_[values, values[-1]]


def _bin_array(h_data, key, top_level_key=None):
    top_level_key = top_level_key or key
    if top_level_key in h_data:
        return np.array(h_data[top_level_key], dtype=float)
    return np.array([b[key] for b in h_data["bins"]], dtype=float)


def plot_histogram_1d_signal_only(h_data, analysis_name, outdir, fmt, dpi):
    """Plot a single plain 1D histogram."""
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

    safe_name = _safe_histogram_name(h_data["name"])
    outpath = os.path.join(outdir, f"{analysis_name}_{safe_name}.{fmt}")
    fig.savefig(outpath, dpi=dpi, bbox_inches="tight")
    plt.close(fig)
    return outpath


def plot_histogram_1d_signal_region(h_data, analysis_name, outdir, fmt, dpi):
    """Plot a 1D histogram that also carries per-bin SR data."""
    edges = np.array(h_data["edges"], dtype=float)
    nbins = len(edges) - 1

    bins = h_data["bins"][:nbins]
    counts = np.array([b["count"] for b in bins], dtype=float)
    obs = _bin_array(h_data, "n_obs", "obs")[:nbins]
    bkg = _bin_array(h_data, "n_bkg", "bkg")[:nbins]
    bkg_err = _bin_array(h_data, "n_bkg_err", "bkg_err")[:nbins]

    centers = 0.5 * (edges[:-1] + edges[1:])
    obs_err = np.sqrt(np.clip(obs, 0.0, None))

    fig, (ax, rax) = plt.subplots(
        2, 1, figsize=(8, 7), sharex=True,
        gridspec_kw={"height_ratios": [3, 1], "hspace": 0.05}
    )

    bkg_low = np.clip(bkg - bkg_err, 0.0, None)
    bkg_high = bkg + bkg_err
    ax.fill_between(
        edges, _step_values(bkg_low), _step_values(bkg_high),
        step="post", facecolor="lightgray", edgecolor="gray",
        alpha=0.45, hatch="///", label="Uncertainty"
    )
    ax.step(edges, _step_values(bkg), where="post",
            color="tab:blue", linewidth=1.6, label="Background")
    ax.step(edges, _step_values(counts), where="post",
            color="tab:red", linestyle="--", linewidth=1.6, label="Signal")
    ax.errorbar(centers, obs, yerr=obs_err, fmt="o",
                color="black", ecolor="black", elinewidth=1,
                capsize=2, markersize=4, label="Data")

    ax.set_ylabel("Events", fontsize=13)
    ax.set_title(f"{analysis_name}: {h_data['name']}", fontsize=14)
    ax.set_xlim(edges[0], edges[-1])
    ymax = np.max(np.r_[obs + obs_err, bkg_high, counts, 1.0])
    ax.set_ylim(bottom=0, top=1.25 * ymax)
    ax.legend(loc="upper right", fontsize=10)

    valid = bkg > 0.0
    rax.axhline(1.0, color="black", linestyle="--", linewidth=1)
    if np.any(valid):
        ratio_unc = np.full(nbins, np.nan)
        ratio_unc[valid] = bkg_err[valid] / bkg[valid]
        ratio_low = np.clip(1.0 - ratio_unc, 0.0, None)
        ratio_high = 1.0 + ratio_unc
        rax.fill_between(
            edges, _step_values(ratio_low), _step_values(ratio_high),
            step="post", facecolor="lightgray", edgecolor="gray",
            alpha=0.45, hatch="///"
        )

        data_ratio = obs[valid] / bkg[valid]
        data_ratio_err = obs_err[valid] / bkg[valid]
        signal_ratio = np.full(nbins, np.nan)
        signal_ratio[valid] = counts[valid] / bkg[valid]

        rax.errorbar(centers[valid], data_ratio, yerr=data_ratio_err,
                     fmt="o", color="black", ecolor="black",
                     elinewidth=1, capsize=2, markersize=4)
        rax.step(edges, _step_values(signal_ratio), where="post",
                 color="tab:red", linestyle="--", linewidth=1.4)

        ratio_values = np.r_[data_ratio + data_ratio_err, signal_ratio[valid], ratio_high[valid], 1.0]
        ratio_values = ratio_values[np.isfinite(ratio_values)]
        ratio_top = max(1.6, np.max(ratio_values) * 1.15) if ratio_values.size else 1.6
        rax.set_ylim(0.0, ratio_top)
    else:
        rax.set_ylim(0.0, 1.6)

    x_label = h_data.get("x_label", "")
    rax.set_xlabel(x_label if x_label else h_data["name"], fontsize=13)
    rax.set_ylabel("Data / Bkg", fontsize=12)
    rax.set_xlim(edges[0], edges[-1])

    safe_name = _safe_histogram_name(h_data["name"])
    outpath = os.path.join(outdir, f"{analysis_name}_{safe_name}.{fmt}")
    fig.savefig(outpath, dpi=dpi, bbox_inches="tight")
    plt.close(fig)
    return outpath


def plot_histogram_1d(h_data, analysis_name, outdir, fmt, dpi):
    """Plot a single 1D histogram."""
    if h_data.get("is_signal_region", False):
        return plot_histogram_1d_signal_region(h_data, analysis_name, outdir, fmt, dpi)
    return plot_histogram_1d_signal_only(h_data, analysis_name, outdir, fmt, dpi)


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

    safe_name = _safe_histogram_name(h_data["name"])
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
