//
// Created by lilly on 3/19/2025.
//

#ifndef IMAGE_H
#define IMAGE_H

#endif //IMAGE_H


#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//(1) Declare a Header struct
struct Header{
    //(2) Declare each Header element
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
    int getImageSize() const{
        return static_cast<int>(width)*static_cast<int>(height);
    }
};
//(3) Declare a Pixel struct
struct Pixel{
    //(4) Declare each Pixel element
    unsigned char blue;
    unsigned char green;
    unsigned char red;

    Pixel(unsigned char _b, unsigned char _g, unsigned char _r){
        blue = _b;
        green = _g;
        red = _r;
    }
};
//(5) Declare an Image class
struct  Image{
    //(6) Declare private data member of the Image class
//private:
    //(7) Declare a name
    string name;
    //(8) Declare a stream (ifstream)
    ifstream inFile;
    ofstream outFile;

public:
    //(9) Declare a header for the Image
    Header header;
    //(10) Declare a vector of pixels
    vector<Pixel> pixels;

    //(11) Declare an Image constructor
    Image();
    //(12) Declare a read function
    void read(const string& inName);
    //(13) Declare a write function
    void write(const string& outName);
};