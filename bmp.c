#include "bmp.h"

BITMAP* bmp_load_bitmap(char *file_path)
{
	
	FILE *f = fopen(file_path, "rb");
	
	if(f == NULL)
		return NULL;
	
	int file_size = bmp_get_file_size(f);
	if(file_size < 54) // minimum BMP file header length (for BITMAPFILEHEADER + BITMAPINFOHEADER)
		return NULL;

	BITMAP *bmp = malloc(sizeof(BITMAP));
	BITMAPFILEHEADER *h = &bmp->file_header;
	BITMAPINFOHEADER *dib = &bmp->dib_header;	
	
	//file header
	fread(&h->header_field, 1, 2, f);
	fread(&h->size, 1, 4, f);
	fread(&h->RESERVED_0, 1, 2, f);
	fread(&h->RESERVED_1, 1, 2, f);
	fread(&h->offset, 1, 4, f);
	
	//DIB header
	fread(&dib->header_size, 1, 4, f);
	fread(&dib->width, 1, 4, f);
	fread(&dib->height, 1, 4, f);
	fread(&dib->color_planes, 1, 2, f);
	fread(&dib->bpp, 1, 2, f);
	fread(&dib->compression_method, 1, 4, f);
	fread(&dib->image_size, 1, 4, f);
	fread(&dib->horizontal_resolution, 1, 4, f);
	fread(&dib->vertical_resolution, 1, 4, f);
	fread(&dib->number_of_colors, 1, 4, f);
	fread(&dib->important_color_used, 1, 4, f);
	
	//compression method and color palette
	if(dib->number_of_colors > 0)
	{
		bmp->colors_palette = malloc(dib->number_of_colors);
		if(bmp->colors_palette == NULL)
			return NULL;
		
		if(dib->compression_method == BI_BITFIELDS)
		{
			fread(bmp->bitmask, 1, 12, f);
		}
		fread(bmp->colors_palette, 1, dib->number_of_colors, f);
	}
	
	//pixels data
	//int pixels_bytes = dib->width * dib->height * (dib->bpp/8);
	int pixels_bytes = dib->image_size;
	if(pixels_bytes > 0)
	{
		bmp->pixels = malloc(pixels_bytes);
		fseek(f, h->offset, SEEK_SET);
		fread(bmp->pixels, 1, pixels_bytes, f);
	}

	return bmp;
}
int bmp_save_bitmap(BITMAP *b, char *path)
{
	FILE *f = fopen(path, "wb");
	
	if(f == NULL)
		return 0;
	
	BITMAPFILEHEADER *fh = &b->file_header;
	BITMAPINFOHEADER *dib = &b->dib_header;
	
	// File header
	fwrite(fh->header_field,1,2,f);
	fwrite(&fh->size, 1, 4, f);
	fwrite(&fh->RESERVED_0, 1, 2, f);
	fwrite(&fh->RESERVED_1, 1, 2, f);
	fwrite(&fh->offset, 1, 4, f);
	
	//DIB header
	fwrite(&dib->header_size, 1, 4, f);
	fwrite(&dib->width, 1, 4, f);
	fwrite(&dib->height, 1, 4, f);
	fwrite(&dib->color_planes, 1, 2, f);
	fwrite(&dib->bpp, 1, 2, f);
	fwrite(&dib->compression_method, 1, 4, f);
	fwrite(&dib->image_size, 1, 4, f);
	fwrite(&dib->horizontal_resolution, 1, 4, f);
	fwrite(&dib->vertical_resolution, 1, 4, f);
	fwrite(&dib->number_of_colors, 1, 4, f);
	fwrite(&dib->important_color_used, 1, 4, f);
	
	if(dib->compression_method == BI_BITFIELDS)
	{
		fwrite(b->bitmask, 1, 12, f);
	}
	if(dib->number_of_colors > 0)
	{
		fwrite(b->colors_palette, 1, dib->number_of_colors, f);
	}
	
	//pixels 
	//int pix_bytes_count = dib->width * dib->height * (dib->bpp / 8);
	int pix_bytes_count = dib->image_size;
	fwrite(b->pixels, 1, pix_bytes_count, f);
	
	return 0;
}
int bmp_get_file_size(FILE *f)
{
	fseek(f,0L,SEEK_END);
	int file_size = ftell(f);
	rewind(f);
	
	return file_size;
}

BITMAP* bmp_create_standard_bitmap(unsigned int width, unsigned int height, unsigned short bpp)
{
	BITMAP *bmp = malloc(sizeof(BITMAP));
	BITMAPINFOHEADER *dib = &bmp->dib_header;
	BITMAPFILEHEADER *fh = &bmp->file_header;
	
	/* HEADERS */
	fh->header_field[0] = 'B';
	fh->header_field[1] = 'M';
	fh->size = (ROW_SIZE(width,bpp) * height) + BMP_FILE_HEADER_SIZE + DIB_HEADER_SIZE;
	fh->offset = DIB_HEADER_SIZE + BMP_FILE_HEADER_SIZE;
	
	dib->header_size = DIB_HEADER_SIZE;
	dib->width = width;	
	dib->height = height;
	dib->color_planes = 1;
	dib->bpp = bpp;
	dib->compression_method = BI_RGB;
	dib->image_size = (ROW_SIZE(width,bpp) * height);
	dib->horizontal_resolution = width;
	dib->vertical_resolution = height;
	dib->number_of_colors = 0;
	dib->important_color_used = 0;
	
	//bmp->pixels = calloc((ROW_SIZE(width,bpp) * height),1);
	bmp->pixels = malloc((ROW_SIZE(width,bpp) * height));
	
	return bmp;
}