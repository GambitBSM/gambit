#!/bin/bash 
pdflatex Observable_TreeV2d2L.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_TreeV2d2L.tex 
echo "" 
echo "PDF for Observable TreeV2d2L finished" 
echo "Thanks for using SARAH" 
echo "" 
