#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bmp.c"

int show_info_header(BITMAP*);
int show_dib_header(BITMAP*);


int main(int argc,char *argv[])
{
	BITMAP *b = bmp_create_standard_bitmap(100,100,atoi(argv[1]));
	
	char *path = "C:\\Users\\Marek\\Desktop\\test.bmp";
	bmp_save_bitmap(b,path);
	
	return 0;
}


/*
BITMAP *b = bmp_load_bitmap("C:\\Users\\Marek\\Desktop\\Untitled.bmp");
	char *savep = "C:\\Users\\Marek\\Desktop\\Untitled1.bmp";
	//bmp_save_bitmap(b,savep);
	
	//printf("%d\n",b->dib_header.image_size );
	
	
	
	//return 0;
	
	printf("%d\n",(b->dib_header.width * b->dib_header.height * (b->dib_header.bpp / 8)));
	
	printf("FILE HEADER:\n\n");
	show_info_header(b);
	printf("DIB HEADER:\n\n");
	show_dib_header(b);
*/


int show_info_header(BITMAP *b)
{
	printf("header_field:\t%c%.c\n",
	b->file_header.header_field[0],
	b->file_header.header_field[1]);
	printf("size:\t\t%.8X\n", b->file_header.size);
	printf("RESERVED_0:\t%.4X\n", b->file_header.RESERVED_0);
	printf("RESERVED_1:\t%.4X\n",b->file_header.RESERVED_1);
	printf("offset:\t\t%.8X\n",b->file_header.offset);
	
	return 0;
}

int show_dib_header(BITMAP *b)
{
	printf("Size:\t\t%.8X\n",b->dib_header.header_size);
	printf("Width:\t\t%.8X\n",b->dib_header.width);
	printf("Height:\t\t%.8X\n",b->dib_header.height);
	printf("Color Planes:\t%.8X\n",b->dib_header.color_planes);
	printf("BPP:\t\t%.8X\n",b->dib_header.bpp);
	printf("Compression:\t%.8X\n",b->dib_header.compression_method);
	printf("Image Size:\t%.8X\n",b->dib_header.image_size);
	printf("H_RES:\t\t%.8X\n",b->dib_header.horizontal_resolution);
	printf("V_RES:\t\t%.8X\n",b->dib_header.vertical_resolution);
	printf("Colors:\t\t%.8X\n",b->dib_header.number_of_colors);
	printf("Imp Colors:\t%.8X\n",b->dib_header.important_color_used);
	
	return 0;
}