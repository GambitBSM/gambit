#!/bin/bash 
pdflatex Observable_TreeV2d2nu.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_TreeV2d2nu.tex 
echo "" 
echo "PDF for Observable TreeV2d2nu finished" 
echo "Thanks for using SARAH" 
echo "" 
