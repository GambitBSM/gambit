import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sys
import itertools
import h5py

# Takes an option to do one of three things:

# 'sum' sums the SRs within each analysis then checks the correlation
# 'max' finds the most correlated SRs for each pair of analyses, and plots that
# 'best' uses the best-expected SR within each analysis for the correlation matrix (note we use the same info even for analyses with covariance matrices)

#
# Read data
#

point = sys.argv[1]
experiment = sys.argv[2]
option = sys.argv[3]

output_name = experiment + "_" + "p" + point
input_csv = experiment + "_analyses/point_" + point + "__" + experiment + ".csv"
input_hdf5 = "DatFiles/CorrelationTest_pt" + point + ".hdf5"

df_SRs = pd.read_csv(input_csv, dtype=int)
SR_names = df_SRs.columns

#
# Calculate correlation matrix
#

# Run this code if you want to do the sum

if option=='sum':

    # Make a new dataframe at analysis level by summing the data for all SRs in the given analysis
    df_analyses = df_SRs.groupby(df_SRs.columns.str.split('::').str[0], axis=1).sum()
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
    np.fill_diagonal(correlation_matrix.values, 1)

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
            sr_indices[analysis_name] = int(data[0])

    # Loop over unique analysis combinations
    for a1, a2 in itertools.combinations(analyses, 2):
        # Retrieve the the SRs for these analyses
        sub1 = df_SRs[a1]
        sub2 = df_SRs[a2]
        # Get the correlation coefficient between the SR data
        best_corr = sub1.iloc[:,sr_indices[a1]].corr(sub2.iloc[:,sr_indices[a2]])
        correlation_matrix.loc[a1, a2] = best_corr
        col_names = analyses
    
        n_cols = len(correlation_matrix.columns)
    
        # Fill missing values from the transpose to make symmetric
        correlation_matrix = correlation_matrix.combine_first(correlation_matrix.T)
        # Set diagonal to 1
        np.fill_diagonal(correlation_matrix.values, 1)
        # Remove nans
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

