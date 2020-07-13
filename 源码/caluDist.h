#pragma once
#include "CPart.h"
#include "CLayout.h"


const int partNum=17;
//the max coat is 1153 total weight = 499 (the optimal solution = 1153)

/*const int AreaWidth = 200;
const int AreaHeight = 200;
const int AreaWeight = 2000;

*/
/*
const int CON_VOLUME = AreaWidth*AreaHeight ;  //背包的容积 这里当做面积
const int CON_WEIGHT = AreaWeight;//重量
*/

class caluDist
{
private:
    //修改
    //
    int getMaxDeadLine()
    {
        int max=0;
        for (int i = 0; i < partNum; i++)
        {
            if(this->C[i][3]>max)
                max=this->C[i][3];
        }
        return max;
    }

    void deadLineInv()
    {
        int max=getMaxDeadLine();
        for (int i = 0; i < partNum; i++)
            this->C[i][3]=max-this->C[i][3];
    }

public:
    static int AreaWidth;
    static int AreaHeight;
    static int AreaWeight;

    double (*C)[4];

    caluDist(double C[Num][4])
    {
        this->C=C;
        this->InitTestPart();
    }

    //测试数据
    CPart testData[partNum];
    void InitTestPart()
    {
        for (int i = 0; i < partNum; i++)  // 宽 ，高 ，重量 ，数量
        {
            double weight, width, height;
            width = C[i][0];
            height = C[i][1];
            weight = C[i][2];
            //cout << "Weight: " << C[i][2] << endl;
            testData[i].setInfo(width, height, weight);
            testData[i].setAmount(C[i][3]);
            testData->setId(i);
            //cout << "Weight: " << testData[i].getWeight() << endl;
        }
    }

    //矩阵表示两两结点之间的体积
    double allDistance[partNum][partNum];
    double allWeight[partNum][partNum];

    //计算两个货物的累加体积
    double calculateDistance(int i, int j)
    {
        //return (C[i][0] + C[j][0]);
        return testData[i].getArea() + testData[j].getArea();
    }

    double calculateWeight(int i, int j)
    {
        //return (C[i][0] + C[j][0]);
        return testData[i].getWeight() + testData[j].getWeight();
    }

    //由矩阵表示两两货物之间的体积 这里改完之后应该是面积
    void calculateAllDistance()
    {
        for (int i = 0; i < partNum; i++)
        {
            for (int j = 0; j < partNum; j++)
            {
                if (i != j)
                {
                    allDistance[i][j] = testData[j].getArea(); //fix:改成截止日期
                    allDistance[j][i] = testData[i].getArea();
                }
                else
                    allDistance[i][j] = testData[j].getArea();
            }
        }
    }
    //由矩阵表示两两货物之间的重量
    void calculateAllWeight()
    {
        for (int i = 0; i < partNum; i++)
        {
            for (int j = 0; j < partNum; j++)
            {
                if (i != j)
                {
                    allWeight[i][j] = calculateWeight(i, j);
                    allWeight[j][i] = allWeight[i][j];
                }
                else
                    //allDistance[i][j] = C[i][0];
                    allWeight[i][j] = testData[i].getWeight();
            }
        }
    }

    //获得经过n个结点的路径得到的总体积
    double calculateSumOfDistance(int* tour, double& utilization)
    {
        double sumVolume = 0;
        double sumCost = 0;
        CLayout Layout;
        Layout.Init(AreaWidth, AreaHeight, AreaWeight,partNum);
        CPart copyData[partNum];//将原始数据复制到里面，不然放入的时候会改变零件的数量
        for (int i = 0; i < partNum; i++)
        {
            copyData[i] = testData[i];
        }
        sumCost = Layout.Calculate(tour, copyData);
        //cout << "Calculate: sumCost: " << sumCost << endl;

        utilization = sumVolume / AreaWidth*AreaHeight ;
        return sumCost;
    }
};
