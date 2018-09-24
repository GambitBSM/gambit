#!/bin/bash 
pdflatex Observable_Box4Lcross.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_Box4Lcross.tex 
echo "" 
echo "PDF for Observable Box4Lcross finished" 
echo "Thanks for using SARAH" 
echo "" 
