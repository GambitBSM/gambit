#!/bin/bash 
pdflatex Observable_TreeSdulv.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_TreeSdulv.tex 
echo "" 
echo "PDF for Observable TreeSdulv finished" 
echo "Thanks for using SARAH" 
echo "" 
