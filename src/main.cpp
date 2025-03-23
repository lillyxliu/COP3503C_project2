#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>

#include "image_processing.h"

using namespace std;


void task_1() {
    multiply_func("input/layer1.tga", "input/pattern1.tga", "output/part1.tga");
    cout << "done task 1" << endl;
}

void task_2() {
    subtract_func("input/car.tga","input/layer2.tga","output/part2.tga");
    cout << "done task 2" << endl;
}

void task_3() {
    Image image23;
    image23 = multiply_func("input/layer1.tga", "input/pattern2.tga","");
    screen_func(image23,"input/text.tga","output/part3.tga");
    cout << "done task 3" << endl;
}

void task_4() {
    Image image7;
    image7 = multiply_func("input/layer2.tga","input/circles.tga","");
    image7.write("output/testimage7.tga");
    subtract_func(image7,"input/pattern2.tga","output/part4.tga");
    cout << "done task 4" << endl;
}

void task_5() {
    overlay_func("input/layer1.tga", "input/pattern1.tga", "output/part5.tga");
    cout << "done task 5" << endl;
}

void task_6() {
    modify_color_channel("input/car.tga","output/part6.tga", 2,200);
    cout << "done task 6"<< endl;

}

void task_7() {
    modify_color_channel("input/car.tga","output/part7.tga", 1,0,0);
    modify_color_channel("output/part7.tga","output/part7.tga", 3,0,4);
    cout << "done task 7" << endl;
}

void task_8() {
    isolate_color_channel("input/car.tga","output/part8_b.tga",1);
    isolate_color_channel("input/car.tga","output/part8_g.tga",2);
    isolate_color_channel("input/car.tga","output/part8_r.tga",2);
    cout << "done task 8" << endl;
}

void task_9() {
    load_color_channel("input/layer_blue.tga","output/task9.tga",1, "input/layer_blue.tga");
    load_color_channel("input/layer_green.tga","output/task9.tga",2);
    load_color_channel("input/layer_red.tga","output/task9.tga",3);
    cout << "done task 9" << endl;
}

void task_10() {
    rotate_image_180("input/text2.tga","output/part10.tga");
    cout << "done task 10" << endl;
}

int main() {
    task_1();
    task_2();
    task_3();
    task_4();
    task_5();
    task_6();
    task_7();
    task_8();
    task_9();
    task_10();

    return 0;
}