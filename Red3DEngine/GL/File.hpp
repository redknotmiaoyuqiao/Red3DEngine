#pragma once

#include "DEBUG/Debug.hpp"

class TextFile
{
private:
public:
    TextFile();
    char * ReadFile(char * filePath);
};

class ImageFile
{
private:
public:
    ImageFile();
    unsigned char * ReadImage(char * filePath,int * image_width,int * image_height);
};
