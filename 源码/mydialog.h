#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QPen>
#include <vector>
#include <QColor>
#include "clayout.h"
const int Num = 50;

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    int w_height, w_width;
    //void move(int offset_x, int offset_y) {}
    int leftX, leftY;
    int length, width;
    int orientedF;

    void init(int x, int y, int len, int wid, int w_hei, int w_wid);
    explicit MyDialog(QWidget *parent = nullptr);

    void draw();
    void display(double n);  //显示资源利用率
    void  paintEvent( QPaintEvent * );//自动调用
    static int num;
    int map[Num][5];
    ~MyDialog();



private:
    Ui::MyDialog *ui;


};

#endif // MYDIALOG_H
