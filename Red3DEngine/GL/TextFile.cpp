#include "File.hpp"

#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#include <string>
#include <fstream>

TextFile::TextFile()
{

}

char * TextFile::ReadFile(char * filePath)
{
    char * txt = nullptr;

    std::string FileContent;
    std::ifstream FileContentStream(filePath, std::ios::in);
    if(FileContentStream.is_open()){
        std::string Line = "";
        while(getline(FileContentStream, Line)){
            FileContent += "\n" + Line;
        }
        FileContentStream.close();

        char * t = (char *)FileContent.c_str();

        txt = (char *)malloc(FileContent.length() * sizeof(char));
        strcpy(txt,t);
    }else{
        RedLog("Impossible to open %s. Are you in the right directory ?\n", filePath);
        getchar();

        txt = nullptr;
    }

    return txt;
}
