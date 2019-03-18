#!/bin/bash 
pdflatex Observable_TreeS4d.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_TreeS4d.tex 
echo "" 
echo "PDF for Observable TreeS4d finished" 
echo "Thanks for using SARAH" 
echo "" 
