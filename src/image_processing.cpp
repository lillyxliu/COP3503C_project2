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


