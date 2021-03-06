#include "File.hpp"
#include "DEBUG/Debug.hpp"
#include "IMAGE/stb_image.h"

ImageFile::ImageFile()
{

}

unsigned char * ImageFile::ReadImage(char * filePath,int * image_width,int * image_height)
{
    int nrChannels;

    unsigned char * data = stbi_load(filePath, image_width, image_height, &nrChannels, 0);

    RedLog("-------------LoadImage Start-------------\n");
    RedLog("Path:%s\n",filePath);
    RedLog("Sizeof:%d\n",sizeof(data));
    RedLog("width:%d\nheight:%d\nchannels:%d\n",*image_width,*image_height,nrChannels);
    RedLog("-------------LoadImage End---------------\n\n\n\n");

    return data;
}

/*
unsigned char * ImageFile::ReadImage(char * filePath,int * image_width,int * image_height)
{
    unsigned char * image = SOIL_load_image(filePath, image_width, image_height, 0, SOIL_LOAD_RGB);

    RedLog("-------------LoadImage Start-------------\n");
    RedLog("Path:%s\n",filePath);
    RedLog("width:%d\nheight:%d\n",*image_width,*image_height);
    RedLog("-------------LoadImage End---------------\n\n\n\n");

    return image;
}
*/

/*
unsigned char * ImageFile::ReadImage(char * filePath,int * image_width,int * image_height)
{
    *image_width = 8888;
    *image_height = 8888;
    unsigned char * res = NULL;


    char png_header[8];
    png_structp png_ptr;
    png_infop info_ptr;
    int width, height, rowBytes;
    png_byte color_type;
    png_byte bit_depth;
    png_colorp palette;

    FILE * file = fopen(filePath, "rb");
    if(file == NULL){
        RedLog("RedFile Fail");
        return NULL;
    }

    fread(png_header, 1, 8, file);
    if(png_sig_cmp((png_bytep)png_header, 0, 8))
    {
        RedLog("Not a PNG file...");
        fclose(file);
        return NULL;
    }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info_ptr = png_create_info_struct(png_ptr);
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, 0);
        RedLog("ReadPngFile: Failed to read the PNG file");
        fclose(file);
    }

    //I/O initialisation methods
    png_init_io(png_ptr, file);
    png_set_sig_bytes(png_ptr, 8);  //Required!!!

    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
    width = info_ptr->width;
    height = info_ptr->height;

    *image_width = width;
    *image_height = height;

    unsigned char* rgba = new unsigned char[width * height * 4];  //each pixel(RGBA) has 4 bytes
    png_bytep * row_pointers = png_get_rows(png_ptr, info_ptr);

    int pos = (width * height * 4) - (4 * width);



    for(int t_row = 0; t_row < height; t_row++)
    {
        int row = height - t_row - 1;
        for(int col = 0; col < (4 * width); col += 4)
         {
             rgba[pos++] = row_pointers[row][col];        // red
             rgba[pos++] = row_pointers[row][col + 1]; // green
             rgba[pos++] = row_pointers[row][col + 2]; // blue
             rgba[pos++] = row_pointers[row][col + 3]; // alpha
         }
         pos=(pos - (width * 4)*2); //move the pointer back two rows
    }

    res = rgba;

    //clean up after the read, and free any memory allocated
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(file);

    RedLog("ReadPng\n\n");

    return res;
}
*/
