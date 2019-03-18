#!/bin/bash 
pdflatex Observable_PengS4L.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_PengS4L.tex 
echo "" 
echo "PDF for Observable PengS4L finished" 
echo "Thanks for using SARAH" 
echo "" 
