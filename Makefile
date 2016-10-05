# Author: Jarid Bredemeier
# Email: jpb64@nau.edu
# Date: Wednesday, September 14, 2016
# File: Makefile.mak
# Copyright © 2016 All rights reserved 

all: main.o ppm.o
	gcc main.o ppm.o -o ppmrw

main.o: main.c
	gcc -c main.c

ppm.o: ppm\ppm.c ppm\ppm.h
	gcc -c ppm\ppm.c

clean:
	rm *.o *.exe