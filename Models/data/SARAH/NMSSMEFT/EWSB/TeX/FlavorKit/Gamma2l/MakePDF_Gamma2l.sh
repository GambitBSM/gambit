#!/bin/bash 
pdflatex Observable_Gamma2l.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_Gamma2l.tex 
echo "" 
echo "PDF for Observable Gamma2l finished" 
echo "Thanks for using SARAH" 
echo "" 
