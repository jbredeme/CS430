# Pixmap

This program reads in a Portable PixMap (PPM) image in either P3 (ASCII) or P6 (Binary) format then stores the image data into a image buffer. Then performs operations on the image header and converts binary data into ascii or ascii into binary depending on the magic number conversion.	

## Usage
```c
ppmrw 6|3 input.ppm output.ppm
```