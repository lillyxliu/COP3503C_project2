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
/*
void task_2() {
    subtract_fun("input/car.tga","input/layer2.tga","output/part2.tga");
    cout << "done task 2" << endl;
}*/
void task_6() {
    modify_color_channel("input/car.tga","output/part6.tga", 2,200);
    cout << "done task 6"<< endl;

}

int main() {
    task_1();
  //  task_2();
    task_6();

    return 0;
}