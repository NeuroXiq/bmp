#ifndef __BMP_EDITOR_LIB__
#define __BMP_EDITOR_LIB__

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#endif


BITMAP* bmp_load_bitmap(char *file_name);
int bmp_get_file_size(FILE* f);
int bmp_editor_save_bitmap(BITMAP *f, char *path);
BITMAP* bmp_editor_create_bitmap(unsigned int width, unsigned int height, unsigned short bpp, int *color_palette);
unsigned int bmp_editor_colors_count_in_color_palette(unsigned short bpp);
int bmp_editor_fill_reserved_bytes(BITMAPFILEHEADER *fh);
