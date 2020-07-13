#include "ant.h"
#include <math.h>
//const double alpha = 2, beta = 4, rou = 0.6, alpha1 = 0.1, qzero = 0.01;
double AntColonySystem::totalCost;

//计算当前节点到下一节点转移的概率
double AntColonySystem::Transition(int i, int j)
{
    if (i != j)
    {
        return (pow(info[i][j], MainWindow::alpha) * pow(visible[i][j], MainWindow::beta)); //第一个参数是已经选的
    }
    else
    {
        return 0.0;
    }
}
//局部更新规则
void AntColonySystem::UpdateLocalPathRule(int i, int j)
{
    //i是当前节点，只调向下一个节点转移的概率
    info[i][j] = (1.0 - MainWindow::alpha1) * info[i][j];
}
//初始化
void AntColonySystem::InitParameter(CPart testData[partNum], double allDistance[partNum][partNum])
{
    //初始化路径上的信息素强度tao0
    for (int i = 0; i < partNum; i++)
    {
        for (int j = 0; j < partNum; j++)
        {
            info[i][j] = allDistance[i][j];
            info[j][i] = allDistance[j][i];
            if (i != j)
            {
                visible[i][j] = testData[j].getArea(); //这里有使用allDistance初始化
            }
        }
    }
}

//全局信息素更新
void AntColonySystem::UpdateGlobalPathRule(int* bestTour, int gloalbestValue) //fix:此函数要改，入炉序列生成后根据时间调整
{
    for(int i=0;i<partNum;i++)
    {
        for(int j=0;j<partNum;j++)
            info[i][j]*=(1-MainWindow::rou); //挥发
    }

    for (int i = 0; i < partNum; i++)
    {
        int row = *(bestTour + 2 * i);
        int col = *(bestTour + 2 * i + 1);
        info[row][col] += MainWindow::rou * gloalbestValue; //只给最优路径中节点增加
    }
}



//开始搜索
int* ACSAnt::Search()
{
    currentNode = startNode;
    int toNode;
    currentTourIndex = 0;
    for (int i = 0; i < partNum; i++)
    {
        allowed[i] = 1;
    }
    allowed[currentNode] = 0;
    int endNode;
    int count = 0;
    do
    {
        count++;
        endNode = currentNode;
        toNode = Choose();
        if (toNode >= 0)
        {
            MoveToNextNode(toNode);
            antColony->UpdateLocalPathRule(endNode, toNode); //end是当前节点
            currentNode = toNode;
        }
    } while (toNode >= 0);
    MoveToNextNode(startNode);
    antColony->UpdateLocalPathRule(endNode, startNode);

    return *Tour;
}

//选择下一节点
int ACSAnt::Choose()
{
    int nextNode = -1;
    double q = rand() / (double)RAND_MAX;
    //如果 q <= q0,按先验知识，否则则按概率转移，
    if (q <= MainWindow::qzero)
    {
        double probability = -1.0;//转移到下一节点的概率
        for (int i = 0; i < partNum; i++)
        {
            //去掉禁忌表中已走过的节点,从剩下节点中选择最大概率的可行节点
            if (1 == allowed[i])
            {
                double prob = antColony->Transition(currentNode, i); //第一个参数是已经选的
                if (prob > probability)
                {
                    nextNode = i;
                    probability = prob;
                }
            }
        }
    }
    else
    {
        //按概率转移
        double p = rand() / (double)RAND_MAX;//生成一个随机数,用来判断落在哪个区间段
        double sum = 0.0;
        double probability = 0.0;//概率的区间点，p 落在哪个区间段，则该点是转移的方向
        //计算概率公式的分母的值
        for (int i = 0; i < partNum; i++)
        {
            if (1 == allowed[i])
            {
                sum += antColony->Transition(currentNode, i);
            }
        }
        for (int j = 0; j < partNum; j++)
        {
            if (1 == allowed[j] && sum > 0)
            {
                probability += antColony->Transition(currentNode, j) / sum;
                if (probability >= p || (p > 0.9999 && probability > 0.9999))
                {
                    nextNode = j;
                    break;
                }
            }
        }
    }
    return nextNode;
}

//移动到下一节点
void ACSAnt::MoveToNextNode(int nextNode)
{
    //这里是不是要根据零件的数量修改？
    allowed[nextNode] = 0;
    Tour[currentTourIndex][0] = currentNode;
    Tour[currentTourIndex][1] = nextNode;
    currentTourIndex++;
    currentNode = nextNode;
}
