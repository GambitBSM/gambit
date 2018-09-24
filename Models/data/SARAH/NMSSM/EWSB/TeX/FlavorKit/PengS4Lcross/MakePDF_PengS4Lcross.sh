#!/bin/bash 
pdflatex Observable_PengS4Lcross.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_PengS4Lcross.tex 
echo "" 
echo "PDF for Observable PengS4Lcross finished" 
echo "Thanks for using SARAH" 
echo "" 
