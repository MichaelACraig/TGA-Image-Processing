#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };

    struct Pixel{
        unsigned char red;
        unsigned char blue;
        unsigned char green;
        vector<Pixel> pixelData;
    };

#endif