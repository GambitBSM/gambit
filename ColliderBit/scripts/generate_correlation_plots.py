import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import argparse
from pathlib import Path
import itertools
import h5py

# Takes an option to do one of three things:

# 'sum' sums the SRs within each analysis then checks the correlation
# 'max' finds the most correlated SRs for each pair of analyses, and plots that
# 'best' uses the best-expected SR within each analysis for the correlation matrix (note we use the same info even for analyses with covariance matrices)

#
# Read data
#

parser = argparse.ArgumentParser(description="Plot unweighted event-acceptance correlations over all CSV rows, including appended batches (not likelihood covariance).")
parser.add_argument("csv", type=Path, help="accepted_events__<collider>__<detector>.csv")
parser.add_argument("option", choices=("sum", "max", "best"))
parser.add_argument("--hdf5", type=Path, help="GAMBIT HDF5 output, required for best mode")
parser.add_argument("--row", type=int, default=0, help="zero-based HDF5 row whose best-SR choices are applied to all CSV events")
parser.add_argument("--output", type=Path, help="output filename prefix")
args = parser.parse_args()
if args.row < 0:
    parser.error("--row must be non-negative")
if args.option == "best" and args.hdf5 is None:
    parser.error("best mode requires --hdf5; --row selects the best-SR choices")
option = args.option
input_csv = args.csv
input_hdf5 = args.hdf5
output_name = str(args.output or args.csv.with_suffix(""))

df_SRs = pd.read_csv(input_csv)
if df_SRs.empty or len(df_SRs.columns) == 0:
    parser.error("CSV contains no completed events or signal regions")
if not df_SRs.columns.str.fullmatch(r"[^:]+::.+__i[0-9]+").all():
    parser.error("CSV columns must be analysis::signal_region__i<index>")
if not df_SRs.isin([0, 1]).all().all():
    parser.error("CSV must contain only 0/1 event-acceptance values")
df_SRs = df_SRs.astype(int)
SR_names = df_SRs.columns

#
# Calculate correlation matrix
#

# Run this code if you want to do the sum

if option=='sum':

    # Make a new dataframe at analysis level by summing the data for all SRs in the given analysis
    df_analyses = df_SRs.T.groupby(df_SRs.columns.str.split('::').str[0], sort=False).sum().T
    analysis_names = df_analyses.columns

    col_names = analysis_names
    df = df_analyses
    
    data = df.to_numpy()
    
    n_cols = len(df.columns)
    correlation_matrix = df.corr()
    correlation_matrix = correlation_matrix.fillna(0)

# Run this code if you want to take the biggest correlation between SRs in each pair of analyses

if option=='max':
    col_info = df_SRs.columns.str.split("::", expand=True)
    df_SRs.columns = pd.MultiIndex.from_tuples(col_info)
    analyses = df_SRs.columns.levels[0]
    correlation_matrix = pd.DataFrame(index=analyses, columns=analyses, dtype=float)

    # Select unique combinations of analyses and obtain correlations between all SRs
    for a1, a2 in itertools.combinations(analyses, 2):
        sub1 = df_SRs[a1]
        sub2 = df_SRs[a2]

        # Get the correlation matrix between the analyses
        corr_temp = pd.concat([sub1, sub2], axis=1, keys=['sub1', 'sub2']).corr().loc['sub2', 'sub1']
        # Set any NaN values to zero
        corr_temp = corr_temp.fillna(0)
        max_corr = corr_temp.abs().max().max()

        correlation_matrix.loc[a1, a2] = max_corr
        # Convert values to float
        correlation_matrix = correlation_matrix.astype(float)

    col_names = analyses
    
    n_cols = len(correlation_matrix.columns)
    
    # Fill missing values from the transpose to make symmetric
    correlation_matrix = correlation_matrix.combine_first(correlation_matrix.T)

    # Set diagonal to 1
    for analysis_name in analyses:
        correlation_matrix.loc[analysis_name, analysis_name] = 1.0

if option=='best':
    col_info = df_SRs.columns.str.split("::", expand=True)
    df_SRs.columns = pd.MultiIndex.from_tuples(col_info)
    analyses = df_SRs.columns.levels[0]
    #print(analyses)
    #analyses = analyses.delete(8) # TODO: Removing CMS_2LEP_soft because I did not simulate it...
    #print(analyses)
    correlation_matrix = pd.DataFrame(index=analyses, columns=analyses, dtype=float)

    # Retrieve the best expected SR index from the relevant HDF5 file
    sr_indices = {}
    with h5py.File(input_hdf5, 'r') as f:
           
        for analysis_name in analyses:
            dataset_path = "/data/#LHC_LogLike_SR_indices @ColliderBit::get_LHC_LogLike_SR_indices::" + analysis_name
            data = f[dataset_path][:]
            if args.row >= len(data):
                parser.error(f"HDF5 dataset for {analysis_name} has no row {args.row}")
            index = int(data[args.row])
            # Match the original SR index in the CSV label, not its column position.
            labels = [name for name in df_SRs[analysis_name].columns if name.endswith(f"__i{index}")]
            if len(labels) != 1:
                parser.error(f"CSV has no unique SR index {index} for {analysis_name}")
            sr_indices[analysis_name] = labels[0]

    # Loop over unique analysis combinations
    for a1, a2 in itertools.combinations(analyses, 2):
        # Retrieve the the SRs for these analyses
        sub1 = df_SRs[a1]
        sub2 = df_SRs[a2]
        # Get the correlation coefficient between the SR data
        best_corr = sub1[sr_indices[a1]].corr(sub2[sr_indices[a2]])
        correlation_matrix.loc[a1, a2] = best_corr
    col_names = analyses
    n_cols = len(correlation_matrix.columns)
    correlation_matrix = correlation_matrix.combine_first(correlation_matrix.T)
    for analysis_name in analyses:
        correlation_matrix.loc[analysis_name, analysis_name] = 1.0
    # Undefined (constant-column) correlations are displayed as zero.
    correlation_matrix = correlation_matrix.fillna(0)

# Output the threshold correlation matrices for later processing - these are still pandas dataframes at this point
corr_above_threshold_005_matrix = (correlation_matrix > 0.05).astype(int)
corr_above_threshold_010_matrix = (correlation_matrix > 0.10).astype(int)
corr_above_threshold_020_matrix = (correlation_matrix > 0.20).astype(int)
corr_above_threshold_005_matrix.to_csv(f"{output_name}__corr_matrix_005.txt", index=False)
corr_above_threshold_010_matrix.to_csv(f"{output_name}__corr_matrix_010.txt", index=False)
corr_above_threshold_020_matrix.to_csv(f"{output_name}__corr_matrix_020.txt", index=False)

#
# Plot correlation
#

# Make numpy versions for plotting
corr_matrix=correlation_matrix.to_numpy()
corr_above_threshold_005_matrix=corr_above_threshold_005_matrix.to_numpy()
corr_above_threshold_010_matrix=corr_above_threshold_010_matrix.to_numpy()
corr_above_threshold_020_matrix=corr_above_threshold_020_matrix.to_numpy()

for r in range(n_cols):
        # for c in range(r, n_cols):
        for c in range(n_cols):
            print(f"({col_names[r]}, {col_names[c]}):  corr: {corr_matrix[r,c]:.4e}")


fig, ax = plt.subplots(figsize=(8,6), layout='constrained')
plt.title("Event correlation")

n_colors = 21
cmin, cmax = -1.0, 1.0
# cmap = matplotlib.colormaps["coolwarm"]
cmap = matplotlib.colormaps["viridis"]
cmap = matplotlib.colors.ListedColormap(cmap(np.linspace(0, 1, n_colors)))
# norm = matplotlib.cm.colors.Normalize(vmin=-1.0, vmax=1.0)
norm = matplotlib.cm.colors.Normalize(vmin=cmin, vmax=cmax)

im = ax.imshow(corr_matrix, cmap=cmap, norm=norm)
cbar = fig.colorbar(im)
cbar.set_label("Correlation", rotation=270)

plt.xticks(range(n_cols), col_names, size=5, rotation=45, ha='right')
plt.yticks(range(n_cols), col_names, size=5)

plt.savefig(f"{output_name}__corr_matrix.png", dpi=300)


# Plot threshold matrices

fig2, ax2 = plt.subplots(figsize=(8,6), layout='constrained')
norm = matplotlib.cm.colors.Normalize(vmin=0.0, vmax=1.0)
im = ax2.imshow(corr_above_threshold_005_matrix, cmap="binary", norm=norm)
plt.xticks(range(n_cols), col_names, size=5, rotation=45, ha='right')
plt.yticks(range(n_cols), col_names, size=5)
plt.title(f"Is correlation greater than 0.05?")
plt.savefig(f"{output_name}__corr_matrix_threshold_005.png", dpi=300)

fig3, ax3 = plt.subplots(figsize=(8,6), layout='constrained')
norm = matplotlib.cm.colors.Normalize(vmin=0.0, vmax=1.0)
im = ax3.imshow(corr_above_threshold_010_matrix, cmap="binary", norm=norm)
plt.xticks(range(n_cols), col_names, size=5, rotation=45, ha='right')
plt.yticks(range(n_cols), col_names, size=5)
plt.title(f"Is correlation greater than 0.10?")
plt.savefig(f"{output_name}__corr_matrix_threshold_010.png", dpi=300)

fig3, ax3 = plt.subplots(figsize=(8,6), layout='constrained')
norm = matplotlib.cm.colors.Normalize(vmin=0.0, vmax=1.0)
im = ax3.imshow(corr_above_threshold_020_matrix, cmap="binary", norm=norm)
plt.xticks(range(n_cols), col_names, size=5, rotation=45, ha='right')
plt.yticks(range(n_cols), col_names, size=5)
plt.title(f"Is correlation greater than 0.20?")
plt.savefig(f"{output_name}__corr_matrix_threshold_020.png", dpi=300)

