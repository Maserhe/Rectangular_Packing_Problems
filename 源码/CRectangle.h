#pragma once
//#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <string>
using namespace std;
//int nwidth = 800, nheight = 600;
//double w, h;
class CRectangle {
public:
    CRectangle(int x, int y, int len, int wid, int w_hei, int w_wid) : leftX(x), leftY(y), length(len), width(wid) {
        orientedF = 0;
        w_width = w_wid;
        w_height = w_hei;
    }

    int w_height, w_width;
    //void move(int offset_x, int offset_y) {}
    int leftX, leftY;
    int length, width;
    int orientedF;
};
