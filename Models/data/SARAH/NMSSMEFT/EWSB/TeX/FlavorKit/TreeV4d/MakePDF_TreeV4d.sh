#!/bin/bash 
pdflatex Observable_TreeV4d.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_TreeV4d.tex 
echo "" 
echo "PDF for Observable TreeV4d finished" 
echo "Thanks for using SARAH" 
echo "" 
