//
// Created by lilly on 3/21/2025.
//

#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

//#include <iostream>
//#include <ostream>
//#include <fstream>
//#include <vector>

//#pragma once
#include "Image.h"

//using namespace std;

template <typename T>
T clamp(T num);

unsigned char multiply_char(unsigned char c1, unsigned char c2);

Pixel multiply_pixel( Pixel &p1,  Pixel &p2);

Image multiply_func(const string& path1, const string& path2, const string& outputPath);

Image subtract_frick(Image& image1, Image& image2, const string& outputPath);

Image subtract_func(const string& path1, const string& path2, const string& outputPath);

Image subtract_func(Image& image1, const string& path2, const string& outputPath);

Image modify_color_channel(const string& input, const string& output, int channel, int mod = 0, int scale = 1);

//--------------------------------------------------------------------------------------------

// Clamping Function
template <typename T>
T clamp(T num) {
    if (num>255) return 255;
    if (num<0) return 0;
    return num;
}

unsigned char multiply_char(unsigned char c1, unsigned char c2) {
    return clamp(static_cast<unsigned char>(((((static_cast<float>(c1)/255) * (static_cast<float>(c2)/255))*255)+0.5f)));
}

Pixel multiply_pixel(Pixel &p1, Pixel &p2) {
    return Pixel( multiply_char(p1.blue, p2.blue),multiply_char(p1.green, p2.green), multiply_char(p1.red, p2.red));
}


Image multiply_func(const string& path1, const string& path2, const string& outputPath) {
    Image image1, image2, image3;
    image1.read(path1);
    image2.read(path2);
    image3 = image1;

    if (image1.header.getImageSize() != image2.header.getImageSize()) {
        cout << "Error: Image size mismatch!" << endl;
        return image1;
    }

    for (int i = 0; i < image1.header.getImageSize(); i++) {
        image3.pixels[i] = multiply_pixel(image1.pixels[i],image2.pixels[i]);
    }
    image3.write(outputPath);
    return image3;
}
/*
void subtract_func(const string& path1, const string& path2, const string& outputPath) {
    Image image1, image2;
    image1.read(path1);
    image2.read(path2);
    if (image1.header.getImageSize() != image2.header.getImageSize()) {
        cout << "Error: Image size mismatch!" << endl;
        return;
    }
    for (int i = 0; i < (image1.header.width * image1.header.height); i++) {
        image1.pixels[i].blue = clamp(image1.pixels[i].blue - image2.pixels[i].blue);
        image1.pixels[i].green = clamp(image1.pixels[i].green - image2.pixels[i].green);
        image1.pixels[i].red = clamp(image1.pixels[i].red - image2.pixels[i].red);
    }
    image1.write(outputPath);
}*/


Image subtract_frick(Image& image1, Image& image2, const string& outputPath){
    Image image3 = image1;
    if (image1.header.getImageSize() != image2.header.getImageSize()) {
        cout << "Error: Image size mismatch!" << endl;
    }

    for (int i = 0; i < (image1.header.width * image1.header.height); i++) {
        // image1.pixels[i].blue = clamp(image1.pixels[i].blue - image2.pixels[i].blue);
        // image1.pixels[i].green = clamp(image1.pixels[i].green - image2.pixels[i].green);
        // image1.pixels[i].red = clamp(image1.pixels[i].red - image2.pixels[i].red);
        image3.pixels[i].blue = clamp(static_cast<int>(image1.pixels[i].blue) - static_cast<int>(image2.pixels[i].blue));
        image3.pixels[i].green = clamp(static_cast<int>(image1.pixels[i].green) - static_cast<int>(image2.pixels[i].green));
        image3.pixels[i].red = clamp(static_cast<int>(image1.pixels[i].red) - static_cast<int>(image2.pixels[i].red));
    }
    image3.write(outputPath);
    return image3;
}


Image subtract_func(const string& path1, const string& path2, const string& outputPath) {
    Image image1, image2;
    image1.read(path1);
    image2.read(path2);

    return subtract_frick(image1, image2, outputPath);
}

Image subtract_func(Image& image1, const string& path2, const string& outputPath) {
    Image image2;
    image2.read(path2);

    return subtract_frick(image1, image2, outputPath);
}
// not made:
// version for combo: string, image
// version for combo: image, image

unsigned char screen_char(unsigned char& c1, unsigned char& c2) {
    float tempb1 = static_cast<float>(c1)/255, tempb2 = static_cast<float>(c2)/255;
    tempb1 = 1- tempb1, tempb2 = 1- tempb2;
    float tempb3 = tempb1*tempb2;
    tempb3 = 1 - tempb3;
    tempb3 = tempb3*255;
    tempb3 = tempb3 + 0.5f;
    float tempb4 = static_cast<unsigned char>(tempb3);
    return tempb4;
}


Image screen_func(Image& image1, const string& path2, const string& outputPath) {
//    Image image1;
    Image image2, image3;
    //image1.read(path1);
    image2.read(path2);
    image3 = image1;
    if (image3.header.getImageSize() != image2.header.getImageSize()) {
        cout << "Error: Image size mismatch!" << endl;
        return image1;;
    }
    for (int i = 0; i < (image1.header.width * image1.header.height); i++) {
        image3.pixels[i].blue = screen_char(image1.pixels[i].blue,image2.pixels[i].blue);
        image3.pixels[i].green = screen_char(image1.pixels[i].green,image2.pixels[i].green);
        image3.pixels[i].red = screen_char(image1.pixels[i].red,image2.pixels[i].red);
    }
    image3.write(outputPath);
    return image3;
}

unsigned char overlay_char(unsigned char& c1, unsigned char& c2) {
    float tempb1 = static_cast<float>(c1)/255;
    float tempb2 = static_cast<float>(c2)/255;
    float tempb3 = 0;
    if (tempb2<=0.5) {
        tempb3 = tempb1*tempb2*2;
    }else if (tempb2>0.5) {
        tempb3 = clamp((1-(2*(1-tempb1)*(1-tempb2))));
    }
    tempb3 = tempb3*255 + 0.5f;
    return static_cast<unsigned char>(tempb3);
}

Image overlay_func(const string& path1, const string& path2, const string& outputPath) {
    Image image1, image2, image3;
    image1.read(path1);
    image2.read(path2);
    image3 = image1;
    if (image1.header.getImageSize() != image2.header.getImageSize()) {
        cout << "Error: Image size mismatch!" << endl;
        return image1;
    }
    for (int i = 0; i < image1.header.getImageSize(); i++) {
       image3.pixels[i].blue = overlay_char(image1.pixels[i].blue,image2.pixels[i].blue);
       image3.pixels[i].green = overlay_char(image1.pixels[i].green,image2.pixels[i].green);
       image3.pixels[i].red = overlay_char(image1.pixels[i].red,image2.pixels[i].red);
    }
    image3.write(outputPath);
    return image3;
}


Image modify_color_channel(const string& input, const string& output, int channel, int mod, int scale) {
    Image image;
    image.read(input);
    unsigned char c = 0;
    for (int i = 0; i < image.header.getImageSize(); i++) {
        if (channel == 1) c = image.pixels[i].blue;
        else if (channel == 2) c = image.pixels[i].green;
        else if (channel == 3) c = image.pixels[i].red;

        int temp_channel = static_cast<int>(c); // source: geeks for geeks
        temp_channel = temp_channel+mod;
        temp_channel = temp_channel*scale;
        temp_channel = clamp(temp_channel);
        c =  static_cast<unsigned char>(temp_channel); // source: geeks for geeks

        if (channel == 1)  image.pixels[i].blue = c;
        else if (channel == 2)  image.pixels[i].green = c;
        else if (channel == 3)  image.pixels[i].red = c;;
    }
    image.write(output);
    return image;
}

Image isolate_color_channel(const string& input, const string& output, int channel) {
    Image image;
    image.read(input);
    unsigned char c = 0;
    for (int i = 0; i < image.header.getImageSize(); i++) {
        if (channel == 1) c = image.pixels[i].blue;
        else if (channel == 2) c = image.pixels[i].green;
        else if (channel == 3) c = image.pixels[i].red;
        image.pixels[i].blue = c;
        image.pixels[i].green = c;
        image.pixels[i].red = c;
    }
    image.write(output);
    return image;
}

Image load_color_channel(const string& input, const string& output, int channel, const string& seed = "") {
    Image image,image3;
    image.read(input);
    if (seed.length() != 0) {
        image3.read(seed);
    }else {
        image3.read(output);
    }
    unsigned char c = 0;
    for (int i = 0; i < image.header.getImageSize(); i++) {
        if (channel == 1) image3.pixels[i].blue = image.pixels[i].blue;
        else if (channel == 2) image3.pixels[i].green = image.pixels[i].green;
        else if (channel == 3) image3.pixels[i].red = image.pixels[i].red;
    }
    image3.write(output);
    return image3;
}

Image rotate_image_180(const string& input, const string& output) {
    Image image;
    image.read(input);
    vector<Pixel> temp_pixels(image.pixels.size());
    for (int i = 0; i < image.header.getImageSize(); i++) {
        temp_pixels[i] = image.pixels[image.header.getImageSize()-1-i];
    }
    for (int i = 0; i<image.header.getImageSize();i++) {
        image.pixels[i] = temp_pixels[i];
    }
    image.write(output);
    return image;
}

#endif //IMAGE_PROCESSING_H
