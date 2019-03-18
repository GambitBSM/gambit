#!/bin/bash 
pdflatex Observable_H2l.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_H2l.tex 
echo "" 
echo "PDF for Observable H2l finished" 
echo "Thanks for using SARAH" 
echo "" 
