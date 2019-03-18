#!/bin/bash 
pdflatex Observable_Box2d2nu.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_Box2d2nu.tex 
echo "" 
echo "PDF for Observable Box2d2nu finished" 
echo "Thanks for using SARAH" 
echo "" 
