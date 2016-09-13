#include <stdio.h>
#include <stdlib.h>

/**
 * Pixel
 *	Pixel is a structure that stores 3 bites with a value range of 0 to 255
 */
typedef struct Pixel {
    unsigned char red, green, blue;

} Pixel;

/**
 * Image
 * 	Image structure stores image information from a file according to the
 * 	PPM Format Specification.
 */
typedef struct Image {
    char *magic_number;
    int width, height;
    int max_color;
    Pixel *image_data;

} Image;

/**
 * read_image
 *	Takes in two pointers as parameters, a filename of a ppm image and image structure
 * 	use to store data read in from the ppm image file.
 */
void read_image(char *filename, Image *image) {
	
    char buffer[32];
	FILE *fpointer;
	int row, column;
	
	// Open file steam for reading
	fpointer = fopen(filename, "r");
	
	// Check to see if file was opened successfully
	if(fpointer == NULL) {
		fprintf(stderr, "Error, unable to open file.\n");

		// Close file stream flush all buffers
		fclose(fpointer);
		exit(-1);
		 
	} else {
		// Make sure we are reading from the beginning of the file
		rewind(fpointer);

		// Read in the first to characters
		buffer[0] = fgetc(fpointer);
		buffer[1] = fgetc(fpointer);

		// Check the magic number
		if((buffer[0] == 'P') && (buffer[1] == '6')) {
			image->magic_number = "P6";

		} else if((buffer[0] == 'P') && (buffer[1] == '3')) {
			image->magic_number = "P3";

		} else {
			 fprintf(stderr, "Error, unacceptable image format.\n Magic number must be P6 or P3");
			 exit(-2);
			 
		}

		// Ignore comments, whitespaces, carrage returns, and tabs
		while(isdigit(buffer[0]) == 0){
			// fgetpos(fpointer, &position);
			
			// If you run into a comment proceed till you reach an newline character
			if(buffer[0] == '#') {
				do {
					buffer[0] = fgetc(fpointer);
					
				} while(buffer[0] != '\n');

			} else {
				buffer[0] = fgetc(fpointer);
				
			}

		}
		
		// Move back one character, tried using 
		ungetc(buffer[0], fpointer);
		// fsetpos(fpointer, &position);


		// Read in <width> whitespace <height>
		if(fscanf(fpointer, "%d %d", &image->width, &image->height) != 2) {
			 fprintf(stderr, "Error, invalid width and/or height.\n");
			 exit(-2);
			 
		}
		
		// Read in <maximum color value>
		if(fscanf(fpointer, "%d", &image->max_color) != 1) {
			 fprintf(stderr, "Error, invalid maximum color value.\n");
			 exit(-2);
			 
		}	

		// Allocated memory size for image data
		image->image_data = malloc(sizeof(Pixel) * image->width * image->height);

		// If magic number is P6 fread, if magic number is P3 for loop
		if(image->magic_number[1] == '6') {
			// Read in raw image data
			fread(image->image_data, sizeof(Pixel), image->width * image->height, fpointer);
						
		} else if(image->magic_number[1] == '3') {
			// Read in ascii image data
			for(row = 0; row < image->height; row++) {
				for(column = 0; column < image->width; column++) {					
					fscanf(fpointer, "%d", &image->image_data[(image->width) * row + column].red);
					fscanf(fpointer, "%d", &image->image_data[(image->width) * row + column].green);
					fscanf(fpointer, "%d", &image->image_data[(image->width) * row + column].blue);

				}
				
			}
			
		} else {
			printf("Magic number: %d\n", image->magic_number[1]);
			fprintf(stderr, "Error, invalid magic number.\n");
			exit(-2);
			
		}

		// Close file stream flush all buffers
		fclose(fpointer);	
		
	}
	
}

/**
 * write_image
 * 	stuff
 */
void write_p6_image(char *filename, Image *image) {
	FILE *fpointer;
	fpointer = fopen(filename, "wb");
	
	if(fpointer == NULL) {
		fprintf(stderr, "Error, unable to open file.\n");

		// Close file stream flush all buffers
		fclose(fpointer);
		exit(-1);
		 
	} else {
		fprintf(fpointer, "%s\n", "P6");
		fprintf(fpointer, "%d %d\n", image->width, image->height);
		fprintf(fpointer, "%d\n", image->max_color);
			
		// ASCII code is a 7-bit code stored in a byte
		fwrite(image->image_data, sizeof(Pixel), image->width * image->height, fpointer);
		
		// Close file stream flush all buffers
		fclose(fpointer);
		
		
	}
	
}

/**
 * write_image
 * 	Get the integer, convert that interger to a string then write the string to the file
 */
void write_p3_image(char *filename, Image *image) {
	FILE *fpointer;
	fpointer = fopen(filename, "w");
	int row, column;
	char str[15];
	
	if(fpointer == NULL) {
		fprintf(stderr, "Error, unable to open file.\n");

		// Close file stream flush all buffers
		fclose(fpointer);
		exit(-1);
		 
	} else {
		fprintf(fpointer, "%s\n", "P3");
		fprintf(fpointer, "%d %d\n", image->width, image->height);
		fprintf(fpointer, "%d\n", image->max_color);
		
		// Read in ascii image data
		for(row = 0; row < image->height; row++) {
			for(column = 0; column < image->width; column++) {
				sprintf(str, "%d", image->image_data[(image->width) * row + column].red);
				fprintf(fpointer, "%s\n", str);
				sprintf(str, "%d", image->image_data[(image->width) * row + column].green);
				fprintf(fpointer, "%s\n", str);
				sprintf(str, "%d", image->image_data[(image->width) * row + column].blue);
				fprintf(fpointer, "%s\n", str);				
		
			}
			
		}
		
		// Close file stream flush all buffers
		fclose(fpointer);
		
		
	}
	
}

/**
 * main
 *	Do I need to say more?
 */
int main(int argc, char *argv[]) {

	Image *ppm_image;
	ppm_image = malloc(sizeof(Image));
	
	// Check number of inputs
	if(argc != 4) {
		fprintf(stderr, "Error, incorrect usage... type<space>input ppm file<space>output ppm file.\n");
		exit(-1);
		
	} else {
		if(atoi(argv[1]) == 6) {
			read_image(argv[2], ppm_image);
			write_p6_image(argv[3], ppm_image);

		} else if(atoi(argv[1]) == 3){
			read_image(argv[2], ppm_image);
			write_p3_image(argv[3], ppm_image);	
			
		} else {
			fprintf(stderr, "Error, incorrect PPM format type.\n");
			exit(-1);
			
		}		
		
	}
	
	return(0);

}
