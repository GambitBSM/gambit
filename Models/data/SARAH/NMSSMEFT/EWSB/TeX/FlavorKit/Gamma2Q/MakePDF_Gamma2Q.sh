#!/bin/bash 
pdflatex Observable_Gamma2Q.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_Gamma2Q.tex 
echo "" 
echo "PDF for Observable Gamma2Q finished" 
echo "Thanks for using SARAH" 
echo "" 
