#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>

#include "Image.h"  //#include "Image.cpp"
#include "image_processing.h" //#include "image_processing.cpp"

using namespace std;

void task_1() {
    multiply_func("input/layer1.tga", "input/pattern1.tga", "output/part1.tga");
    cout << "done task 1" << endl;
}

void task_6() {
    Image image;
    image.read("input/car.tga");
    int imageSize = image.header.width * image.header.height;
    for (int i = 0; i < imageSize; i++) {
        //  cout << "inside" << endl;
        int temp_green = static_cast<int>(image.pixels[i].green); // source: geeks for geeks
        //cout << "temp_green:" << temp_green << endl;
        temp_green = temp_green+200;
        // cout << "+200:" << temp_green << endl;
        temp_green = clamp(temp_green);
        // cout << "clamp:" << temp_green << endl;
        image.pixels[i].green =  static_cast<unsigned char>(temp_green); // source: geeks for geeks
    }
    //image.pixels[i].green = clamp(image.pixels[i].green+200);
    image.write("output/part6.tga");
    cout << "done task 6"<< endl;

}

int main() {
    task_1();
    task_6();

    return 0;
}