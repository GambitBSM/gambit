set title "MSSMNoFVatMGUT renormalization group flow"
set xlabel "renormalization scale / GeV"
set logscale x

if (!exists("filename")) filename='MSSMNoFVatMGUT_rgflow.dat'

plot for [i=2:111+1] filename using 1:(column(i)) title columnhead(i)
