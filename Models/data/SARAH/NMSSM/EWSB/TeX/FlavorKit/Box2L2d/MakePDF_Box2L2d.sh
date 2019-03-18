#!/bin/bash 
pdflatex Observable_Box2L2d.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_Box2L2d.tex 
echo "" 
echo "PDF for Observable Box2L2d finished" 
echo "Thanks for using SARAH" 
echo "" 
