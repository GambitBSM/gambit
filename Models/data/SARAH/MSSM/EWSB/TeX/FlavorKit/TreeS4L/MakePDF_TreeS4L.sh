#!/bin/bash 
pdflatex Observable_TreeS4L.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_TreeS4L.tex 
echo "" 
echo "PDF for Observable TreeS4L finished" 
echo "Thanks for using SARAH" 
echo "" 
