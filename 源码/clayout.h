#pragma once
#define ANT_MAX_COUNT 50
#include "CAreaList.h"
#include "CLayoutList.h"
#include "CPart.h"
#include <list>
#include "mydialog.h"
#include <tchar.h>
using namespace std;
class CLayout
{

public:
    double m_dHeight;
    double m_dWidth;
    double m_dWeight;//重量
    //double m_dWeightLeft[ANT_MAX_COUNT];//重量剩余
    double m_dWeightLeft;//重量剩余
    double m_dUsedArea;
    int nPartsAmount;
    list<CAreaList> m_lstAvailable;
    list<CAreaList> m_lstUseless;
    list<CLayoutList> m_lstLayout;

    CLayout() {}
    ~CLayout() {}
    void Init(double dAreaWidth, double dAreaHeight, double dAreaWeight,int nPartsAmount);//初始化区域
    int CanBePutIn(CPart Part);
    int PutIn(CPart& Part, bool bTrans);//返回装入的数量 引用为了修改零件的剩余重量
    double UpdateList(double dWidth, double dHeight, int nHorizonAmount, int nVerticalAmount, CPart Part, double dWeight);
    void Merge();
    void FindUseless(CPart* data);
    double Calculate(int* tour, CPart* Part);
    list<CAreaList>::iterator getAvaliableBegin() { return m_lstAvailable.begin(); }
    list<CAreaList>::iterator getAvaliableEnd() { return m_lstAvailable.end(); }
    void testMerge();
    void showLayoutList();
    void showLayoutPartNo();
    int getLayoutListSize() { return this->m_lstLayout.size(); }
    int AvailSize() { return m_lstAvailable.size(); }
};

