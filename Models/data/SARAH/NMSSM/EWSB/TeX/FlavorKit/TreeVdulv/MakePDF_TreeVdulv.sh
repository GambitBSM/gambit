#!/bin/bash 
pdflatex Observable_TreeVdulv.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_TreeVdulv.tex 
echo "" 
echo "PDF for Observable TreeVdulv finished" 
echo "Thanks for using SARAH" 
echo "" 
