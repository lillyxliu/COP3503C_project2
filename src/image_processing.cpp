//
// Created by lilly on 3/21/2025.
//

#include "image_processing.h"

// Clamping Function
//template <typename T>
int clamp(int num) {
    if (num>255) return 255;
    if (num<0) return 0;
    return num;
}

unsigned char multiply_char(unsigned char c1, unsigned char c2) {
    return clamp(static_cast<unsigned char>(((((static_cast<float>(c1)/255) * (static_cast<float>(c2)/255))*255)+0.5f)));
}

Pixel multiply_pixel( Pixel &p1,  Pixel &p2) {
    return Pixel( multiply_char(p1.blue, p2.blue),multiply_char(p1.green, p2.green), multiply_char(p1.red, p2.red));
}

void multiply_func(const string& path1, const string& path2, const string& outputPath) {
    Image image1, image2;
    image1.read(path1);
    image2.read(path2);

    if (image1.header.getImageSize() != image2.header.getImageSize()) {
        cout << "Error: Image size mismatch!" << endl;
        return;
    }

    for (int i = 0; i < (image1.header.width * image1.header.height); i++) {
        image1.pixels[i] = multiply_pixel(image1.pixels[i],image2.pixels[i]);
    }
    image1.write(outputPath);
}

void modify_color_channel(const string& input, const string& output, int channel, int mod) {
    Image image;
    image.read(input);
    unsigned char c = 0;
    for (int i = 0; i < image.header.getImageSize(); i++) {
        if (channel == 1) c = image.pixels[i].blue;
        else if (channel == 2) c = image.pixels[i].green;
        else if (channel == 3) c = image.pixels[i].red;

        int temp_channel = static_cast<int>(c); // source: geeks for geeks
        temp_channel = temp_channel+mod;
        temp_channel = clamp(temp_channel);
        c =  static_cast<unsigned char>(temp_channel); // source: geeks for geeks
    }
    image.write(output);
}

