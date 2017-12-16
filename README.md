# Pixmap ![Jarid_Bredemeier](https://img.shields.io/badge/build-passing-green.svg?style=flat-plastic)

This program reads in a Portable PixMap (PPM) image in either P3 (ASCII) or P6 (Binary) format then stores the image data into a image buffer. Then performs operations on the image header and converts binary data into ascii or ascii into binary depending on the magic number conversion.	

## Usage
```c
ppmrw 6|3 input.ppm output.ppm
```

## Built With
* [Cygwin](https://cygwin.com/index.html) - 64-bit version for Windows
* GNU Compiler Collection (GCC) 5.4.0
* Windows 10 Professional

## Author
* **Jarid Bredemeier**
