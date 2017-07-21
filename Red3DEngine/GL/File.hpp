#pragma once

#include "DEBUG/Debug.hpp"

class TextFile
{
private:
public:
    TextFile();
    char * ReadFile(char * filePath);
};
