#!/bin/bash 
pdflatex Observable_H2q.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_H2q.tex 
echo "" 
echo "PDF for Observable H2q finished" 
echo "Thanks for using SARAH" 
echo "" 
