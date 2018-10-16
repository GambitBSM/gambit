set title "SingletDMZ3 renormalization group flow"
set xlabel "renormalization scale / GeV"
set logscale x

if (!exists("filename")) filename='SingletDMZ3_rgflow.dat'

plot for [i=2:37+1] filename using 1:(column(i)) title columnhead(i)
