#!/bin/bash 
pdflatex Observable_TreeV4L.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_TreeV4L.tex 
echo "" 
echo "PDF for Observable TreeV4L finished" 
echo "Thanks for using SARAH" 
echo "" 
