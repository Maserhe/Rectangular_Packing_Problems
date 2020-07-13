#include "mainwindow.h"
/*
#include "CPart.h"
#include "CAreaList.h"
#include "CLayoutList.h"
#include "CLayout.h"
#include "ant.h"
#include <time.h>
#include <ctype.h> */
#include <QApplication>


//最大循环次数NcMax
int NcMax = 500;

int CargoNum[partNum];  //number of each type cargo



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
