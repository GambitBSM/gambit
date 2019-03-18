#!/bin/bash 
pdflatex Observable_PengV2d2nu.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_PengV2d2nu.tex 
echo "" 
echo "PDF for Observable PengV2d2nu finished" 
echo "Thanks for using SARAH" 
echo "" 
