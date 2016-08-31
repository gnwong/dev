##########################################
##  
##  Makefile
##
##    Provides useful commands for the
##    LaTeX problem set environment.
##
##  Created        31-08-16  by  GNW
##  Last Modified  31-08-16  by  GNW
##
##########################################

all:
	pdflatex src/*
	$(MAKE) clean

setup:
	@read -p "Enter Course Name: " course; \
	sed -i '' -e "s/COURSE/$$course/g" src/template.tex
	@read -p "Enter Your Name: " aname; \
	sed -i '' -e "s/AUTHOR/$$aname/g" src/template.tex

clean:
	@-rm *.aux *.log *.gz
	@-rm src/*.aux src/*.log src/*.gz
	@-rm template.pdf
	@-cp src/*.pdf pdf/
	
