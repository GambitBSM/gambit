#!/bin/bash 
pdflatex Observable_PengS2d2nu.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_PengS2d2nu.tex 
echo "" 
echo "PDF for Observable PengS2d2nu finished" 
echo "Thanks for using SARAH" 
echo "" 
