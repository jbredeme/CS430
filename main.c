/**
 * Author: Jarid Bredemeier
 * Email: jpb64@nau.edu
 * Date: Wednesday, September 14, 2016
 * File: main.c
 * Copyright © 2016 All rights reserved
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ppm\ppm.h"

/**
 * main
 *
 * @param argc - contains the number of arguments passed to the program
 * @param argv - a one-dimensional array of strings
 * @returns 0 upon successful completion 
 * @description main function called by the operating system when the user runs the program. 
 */
int main(int argc, char *argv[]) {

	Image *ppm_image;
	ppm_image = (Image *)malloc(sizeof(Image));
	
	// Check number of inputs
	if(argc != 4) {
		fprintf(stderr, "Error, incorrect usage. Please enter:\n6 or 3<space>input_file_name.ppm<space>output_file_name.ppm.\n");
		exit(-1);
	
	// Verify if the conversion specifier is either 3 or 6, error if not.
	} else {
		if(atoi(argv[1]) == 6) {
			read_image(argv[2], ppm_image);
			write_p6_image(argv[3], ppm_image);

		} else if(atoi(argv[1]) == 3){
			read_image(argv[2], ppm_image);
			write_p3_image(argv[3], ppm_image);	
			
		} else {
			fprintf(stderr, "Error, invalid PPM conversion format type. Must be 6 or 3.\n");
			exit(-1);
			
		}		
		
	}
	
	return(0);

}