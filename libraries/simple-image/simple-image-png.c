#include <stdio.h>
#include <stdlib.h>

#include <png.h>

#include "simple-image.h"


#define PNG_HEADER_SIZE 8

GLboolean siTexImagePNG(GLenum target,GLenum internalFormat, const char *path, unsigned int* pixelWidth, unsigned int* pixelHeight){

    FILE *PNG_file;
	GLubyte PNG_header[PNG_HEADER_SIZE];
png_uint_32 bit_depth, color_type;
	 png_uint_32 width, height;
	  png_byte* PNG_image_buffer ;
    png_byte** PNG_rows;
	  png_structp PNG_reader;
	unsigned int row;
	png_infop PNG_info;
	 png_infop PNG_end_info;

	PNG_file = fopen(path, "rb");
    if (PNG_file == NULL)
    {

        return GL_FALSE;
    }
    
    
    
    fread(PNG_header, 1, PNG_HEADER_SIZE, PNG_file);
    if (png_sig_cmp(PNG_header, 0, PNG_HEADER_SIZE) != 0)
    {
    
        return GL_FALSE;
    }
    
     PNG_reader = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (PNG_reader == NULL)
    {
      
        fclose(PNG_file);
        return GL_FALSE;
    }
	
     PNG_info = png_create_info_struct(PNG_reader);
    if (PNG_info == NULL)
    {
    
        png_destroy_read_struct(&PNG_reader, NULL, NULL);
        fclose(PNG_file);
        return GL_FALSE;
    }
	
     PNG_end_info = png_create_info_struct(PNG_reader);
    if (PNG_end_info == NULL)
    {
  
        png_destroy_read_struct(&PNG_reader, &PNG_info, NULL);
        fclose(PNG_file);
        return GL_FALSE;
    }
    
    if (setjmp(png_jmpbuf(PNG_reader)))
    {
 
        png_destroy_read_struct(&PNG_reader, &PNG_info, &PNG_end_info);
        fclose(PNG_file);
        return GL_FALSE;
    }
    
    png_init_io(PNG_reader, PNG_file);
    png_set_sig_bytes(PNG_reader, PNG_HEADER_SIZE);
    
    png_read_info(PNG_reader, PNG_info);
    

    width = png_get_image_width(PNG_reader, PNG_info);
    height = png_get_image_height(PNG_reader, PNG_info);
    
    
    bit_depth = png_get_bit_depth(PNG_reader, PNG_info);
    color_type = png_get_color_type(PNG_reader, PNG_info);
    
    if (color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(PNG_reader);
    }
	
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) 
    {
        png_set_gray_1_2_4_to_8(PNG_reader);
    }
    
    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
        png_set_gray_to_rgb(PNG_reader);
    }
	
    if (png_get_valid(PNG_reader, PNG_info, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(PNG_reader);
    }
    else
    {
        png_set_filler(PNG_reader, 0xff, PNG_FILLER_AFTER);
    }
    
    if (bit_depth == 16)
    {
        png_set_strip_16(PNG_reader);
    }
    
    png_read_update_info(PNG_reader, PNG_info);
    
     PNG_image_buffer = (png_byte*)malloc(4 * width * height);
   PNG_rows = (png_byte**)malloc(height * sizeof(png_byte*));
    
    
    for (row = 0; row < height; ++row)
    {
        PNG_rows[height - 1 - row] = PNG_image_buffer + (row * 4 * width);
    }
    
    png_read_image(PNG_reader, PNG_rows);
    
    free(PNG_rows);
    
    png_destroy_read_struct(&PNG_reader, &PNG_info, &PNG_end_info);
    fclose(PNG_file);
    
	    glTexImage2D(
				 target,
				 0,
				 //internalFormat
				 GL_RGBA,
				 width,
				 height,
				0,
				GL_RGBA,
				 GL_UNSIGNED_BYTE,
				 PNG_image_buffer);
	if (pixelWidth != 0) {
		*pixelWidth = width;
	}
	if (pixelHeight != 0) {
		*pixelHeight = height;
	}
	

   free(PNG_image_buffer);
    
    return GL_TRUE;
}
