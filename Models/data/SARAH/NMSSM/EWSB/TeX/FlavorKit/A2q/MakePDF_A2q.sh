#!/bin/bash 
pdflatex Observable_A2q.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_A2q.tex 
echo "" 
echo "PDF for Observable A2q finished" 
echo "Thanks for using SARAH" 
echo "" 
