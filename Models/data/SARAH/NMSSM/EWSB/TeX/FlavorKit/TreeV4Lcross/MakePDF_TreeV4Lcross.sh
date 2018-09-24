#!/bin/bash 
pdflatex Observable_TreeV4Lcross.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_TreeV4Lcross.tex 
echo "" 
echo "PDF for Observable TreeV4Lcross finished" 
echo "Thanks for using SARAH" 
echo "" 
