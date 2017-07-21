#ifndef __BMPLIB_H__
#define __BMPLIB_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#define ROW_SIZE(width, bpp)\
		(unsigned int)\
		((((width * bpp) + 31)/32)  * 4 )
		
#define BMP_FILE_HEADER_SIZE 14
#define DIB_HEADER_SIZE 40

typedef enum CompressionMethod
{
	BI_RGB = 0, // NO COMPRESSION
	BI_RLE8 = 1,
	BI_RLE4 = 2,
	BI_BITFIELDS = 3,
	BI_JPEG = 4,
	BI_PNG = 5, 
	BI_ALPHABITFIELDS = 6,
	BI_CMYK = 11,
	BI_CMYKRLE8 = 12,
	BI_CMYKRLE4 = 13
} CompressionMethod ;

typedef struct BITMAPFILEHEADER
{
	unsigned char header_field[2];
	unsigned int size;	
	unsigned short RESERVED_0;
	unsigned short RESERVED_1;
	unsigned int offset;
	
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER
{
	unsigned int header_size;
	unsigned int width;
	unsigned int height;
	unsigned short color_planes;
	unsigned short bpp;
	unsigned int compression_method;
	unsigned int image_size;
	unsigned int horizontal_resolution;
	unsigned int vertical_resolution;
	unsigned int number_of_colors;
	unsigned int important_color_used;
	
} BITMAPINFOHEADER;

typedef struct BITMAP
{
	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER dib_header;
	char *colors_palette;
	char *pixels;
	char bitmask[12];
	
} BITMAP;

BITMAP* bmp_load_bitmap(char *file_name);
int bmp_get_file_size(FILE* f);
int bmp_save_bitmap(BITMAP *f, char *path);
BITMAP* bmp_create_standard_bitmap(unsigned int width, unsigned int height, unsigned short bpp);

#endif