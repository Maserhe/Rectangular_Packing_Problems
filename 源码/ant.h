#pragma once
#include "caluDist.h"
#include "mainwindow.h"
//信息启发因子，期望启发式因子，全局信息素挥发参数，局部信息素挥发参数, 状态转移公式中的q0
const double alpha = 2, beta = 4, rou = 0.6, alpha1 = 0.1, qzero = 0.01; //these parameters produce the best solution
//蚂蚁数量
const int antNum=15;

class ACSAnt;

class AntColonySystem
{
private:
    double info[partNum][partNum], visible[partNum][partNum];//节点之间的信息素强度,节点之间的能见度
public:
    //每个节点都可能作为源节点来遍历
    static double totalCost;
    //计算当前节点到下一节点转移的概率
    double Transition(int i, int j);
    //局部更新规则
    void UpdateLocalPathRule(int i, int j);
    //初始化
    void InitParameter(CPart testData[], double allDistance[][partNum]);
    //全局信息素更新
    void UpdateGlobalPathRule(int *bestTour, int gloalbestValue);
};


class ACSAnt
{
private:
    AntColonySystem* antColony;
protected:
    int startNode, currentNode;//初始节点编号，当前节点编号
    int allowed[partNum];//禁忌表
    int Tour[partNum][2];//当前路径
    int currentTourIndex;//当前路径索引，从0开始，存储蚂蚁经过城市的编号
public:
    ACSAnt(AntColonySystem* acs, int start)
    {
        antColony = acs;
        startNode = start;
    }
    //开始搜索
    int* Search();
    //选择下一节点
    int Choose();
    //移动到下一节点
    void MoveToNextNode(int nextNode);
};

