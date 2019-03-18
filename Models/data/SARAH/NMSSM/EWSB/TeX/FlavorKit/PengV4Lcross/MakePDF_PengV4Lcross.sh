#!/bin/bash 
pdflatex Observable_PengV4Lcross.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_PengV4Lcross.tex 
echo "" 
echo "PDF for Observable PengV4Lcross finished" 
echo "Thanks for using SARAH" 
echo "" 
