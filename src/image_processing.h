//
// Created by lilly on 3/21/2025.
//

#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#pragma once
using namespace std;


int clamp(int num);

unsigned char multiply_char(unsigned char c1, unsigned char c2);

Pixel multiply_pixel( Pixel &p1,  Pixel &p2);

void multiply_func(const string& path1, const string& path2, const string& outputPath);

void subtract_fun(const string& path1, const string& path2, const string& outputPath);

void modify_color_channel(const string& input, const string& output, int channel, int mod);

#endif //IMAGE_PROCESSING_H
