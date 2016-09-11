#include <stdio.h>
#include <stdlib.h>

typedef struct Pixel {
    unsigned char red, blue, green;

} Pixel;

typedef struct Image {
    char *magic_number;
    int width, height;
    int max_color;
    Pixel *image_data;

} Image;

void read_image(char *filename, Image *image) {
	
    char buffer[32];
	FILE *fpointer;
	
	fpointer = fopen(filename, "r");
	
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
			 fprintf(stderr, "Error, unacceptable image format.\n");
			 exit(-2);
			 
		}

		// Ignore comments, whitespaces, carrage returns, and tabs
		while(isdigit(buffer[0]) == 0){
			if(buffer[0] == '#') {
				do {
					buffer[0] = fgetc(fpointer);
					
				} while(buffer[0] != '\n');

			} else {
				buffer[0] = fgetc(fpointer);

			}

		}
		
		// Move back one character
		ungetc(buffer[0], fpointer);

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

		// Read in image data
		fread(image->image_data, sizeof(Pixel), image->width * image->height, fpointer);
		
		// Close file stream flush all buffers
		fclose(fpointer);	
		
	}
	
}

void write_image(char *filename, Image *image, char ) {
	FILE *fpointer;
	fpointer = fopen(filename, "w");
	
	if(fpointer == NULL) {
		fprintf(stderr, "Error, unable to open file.\n");

		// Close file stream flush all buffers
		fclose(fpointer);
		exit(-1);
		 
	} else {
		fprintf(fpointer, "%s\n", image->magic_number);
		fprintf(fpointer, "%d %d\n", image->width, image->height);
		fprintf(fpointer, "%d\n", image->max_color);
		fwrite(image->image_data, sizeof(Pixel), image->width * image->height, fpointer);
		
		// Close file stream flush all buffers
		fclose(fpointer);
		
	}
	
}

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
			write_image(argv[3], ppm_image);

		} else if(atoi(argv[1]) == 3){
			read_image(argv[2], ppm_image);
			write_image(argv[3], ppm_image);	
			
		} else {
			fprintf(stderr, "Error, incorrect PPM format type.\n");
			exit(-1);
			
		}		
		
	}
	
	return(0);

}
