//
// Created by lilly on 3/19/2025.
//

#ifndef IMAGE_H
#define IMAGE_H

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
    Pixel() {
        // do nothing
    }
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
  //  ifstream inFile;
   // ofstream outFile;

public:
    //(9) Declare a header for the Image
    Header header;
    //(10) Declare a vector of pixels
    vector<Pixel> pixels;

    //(11) Declare an Image constructor
    Image();
    Image(const Image& other);
    Image& operator=(const Image& other);
    ~Image();
    //(12) Declare a read function
    void read(const string& inName);
    //(13) Declare a write function
    void write(const string& outName);
};

//--------------------------------------------------------
Image::Image() {
    // Do nothing
}

Image::Image(const Image& other) {
    this->name = other.name;
    this->header = other.header;
    this->pixels = other.pixels;
}

Image& Image::operator=(const Image& other) {
    if (this != &other) {
        this->name = other.name;
        this->header = other.header;
        this->pixels = other.pixels;
    }
    return *this;
}

Image::~Image() {
    // do nothing
}

void Image::read(const string& inName) {
    ifstream inFile;
    //(14) Read in the .tga file
    inFile.open(inName,ios::binary);
    //(15) Check if the file is opening
    if(inFile.is_open() == false){
        cout << "Error: Input file " << inName << endl;
        return;
    }
    //(16) Read in each element of the .tga file
    inFile.read(&header.idLength,1);
    inFile.read(&header.colorMapType,1);
    inFile.read(&header.dataTypeCode,1);
    inFile.read(reinterpret_cast<char*>(&header.colorMapOrigin),2);
    inFile.read(reinterpret_cast<char*>(&header.colorMapLength),2);
    inFile.read(&header.colorMapDepth,1);
    inFile.read(reinterpret_cast<char*>(&header.xOrigin),2);
    inFile.read(reinterpret_cast<char*>(&header.yOrigin),2);
    inFile.read(reinterpret_cast<char*>(&header.width),2);
    inFile.read(reinterpret_cast<char*>(&header.height),2);
    inFile.read(&header.bitsPerPixel,1);
    inFile.read(&header.imageDescriptor,1);

//  file.read(reinterpret_cast<char*> (&my_T), sizeof(my_T));

    //(17) Get the image size by multiplying the image height and width
  //  int imageSize = header.height * header.height;
    //(18) Create a for loop to read in all the pixels
    for(int i = 0 ; i< header.getImageSize(); i++){
        //(21) Push in each pixel to the pixel vector
        unsigned char b;
        unsigned char g;
        unsigned char r;

        inFile.read(reinterpret_cast<char*>(&b),1);
        inFile.read(reinterpret_cast<char*>(&g),1);
        inFile.read(reinterpret_cast<char*>(&r),1);

        pixels.push_back(Pixel(b,g,r));
    }
}

void Image::write(const string& outName) {
    ofstream outFile;
    //(22) Create a .tga file
    outFile.open(outName,ios::binary);
    //(23) Write out each .tga file header element
      outFile.write(&header.idLength,1);
      outFile.write(&header.colorMapType,1);
      outFile.write(&header.dataTypeCode,1);
      outFile.write(reinterpret_cast<char*>(&header.colorMapOrigin),2);
      outFile.write(reinterpret_cast<char*>(&header.colorMapLength),2);
      outFile.write(&header.colorMapDepth,1);
      outFile.write(reinterpret_cast<char*>(&header.xOrigin),2);
      outFile.write(reinterpret_cast<char*>(&header.yOrigin),2);
      outFile.write(reinterpret_cast<char*>(&header.width),2);
      outFile.write(reinterpret_cast<char*>(&header.height),2);
      outFile.write(&header.bitsPerPixel,1);
      outFile.write(&header.imageDescriptor,1);

  //  int imageSize = header.height * header.height;
    //(24) Create a for loop to write out each pixel
      for(int i = 0; i < header.getImageSize(); i++){
        //(25) Write out each image pixel
        outFile.write(reinterpret_cast<char*>(&pixels[i].blue),1);
        outFile.write(reinterpret_cast<char*>(&pixels[i].green),1);
        outFile.write(reinterpret_cast<char*>(&pixels[i].red),1);
      }
}

#endif
