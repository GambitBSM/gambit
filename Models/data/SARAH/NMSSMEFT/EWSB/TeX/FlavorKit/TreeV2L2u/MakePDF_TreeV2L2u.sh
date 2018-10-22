#!/bin/bash 
pdflatex Observable_TreeV2L2u.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_TreeV2L2u.tex 
echo "" 
echo "PDF for Observable TreeV2L2u finished" 
echo "Thanks for using SARAH" 
echo "" 
