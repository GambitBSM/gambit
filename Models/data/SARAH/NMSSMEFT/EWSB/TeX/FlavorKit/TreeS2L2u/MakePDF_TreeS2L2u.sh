#!/bin/bash 
pdflatex Observable_TreeS2L2u.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_TreeS2L2u.tex 
echo "" 
echo "PDF for Observable TreeS2L2u finished" 
echo "Thanks for using SARAH" 
echo "" 
