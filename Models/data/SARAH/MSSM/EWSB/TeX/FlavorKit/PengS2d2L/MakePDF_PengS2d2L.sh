#!/bin/bash 
pdflatex Observable_PengS2d2L.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_PengS2d2L.tex 
echo "" 
echo "PDF for Observable PengS2d2L finished" 
echo "Thanks for using SARAH" 
echo "" 
