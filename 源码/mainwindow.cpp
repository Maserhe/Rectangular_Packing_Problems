#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextCodec>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include <QTextStream>
#include <tchar.h>
#include <qDebug>

double MainWindow::alpha = 2 , MainWindow::beta = 4, MainWindow::rou = 0.6, MainWindow::alpha1 = 0.1 , MainWindow::qzero = 0.01 ;
double MainWindow::A[partNum][4] = {{0,0,0,0}};
int MainWindow::antNum = 15;
//int MainWindow::AreaWidth = 200 , MainWindow::AreaHeight = 200 , MainWindow::AreaWeight = 2000;
int MainWindow::partNum_t = 17;

int caluDist::AreaWidth = 200;
int caluDist::AreaHeight = 200;
int caluDist::AreaWeight = 2000;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //确定水平方向上有多少列
    ui->tableWidget->setColumnCount(4);
    //设置水平方向的头
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"宽度"<<"高度"<<"重量"<<"数量");
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    for(int i = 0 ; i < 4; i ++ )ui->tableWidget->setColumnWidth(i,80);
    ui->tableWidget->setRowCount(50);


    //QspinBox  获取alpha, 信息启发因子
    connect(ui->doubleSpinBox,&QDoubleSpinBox::textChanged,[=](){
        MainWindow::alpha = ui->doubleSpinBox->text().toDouble();
    });
    //QspinBox  获取 beta, 期望启发因子
    connect(ui->doubleSpinBox_2,&QDoubleSpinBox::textChanged,[=](){
        MainWindow::beta = ui->doubleSpinBox_2->text().toDouble();
    });

    //QspinBox  获取 rou, 全局信息素挥发参数，
    connect(ui->doubleSpinBox_3,&QDoubleSpinBox::textChanged,[=](){
        MainWindow::alpha = ui->doubleSpinBox_3->text().toDouble();
    });
    //QspinBox  获取 alpha1, 局部信息素挥发参数
    connect(ui->doubleSpinBox_4,&QDoubleSpinBox::textChanged,[=](){
        MainWindow::alpha1 = ui->doubleSpinBox_4->text().toDouble();
    });
    //QspinBox  获取 Qzero, , 状态转移公式中的q0
    connect(ui->doubleSpinBox_5,&QDoubleSpinBox::textChanged,[=](){
        MainWindow::qzero = ui->doubleSpinBox_5->text().toDouble();
    });

    //蚂蚁数量
    /*connect(ui->lineEdit_2,&QLineEdit::textEdited,[=](){
       MainWindow::antNum = ui->lineEdit_2->text().toInt();
    }); */

    //加载文件
    connect(ui->pushButton,&QPushButton::clicked,[=](){

         QString path = QFileDialog::getOpenFileName(this,"打开文件","E:\\杂烩\\"); //默认打开目录
         if(path.isEmpty())
         {
            QMessageBox::warning(this,"警告","打开失败");
         }
         else{
             //将路径 放入到lineEdit
             ui->lineEdit->setText(path);

             //QFile File("E:\\杂烩\\qtData1.txt");
             QFile File(path);
             File.open(QFileDevice::ReadWrite);

             QTextStream in(&File);
             QString str; // 读取每行的三个信息
             partNum_t = str.count();  //获取，每行个数
             QStringList strList = in.readAll().split(QRegExp("[\r\n]"),QString::SkipEmptyParts); //截取每行
             for (int i = 0; i < strList.count(); i ++ ) {
                 str = strList[i];
                 QStringList strlist_t = str.split(" ");
                 ui->tableWidget->setItem(i,0,new QTableWidgetItem(strlist_t[0]));
                 ui->tableWidget->setItem(i,1,new QTableWidgetItem(strlist_t[1]));
                 ui->tableWidget->setItem(i,2,new QTableWidgetItem(strlist_t[2]));
                 ui->tableWidget->setItem(i,3,new QTableWidgetItem(strlist_t[3]));

                 A[i][0] =  QString(strlist_t[0]).toDouble();
                 A[i][1] =  QString(strlist_t[1]).toDouble();
                 A[i][2] =  QString(strlist_t[2]).toDouble();
                 A[i][3] =  QString(strlist_t[3]).toDouble();
             }


         }


     });

    //更改矩形的大小  宽
    connect(ui->lineEdit_2,&QLineEdit::textChanged,[=](){
        caluDist::AreaWidth = ui->lineEdit_2->text().toInt();

    });
    //更改矩形的大小  高
    connect(ui->lineEdit_3,&QLineEdit::textChanged,[=](){
        caluDist::AreaHeight = ui->lineEdit_3->text().toInt();
    });
    //更改矩形的大小  承重
    connect(ui->lineEdit_4,&QLineEdit::textChanged,[=](){
        caluDist::AreaWeight = ui->lineEdit_4->text().toInt();
    });

    //执行确定按钮
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){


        caluDist cd(A); //包含初始化测试数据


        int NcMax = 500;
        int start = 1;
        //绘图
        dialog = new MyDialog(this);
        dialog->setModal(true);
        dialog->num = 0;  //注意要把，dialog 里面的数据清零


        if (start)
        {
            time_t timer, timerl;

            time(&timer);
            unsigned long seed = timer;
            seed %= 56000;
            srand((unsigned int)seed);

            //由矩阵表示两两城市之间的距离
            cd.calculateAllDistance();
            //蚁群系统对象
            AntColonySystem* acs = new AntColonySystem();
            ACSAnt* ants[antNum];
            //蚂蚁均匀分布在城市上
            for (int k = 0; k < antNum; k++)
            {
                ants[k] = new ACSAnt(acs, (int)(k % partNum));
            }
            cd.calculateAllDistance();
            cd.calculateAllWeight();
            //随机选择一个节点计算由最近邻方法得到的一个长度
            int node = rand() % partNum;

            AntColonySystem::totalCost = CalAdjacentDistance(node,cd);

            //各条路径上初始化的信息素强度
            acs->InitParameter(cd.testData,cd.allDistance);

            //全局最优路径
            int globalTour[partNum][2];
            //全局最优长度
            double gloalbestValue = 0.0;
            for (int i = 0; i < NcMax; i++)
            {
                //局部最优路径
                int localTour[partNum][2];
                //局部最优长度
                double localBestValue = 0.0;
                //当前路径长度
                double tourCost;
                double tourUtil = 0;
                for (int j = 0; j < antNum; j++) //每个蚂蚁行动
                {
                    CLayout Layout;
                    Layout.Init(caluDist::AreaWidth, caluDist::AreaHeight, caluDist::AreaWeight, partNum);
                    CPart testCopy[partNum];
                    for (int i = 0; i < partNum; i++)
                    {
                        testCopy[i] = cd.testData[i];
                    }
                    int* tourPath = ants[j]->Search();
                    tourCost = cd.calculateSumOfDistance(tourPath, tourUtil);			//计算每个链的总价值和利用率
                    //tourCost = Layout.Calculate(tourPath, tourUtil, testCopy);		//计算每个链的总价值和利用率
                    //tourWeight = calculateSumOfWeight(tourPath, tourUtil2);//计算重量利用率
                    //qDebug() << "Main: tourWeight: " << tourWeight << endl;
                    //局部比较，并记录路径和长度
                    //if ((tourCost > localBestValue || abs(localBestValue - 0.0) < 0.000001) && tourWeight <= CON_WEIGHT)
                    if (tourCost > localBestValue || abs(localBestValue - 0.0) < 0.000001)
                    {
                        //qDebug() << "Main: tourWeight: " << tourWeight << endl;
                        for (int m = 0; m < partNum; m++)
                        {
                            int row = *(tourPath + 2 * m);
                            int col = *(tourPath + 2 * m + 1);
                            localTour[m][0] = row;
                            localTour[m][1] = col;
                        }
                        localBestValue = tourCost;
                    }
                }
                //全局比较，并记录路径和长度
                //if ((localBestValue > gloalbestValue || abs(gloalbestValue - 0.0) < 0.000001) && tourWeight <= CON_WEIGHT)
                if (localBestValue > gloalbestValue || abs(gloalbestValue - 0.0) < 0.000001)
                {
                    for (int m = 0; m < partNum; m++)
                    {
                        globalTour[m][0] = localTour[m][0];
                        globalTour[m][1] = localTour[m][1];
                    }
                    gloalbestValue = localBestValue;
                }
                acs->UpdateGlobalPathRule(*globalTour, gloalbestValue);
                //输出所有蚂蚁循环一次后的迭代最优路径
                qDebug() << "Iterative optimal path " << i + 1 << localBestValue << "." << endl;
                for (int m = 0; m < partNum; m++)
                {
                    qDebug() << localTour[m][0] << ".";
                    //CargoNum[m] = 0;
                }
                qDebug() << endl;
            }
            //输出全局最优路径
            qDebug() << "Total value:" << gloalbestValue << endl;

            qDebug() << "Loading result:";
            double sum = 0;
            double sumWeight = 0;


            CLayout Layout;
            Layout.Init(caluDist::AreaWidth, caluDist::AreaHeight, caluDist::AreaWeight, partNum);
            CPart copyData[partNum];//将原始数据复制到里面，不然放入的时候会改变零件的数量
            for (int i = 0; i < partNum; i++)
            {
                copyData[i] = cd.testData[i];
            }

            int tour[partNum];
            for (int i = 0; i < partNum; i++)
            {
                tour[i] = globalTour[i][0];
                copyData[i].setId(i);
            }
            sum=Layout.Calculate(tour, copyData);
            qDebug() << endl;
            //AreaWidth*AreaHeight 背包容积
            qDebug() << "Total volume:" << sum << " Utilization ratio:" << sum / (caluDist::AreaWidth*caluDist::AreaHeight) << endl;
            qDebug() << "Total weight:" << sumWeight << endl;
            time(&timerl);
            double t = timerl - timer;
            //qDebug() << testData[globalTour[0][0]].getHeight() << " " << testData[globalTour[0][0]].getWidth() << endl;

            //Layout.showLayoutList();

            // 绘图   我的
            auto itLayoutList = Layout.m_lstLayout.begin();
            int grapWidth = 750, grapHeight = 650;
            dialog->resize(grapWidth,grapHeight);

            //initgraph(grapWidth, grapHeight);
            //int panelWidth = 300, panelHeight = 200;  //一个平板车尺寸
            //leftX(x), leftY(y), length(len), width(wid)

            dialog->init(0, 0, caluDist::AreaWidth, caluDist::AreaHeight, grapWidth, grapHeight);

            //CRectangle panel(0, 0, panelWidth, panelHeight, grapWidth, grapHeight); //创建平板车对象
            dialog->draw(); //画平板车 .


            //TCHAR s[3];
            //int i = 0;
            for (; itLayoutList != Layout.m_lstLayout.end(); itLayoutList++)
            {
                dialog->init(itLayoutList->getX(), itLayoutList->getY(), itLayoutList->getW(), itLayoutList->getH(), grapWidth, grapHeight);
                //CRectangle part(itLayoutList->getX(), itLayoutList->getY(), itLayoutList->getW(), itLayoutList->getH(), grapWidth, grapHeight);
                dialog->draw();
                qDebug() << "X: " << itLayoutList->getX() << " Y: " << itLayoutList->getY() << " H: " << itLayoutList->getH() << " W: " << itLayoutList->getW() << " ";
                qDebug() << "Width: " << itLayoutList->getPart().getWidth() * itLayoutList->getHorizonAmount() << " Height: " << itLayoutList->getPart().getHeight() * itLayoutList->getVerticalAmount() << " HorizonAmount: " << itLayoutList->getHorizonAmount() << " VerticalAmount: " << itLayoutList->getVerticalAmount() << endl;
                //swprintf_s(s, _T("%d"), itLayoutList->getPart().getID());
                //int Id = itLayoutList->getPart().getID();
                //swprintf_s(s, _T("%d"), Id);

                //outtextxy(tranX + part.leftX + part.length / 3, grapHeight - part.leftY - part.width/ 2 - tranY, s); //标注数字
                //i++;
                dialog->display(sum / (caluDist::AreaWidth*caluDist::AreaHeight));
                dialog->update();

            }



            qDebug() << Layout.AvailSize() << endl;
            qDebug() << "Number of parts:" << Layout.getLayoutListSize() << endl;
            qDebug() << "time:" << t << endl;
            Layout.showLayoutPartNo();
            //dialog->settableWidget(Layout);
            dialog->show();
            //initgraph(640, 480);
            //setorigin(0,0);
        }



    });


}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::ChooseNextNode(int currentNode, int visitedNode[], double allDistance[partNum][partNum])
{
    int nextNode = -1;
    double shortDistance = 0.0;
    for (int i = 0; i < partNum; i++)
    {
        //去掉已走过的节点,从剩下节点中选择距离最近的节点
        if (1 == visitedNode[i])
        {
            if (shortDistance == 0.0)
            {
                shortDistance = allDistance[currentNode][i];
                nextNode = i;
            }
            if (shortDistance < allDistance[currentNode][i]) //
            {
                nextNode = i;
            }
        }
    }
    return nextNode;
}
//
double MainWindow::CalAdjacentDistance(int node, caluDist &cd)
{
    double sumCost = 0;
    int visitedNode[partNum];
    for (int j = 0; j < partNum; j++)
    {
        visitedNode[j] = 1;
    }
    visitedNode[node] = 0;
    int currentNode = node;
    int nextNode;
    do
    {
        nextNode = ChooseNextNode(currentNode, visitedNode, cd.allDistance);
        if (nextNode >= 0)
        {
            //sum += cd.allDistance[currentNode][nextNode] - cd.allDistance[currentNode][currentNode];
            sumCost += cd.testData[currentNode].getArea(); //fix: 改成截止日期
            currentNode = nextNode;
            visitedNode[currentNode] = 0;
        }
    } while (nextNode >= 0);
    //sum += cd.allDistance[currentNode][node] - cd.allDistance[currentNode][currentNode];

    //sumCost += C[currentNode][1];
    sumCost += cd.testData[currentNode].getArea();
    return sumCost;

}

