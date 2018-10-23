#!/bin/bash 
pdflatex Observable_Box4d.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_Box4d.tex 
echo "" 
echo "PDF for Observable Box4d finished" 
echo "Thanks for using SARAH" 
echo "" 
