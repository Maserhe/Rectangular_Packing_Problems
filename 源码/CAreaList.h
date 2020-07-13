#pragma once
class CAreaList
{
    double x;//左下角的坐标
    double y;
    double Height;//区域的高度
    double Width;//区域的宽度
public:
    bool operator<(const CAreaList& t2)//这里应该是左下原则
    {
        if (x != t2.x)
        {
            return x < t2.x;//会产生升序排序
        }
        else
        {
            return y < t2.y;
        }
    }
    /*bool operator<(const CAreaList& t2)
    {
        return this->getArea() < t2.Height * t2.Width;
    }*/
    CAreaList() {};
    ~CAreaList() {};
    double getX() { return x; }
    double getY() { return y; }
    double getWidth() { return Width; }
    double getHeight() { return Height; }
    double getArea() { return Width * Height; }
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    void setWidth(double Width) { this->Width = Width; }
    void setHeight(double Height) { this->Height = Height; }
};


