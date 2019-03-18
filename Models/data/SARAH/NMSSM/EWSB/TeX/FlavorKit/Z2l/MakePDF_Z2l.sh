#!/bin/bash 
pdflatex Observable_Z2l.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_Z2l.tex 
echo "" 
echo "PDF for Observable Z2l finished" 
echo "Thanks for using SARAH" 
echo "" 
