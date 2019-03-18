#!/bin/bash 
pdflatex Observable_TreeS4Lcross.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_TreeS4Lcross.tex 
echo "" 
echo "PDF for Observable TreeS4Lcross finished" 
echo "Thanks for using SARAH" 
echo "" 
