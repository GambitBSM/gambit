#!/bin/bash 
pdflatex Observable_PengV4L.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_PengV4L.tex 
echo "" 
echo "PDF for Observable PengV4L finished" 
echo "Thanks for using SARAH" 
echo "" 
