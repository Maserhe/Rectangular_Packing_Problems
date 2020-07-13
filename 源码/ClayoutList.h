#pragma once
//#include "List"
#include "CPart.h"
class CLayoutList
{
private:
    double x;//零件的x坐标
    double y;//零件的y坐标
    double w;//零件的宽
    double h;//零件的高
    double dWeightUsed;
    int bTrans;//放置的时候是否转置
    int nHorizonAmount;//横向个数
    int nVerticalAmount;//纵向个数
    CPart Part;
public:
    CLayoutList() {}
    ~CLayoutList() {}
    double getX() { return x; }
    double getY() { return y; }
    double getW() { return w; }
    double getH() { return h; }
    double getHorizonAmount() { return nHorizonAmount; }
    double getVerticalAmount() { return nVerticalAmount; }
    double getWeightUsed() { return dWeightUsed; }
    CPart getPart() { return this->Part; }
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    void setW(double w) { this->w = w; }
    void setH(double h) { this->h = h; }
    void setHorizonAmount(int nHorizonAmount) { this->nHorizonAmount = nHorizonAmount; }
    void setVerticalAmount(int nVerticalAmount) { this->nVerticalAmount = nVerticalAmount; }
    void setWeightUsed(double dWeight) { this->dWeightUsed = dWeight; }
    void setPart(CPart Part) { this->Part = Part; }
};



