#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "CPart.h"
#include "CAreaList.h"
#include "CLayoutList.h"
#include "CLayout.h"
#include "ant.h"
#include <time.h>
#include <ctype.h>
#include <QMainWindow>
#include "mydialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int ChooseNextNode(int currentNode, int visitedNode[],double allDistance[partNum][partNum]);
    double CalAdjacentDistance(int node, caluDist &cd);

    static double alpha, beta, rou , alpha1 , qzero;
    //蚂蚁数量
    static int antNum;

    static double A[partNum][4];
    static int partNum_t;
private:
    Ui::MainWindow *ui;
    MyDialog *dialog;   //添加私有成员，为一个dailog（窗口）的指针
};
#endif // MAINWINDOW_H
