#!/bin/bash 
pdflatex Observable_Gluon2Q.tex 
cd Diagrams 
find . -name "*.mp" -exec mpost {} \; 
cd .. 
pdflatex  Observable_Gluon2Q.tex 
echo "" 
echo "PDF for Observable Gluon2Q finished" 
echo "Thanks for using SARAH" 
echo "" 
