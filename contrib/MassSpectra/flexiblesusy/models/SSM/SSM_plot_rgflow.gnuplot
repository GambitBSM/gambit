set title "SSM renormalization group flow"
set xlabel "renormalization scale / GeV"
set logscale x

if (!exists("filename")) filename='SSM_rgflow.dat'

plot for [i=2:39+1] filename using 1:(column(i)) title columnhead(i)
