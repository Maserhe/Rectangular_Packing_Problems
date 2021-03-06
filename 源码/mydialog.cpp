#include "mydialog.h"
#include "ui_mydialog.h"
#include "QTimer"
#include <QTime>
#include <qDebug>
int MyDialog::num = 0;
void MyDialog::init(int x, int y, int len, int wid, int w_hei, int w_wid)
{

    leftX = x;
    leftY = y;
    length = len;
    width = wid;
    //orientedF = 0;
    w_width = w_wid;
    w_height = w_hei;
}

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//种下产生随机数的种子
}

void MyDialog::draw( )
{
    map[num][0]= leftX;
    map[num][1]=leftY;
    map[num][2]=length;
    map[num][3]=width;
    num ++;

}

void MyDialog::display(double n)
{
    ui->lcdNumber->display(n);

}



void MyDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //坐标变换
    QTransform transfrom;
    transfrom.translate(0,650);
    transfrom.rotate(180,Qt::XAxis);
    transfrom.scale(2,2);

    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;

    pen.setBrush(Qt::blue);
    painter.setPen(pen);

    QTimer t;

    for(int i = 0 ; i< num ; i++ ){
        painter.setWorldTransform(transfrom);
        //产生随机颜色
        QColor c(qrand()%256,qrand()%256,qrand()%256);
        QBrush brush(c);
        painter.setBrush(brush);
        painter.drawRect(map[i][0], map[i][1], map[i][2] ,map[i][3]);


    }

}


MyDialog::~MyDialog()
{

    delete ui;

}
