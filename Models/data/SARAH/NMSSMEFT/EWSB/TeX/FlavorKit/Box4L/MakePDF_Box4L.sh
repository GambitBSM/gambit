#!/bin/bash 
pdflatex Observable_Box4L.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_Box4L.tex 
echo "" 
echo "PDF for Observable Box4L finished" 
echo "Thanks for using SARAH" 
echo "" 
