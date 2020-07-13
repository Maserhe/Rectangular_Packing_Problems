#include "CLayout.h"
#include <algorithm>
#include <iostream>
#include "caluDist.h"

using namespace std;

int RND(int nLow, int nUpper)//产生随机数
{
    return rand() % (nUpper - nLow + 1) + nLow;
}

double RND(double dbLow, double dbUpper)//产生随机数
{
    return (dbUpper - dbLow) * rand() / ((double)RAND_MAX + 1.0) + dbLow;
}

/*int min(int a, int b)
{
    return a < b ? a : b;
}*/

void CLayout::Init(double dAreaWidth, double dAreaHeight, double dAreaWeight,int nPartsAmount)
{
    this->m_dWidth = dAreaWidth;
    this->m_dHeight = dAreaHeight;
    this->m_dWeight = dAreaWeight;
    this->m_dWeightLeft = dAreaWeight;
    CAreaList tmpArea;
    tmpArea.setHeight(dAreaHeight);
    tmpArea.setWidth(dAreaWidth);
    tmpArea.setX(0.0);
    tmpArea.setY(0.0);
    //cout << "Init: Y: " << tmpArea.getY() << " H: " << tmpArea.getHeight() << endl;
    this->m_lstAvailable.push_back(tmpArea);
    m_dUsedArea = 0;
    this->nPartsAmount = nPartsAmount;
}

int CLayout::CanBePutIn(CPart Part)//这里没有考虑可用空间为0的情况
{
    //-1转置 1不转置 0不能放入
    if (m_dWeightLeft < Part.getWeight() || m_lstAvailable.empty())
    {
        //cout << "CanBePutIn: WeightLeft: " << m_dWeightLeft << " PartWeight: " << Part.getWeight() << " AvailableSize: " << m_lstAvailable.size() << endl;
        //if (m_dWeightLeft < Part.getWeight())cout << "重量不够不能放置" << endl;
        //if (m_lstAvailable.empty()) cout << "没有可用空间" << endl;
        return 0;//如果重量放不下就返回0
    }
    //cout<< " AvailableSize: " << m_lstAvailable.size() << endl;
    list<CAreaList>::iterator itAvail = this->m_lstAvailable.begin();
    double dPartWidth = Part.getWidth();
    double dPartHeight = Part.getHeight();
    int nVerticalMost, nHorizonMost;//竖直、水平方向最多放置
    int nWeightMost;
    int CanbePutInMost;
    int nHorizonReal;//水平实际放置几块
    int nPutInAmount = 0;
    double dSurplusAreaWithoutTrans = -1;//
    double dSurplusAreaWithTrans = -1;//转置放置上方剩余面积

    //不转置放入
    //cout << "CanBePutIn: WithoutTrans: AvailWidth: " << itAvail->getWidth() << " PartWidth: " << dPartWidth << " ";
    nVerticalMost = int(itAvail->getHeight() / Part.getHeight());
    //cout << "CanBePutIn: AvailHeight: " << itAvail->getHeight() << " PartHeight: " << Part.getHeight() << endl;
    nWeightMost = int(m_dWeightLeft / Part.getWeight());
    CanbePutInMost = min(nWeightMost, Part.getSurplusAmount());
    //cout << "CanBePutIn: VerticalMost: " << nVerticalMost << " WeightMost: " << nWeightMost << " CanbePutInMost: " << CanbePutInMost << endl;
    if ((nVerticalMost == 0) && int(itAvail->getHeight() / Part.getWidth() == 0)) return 0;
    if (nVerticalMost > 0 && itAvail->getWidth() >= dPartWidth)
    {
        //cout << "不转置可以放入" << endl;
        if (CanbePutInMost <= nVerticalMost)
        {
            nPutInAmount = CanbePutInMost;
            dSurplusAreaWithoutTrans = dPartWidth * (itAvail->getHeight() - nPutInAmount * dPartHeight);
            //cout << "可以直接放入一列 PutInAmount: " << nPutInAmount << " SurPlusArea: " << dSurplusAreaWithoutTrans << "垂直高度: " << nPutInAmount * dPartHeight << endl;

        }
        else
        {
            nHorizonMost = int(itAvail->getWidth() / dPartWidth);
            for (nHorizonReal = 1; nHorizonReal <= nHorizonMost; nHorizonReal++)
            {
                if ((nHorizonReal * nVerticalMost) > CanbePutInMost) break;
            }
            nHorizonReal--;
            dSurplusAreaWithoutTrans = (dPartWidth * nHorizonReal) * (itAvail->getHeight() - dPartHeight * nVerticalMost);
            nPutInAmount = nHorizonReal * nVerticalMost;
            //cout << "不能直接放一列 水平数量 " << nHorizonReal << " 竖直数量 " << nVerticalMost << " SurPlusArea: " << dSurplusAreaWithoutTrans << " 水平高度 " << nHorizonReal * dPartWidth << " 竖直高度 " << nVerticalMost * dPartHeight << endl;
        }
    }
    //else cout << "不转置不可以放入" << endl;
    int nPutInAmountWithoutTrans = nPutInAmount;
    //cout << "CanBePutIn: WithoutTrans: PutInAmount: " << nPutInAmount << endl;
    //转置后放入
    //cout << "CanbePutIn Before Swap PartHeight: " << dPartHeight << " PartWidth: " << dPartWidth << endl;
    swap(dPartHeight, dPartWidth);
    /*dPartHeight = Part.getWidth();
    dPartWidth = Part.getHeight();*/
    //cout << "CanbePutIn After Swap PartHeight: " << dPartHeight << " PartWidth: " << dPartWidth << endl;
    nVerticalMost = int(itAvail->getHeight() / dPartHeight);
    nWeightMost = int(m_dWeightLeft / Part.getWeight());
    CanbePutInMost = min(nWeightMost, Part.getSurplusAmount());
    /*cout << "CanBePutIn: WithTrans: AvailWidth: " << itAvail->getWidth() << " PartWidth: " << dPartWidth << " ";
    cout << "CanBePutIn: AvailHeight: " << itAvail->getHeight() << " PartHeight: " << dPartHeight << endl;
    cout << "CanBePutIn: VerticalMost: " << nVerticalMost << " WeightMost: " << nWeightMost << " CanbePutInMost: " << CanbePutInMost << endl;*/
    if (nVerticalMost > 0 && itAvail->getWidth() >= dPartWidth)
    {
        //cout << "转置可以放入" << endl;
        if (CanbePutInMost <= nVerticalMost)
        {
            nPutInAmount = CanbePutInMost;
            dSurplusAreaWithTrans = dPartWidth * (itAvail->getHeight() - nPutInAmount * dPartHeight);
            //cout << "可以直接放入一列 PutInAmount: " << nPutInAmount << " SurPlusArea: " << dSurplusAreaWithTrans << "垂直高度: " << nPutInAmount * dPartHeight << endl;
        }
        else
        {
            nHorizonMost = int(itAvail->getWidth() / dPartWidth);
            for (nHorizonReal = 1; nHorizonReal <= nHorizonMost; nHorizonReal++)
            {
                if ((nHorizonReal * nVerticalMost) > CanbePutInMost) break;
            }
            nHorizonReal--;
            dSurplusAreaWithTrans = (dPartWidth * nHorizonReal) * (itAvail->getHeight() - dPartHeight * nVerticalMost);
            nPutInAmount = nHorizonReal * nVerticalMost;
            //cout << "不能直接放一列 水平数量 " << nHorizonReal << " 竖直数量 " << nVerticalMost << " 放入数量 " << nPutInAmount << " SurPlusArea: " << dSurplusAreaWithTrans << " 水平高度 " << nHorizonReal * dPartWidth << " 竖直高度 " << nVerticalMost * dPartHeight << endl;
        }
    }
    //else cout << "转置不可以放入" << endl;
    //cout << "CanBePutIn: WithTrans: PutInAmount: " << nPutInAmount << endl;
    //比较是否转置
    if (nPutInAmountWithoutTrans == 0 && nPutInAmount == 0) return 0;
    if (dSurplusAreaWithoutTrans <= 0 && dSurplusAreaWithTrans <= 0)return 0;
    else if (dSurplusAreaWithoutTrans <= 0 && dSurplusAreaWithTrans > 0)return -1;
    else if (dSurplusAreaWithoutTrans > 0 && dSurplusAreaWithTrans <= 0)return 1;
    //如果只放置一个 则随机决定是否转置
    else
        return dSurplusAreaWithoutTrans <= dSurplusAreaWithTrans ? 1 : -1;
}

int CLayout::PutIn(CPart& Part,bool bTrans)
{
    if (m_lstAvailable.empty()) return 0;//如果可用空间为空 返回0
    //但是这个应该在CanbePutIn里面考虑过了
    auto itAvail = m_lstAvailable.begin();
    //cout << "PutIn AreaWidth: " << itAvail->getWidth() << " AreaHeight: " << itAvail->getHeight() << endl;
    double dPartWidth = Part.getWidth();
    double dPartHeight = Part.getHeight();
    int nVerticalMost, nHorizonMost;
    int nWeightMost = int(m_dWeightLeft / Part.getWeight());
    /*cout << "PutIn: WeightLeft: " << m_dWeightLeft;
    cout << " PartWeight: " << Part.getWeight();
    cout << " WeightMost: " << nWeightMost ;*/
    int nHorizonReal;
    int nPutInAmount;
    //cout << " SurplusAMount: " << Part.getSurplusAmount() << endl;
    int nPutInMost = min(nWeightMost, Part.getSurplusAmount());//最多放置数量根据零件剩余个数和重量约束考虑
    //cout << "PutIn: dPartHeight: " << dPartHeight << " dPartWidth " << dPartWidth << " Trans: " << bTrans << endl;
    if (bTrans) swap(dPartHeight, dPartWidth);//转置就交换
    //cout << "PutIn: dPartHeight: " << dPartHeight << endl;
    //if(bTrans) cout << "After Trans PutIn: dPartHeight: " << dPartHeight << " dPartWidth " << dPartWidth << endl;
    nVerticalMost = int(itAvail->getHeight() / dPartHeight);
    nHorizonMost = int(itAvail->getWidth() / dPartWidth);
    //cout << "PutIn VerticalMost " << nVerticalMost << " HorizonMost " << nHorizonMost << endl;
    if (nVerticalMost == 0 || nHorizonMost == 0)
    {
        /*cout << "不能放置 ";
        bTrans == -1 ? cout << "转置放入 " : cout << "不转置放入" << endl;
        cout << "PutIn VerticalMost " << nVerticalMost << " HorizonMost " << nHorizonMost << endl;
        cout << "零件Height " << dPartHeight << " 零件Width " << dPartWidth << endl;*/
        return 0;
    }
    if (nPutInMost <= nVerticalMost&&itAvail->getWidth()>=dPartWidth)
    {
        nPutInAmount = nPutInMost;
        //cout << "竖着放一列 PutInMost<VerticalMost ";
        //cout << "PutInMost " << nPutInMost << " PutInAmount " << nPutInAmount << endl;
        //cout << "nPutIn nPutInMost: " << nPutInMost << endl;
        //cout << "PutIn Called" << endl;
        //cout << "PutIn 放入前零件数量 " << Part.getSurplusAmount();
        Part.changeAmount(nPutInAmount);
        //if (Part.getSurplusAmount() > 0) system("pause");
        //cout << " PutIn 放入后零件数量 " << Part.getSurplusAmount() << endl;
        //cout << "PutIn: AvailWidth: " << itAvail->getWidth() << " AvailHeight: " << itAvail->getHeight() << endl;
        //cout << "PutIn: PutInWidth: " << dPartWidth << " PutInHeight: " << dPartHeight * nPutInAmount << endl;
        /*if (nPutInAmount == 0)
        {
            cout << "PutIn PutInAmount==0" << endl;
        }*/
        //cout << "PutIn: Updatelist dWidth: " << dPartWidth << " dHeight: " << dPartHeight * nPutInAmount << " HorizonAmount: 1 VerticalAmount: " << nPutInAmount << " Weight: " << Part.getWeight() * nPutInAmount << endl;
        m_dUsedArea += UpdateList(dPartWidth, dPartHeight * nPutInAmount, 1, nPutInAmount, Part, Part.getWeight() * nPutInAmount);
        return nPutInAmount;
        //UpdateList(dPartWidth, dPartHeight * nPutInAmount, 1, nPutInAmount, Part, Part.getWeight() * 0);
        //cout << "PutIn: PutInAmount: " << nPutInAmount << endl;
        //更新区域
    }
    else
    {
        //cout << "不能全部放一列" << endl;
        nHorizonMost = int(itAvail->getWidth() / dPartWidth);
        for (nHorizonReal = 1; nHorizonReal <= nHorizonMost; nHorizonReal++)
        {
            if ((nHorizonReal * nVerticalMost) > nPutInMost) break;
        }
        nHorizonReal--;
        //cout << "PutIn HozizonReal " << nHorizonReal << endl;
        nPutInAmount = nHorizonReal * nVerticalMost;

        if (nPutInAmount == 0) return 0;
        Part.changeAmount(nPutInAmount);
        //if (Part.getSurplusAmount() > 0) system("pause");
        if (dPartHeight * nVerticalMost == 0)
        {
            //cout << "PutIn nVerticalMost:" << nVerticalMost << " bTrans: " << bTrans << endl;
            return 0;
        }
        if (nHorizonReal == 0)
        {
            //cout << "PutIN HorizonReal: " << nHorizonReal << endl;
            return 0;
        }
        //cout << "PutIn: Updatelist dWidth: " << dPartWidth * nHorizonReal << " dHeight: " << dPartHeight * nVerticalMost << " HorizonAmount "<< nHorizonReal<<" VerticalAmount: " << nVerticalMost << " Weight: " << Part.getWeight() * nPutInAmount << endl;
        m_dUsedArea += UpdateList(dPartWidth * nHorizonReal, dPartHeight * nVerticalMost, nHorizonReal, nVerticalMost, Part, Part.getWeight() * nPutInAmount);
        //UpdateList(dPartWidth * nHorizonReal, dPartHeight * nVerticalMost, nHorizonReal, nVerticalMost, Part, Part.getWeight() * 0);
    }
    return nPutInAmount;
}

double CLayout::UpdateList(double dWidth, double dHeight, int nHorizonAmount, int nVerticalAmount, CPart Part, double dWeight)
{
    m_dWeightLeft -= dWeight;//首先更新重量
    //cout << "UpdateList: AvailableSize: " << m_lstAvailable.size() << endl;
    CAreaList tmpArea;
    CLayoutList tmpLayout;
    list<CAreaList>::iterator itAvail = m_lstAvailable.begin();
    double dAvailX = itAvail->getX();//可用空间信息
    double dAvailY = itAvail->getY();
    double dAvailH = itAvail->getHeight();
    double dAvailW = itAvail->getWidth();
    //cout << "UpdateList AvailX " << dAvailX << " AvailY " << dAvailY << " AvailH " << dAvailH << " AvailW " << dAvailW << endl;
    //cout << "UpdateList UseWidth " << dWidth << " UseHeight " << dHeight << " HorizonAmount " << nHorizonAmount << " VerticalAmount " << nVerticalAmount << " UseWeight " << dWeight << endl;
    if (dAvailH > dHeight)//等宽不等高
    {
        tmpArea.setX(dAvailX);
        tmpArea.setY(dHeight + dAvailY);
        tmpArea.setWidth(dWidth);
        tmpArea.setHeight(dAvailH - dHeight);
        m_lstAvailable.push_back(tmpArea);
        //cout << "分割上面区域 X " << tmpArea.getX() << " Y " << tmpArea.getY() << " Width " << tmpArea.getWidth() << " Height " << tmpArea.getHeight() << endl;
        if (dAvailW > dWidth)//不等宽不登高
        {

            //tmpArea.setX(dAvailH + dWidth);BUG1
            tmpArea.setX(dAvailX + dWidth);
            tmpArea.setY(dAvailY);
            tmpArea.setWidth(dAvailW - dWidth);
            tmpArea.setHeight(dAvailH);
            //cout << "分割左侧区域 X " << tmpArea.getX() << " Y " << tmpArea.getY() << " Width " << tmpArea.getWidth() << " Height " << tmpArea.getHeight() << endl;
            m_lstAvailable.push_back(tmpArea);
        }
    }
    else if (dAvailH == dHeight && dAvailW > dWidth)//等高不等宽
    {
        tmpArea.setX(dAvailX + dWidth);
        tmpArea.setY(dAvailY);
        tmpArea.setWidth(dAvailW - dWidth);
        tmpArea.setHeight(dAvailH);
        //cout<<"可用和已用等高 直接分割右侧区域 X " << tmpArea.getX() << " Y " << tmpArea.getY() << " Width " << tmpArea.getWidth() << " Height " << tmpArea.getHeight() << endl;
        m_lstAvailable.push_back(tmpArea);
    }
    m_lstAvailable.erase(itAvail);


    /*if (dWidth == 0||dWidth+dAvailX>200||dHeight+dAvailY>200)
    {
        cout << "UpdateList: dAvailY: " << dAvailY << " dHeight: " << dHeight << " dWidth: " << dWidth << endl;
    }*/
    tmpLayout.setX(dAvailX);
    tmpLayout.setY(dAvailY);
    tmpLayout.setW(dWidth);
    tmpLayout.setH(dHeight);
    tmpLayout.setHorizonAmount(nHorizonAmount);
    tmpLayout.setVerticalAmount(nVerticalAmount);
    tmpLayout.setPart(Part);
    m_lstLayout.push_back(tmpLayout);
    //cout << "UpdateList 更新放置区域 X " << dAvailX << " Y " << dAvailY << " Width " << dWidth << " Height " << dHeight << " 垂直数量 " << nVerticalAmount << " 水平数量 " << nHorizonAmount << endl;
    if (!m_lstAvailable.empty())
    {
        m_lstAvailable.sort(); //排序
    }
    //cout << "UpdateList dWidth: " << dWidth << " dHeight: " << dHeight << endl;
    return dWidth * dHeight;
}

void CLayout::Merge()
{
    if (m_lstUseless.empty() || m_lstAvailable.empty()) return;//不可用或者可用为空都返回
    list<CAreaList>::iterator itAvail = m_lstAvailable.begin();
    double dAvailX = itAvail->getX();
    double dAvailY = itAvail->getY();
    double dAvailWidth = itAvail->getWidth();
    double dAvailHeight = itAvail->getHeight();
    list<CAreaList>::iterator itUseless = m_lstUseless.begin();
    for (; itUseless != m_lstUseless.end(); itUseless++)
    {
        double dUselessX = itUseless->getX();
        double dUselessY = itUseless->getY();
        double dUselessWidth = itUseless->getWidth();
        double dUselessHeight = itUseless->getHeight();
        //先判断上下相邻的情况
        if (dAvailX == dUselessX)//x坐标相邻，接下来判断是否相邻
        {
            if (dAvailY == dUselessY + dUselessHeight)//可用在废弃上面 相邻
            {
                //判断是否可以合并
                if (dUselessWidth >= dAvailWidth)
                {
                    //cout << "Merge 在可用下方 可以合并" << endl;
                    itAvail->setHeight(dAvailHeight + dUselessHeight);
                    itAvail->setY(dUselessY);
                    if (dUselessWidth > dAvailWidth)//合并后还剩下部分区域
                    {
                        CAreaList tmpArea;
                        tmpArea.setHeight(dUselessHeight);
                        tmpArea.setWidth(dUselessWidth - dAvailWidth);
                        tmpArea.setX(dAvailWidth);
                        tmpArea.setY(dUselessY);
                        m_lstUseless.erase(itUseless);
                        m_lstUseless.push_back(tmpArea);
                        //cout << "Merge Useless.Size " << m_lstUseless.size() << endl;
                    }
                    return;
                }
                else continue;//不符合合并条件 下一个废弃区域
            }
            else if (dAvailHeight + dAvailY == dUselessY)//可用在下 废弃在上
            {
                //判断是否可以合并
                //cout << "Merge 可用在下 废弃在上" << endl;
                if (dUselessWidth >= dAvailWidth)
                {
                    //cout << "Merge 在可用上方 可以合并" << endl;
                    itAvail->setHeight(dAvailHeight + dUselessHeight);
                    if (dUselessWidth > dAvailWidth)//合并后还剩下部分区域
                    {
                        CAreaList tmpArea;
                        tmpArea.setHeight(dUselessHeight);
                        tmpArea.setWidth(dUselessWidth - dAvailWidth);
                        tmpArea.setX(dAvailWidth);
                        tmpArea.setY(dUselessY);
                        m_lstUseless.erase(itUseless);
                        m_lstUseless.push_back(tmpArea);
                    }
                    return;
                }
                else continue;//不符合合并条件 下一个废弃区域
            }
        }
        //判断左右相邻的情况
        else if (dAvailY == dUselessY)
        {
            //废弃在左，可用在右
            //cout << "Merge 可用废弃纵坐标相同 " << endl;
            if (dUselessX + dUselessWidth == dAvailX)//判断相邻
            {
                //cout << "Merge 可用在左 废弃在右" << endl;
                if (dUselessHeight >= dAvailHeight)//合并条件
                {
                    itAvail->setX(dUselessX);
                    itAvail->setWidth(dUselessWidth + dAvailWidth);
                    if (dUselessHeight - dAvailHeight > 0)
                    {
                        CAreaList tmpArea;
                        tmpArea.setHeight(dUselessHeight - dAvailHeight);
                        tmpArea.setWidth(dUselessWidth);
                        tmpArea.setX(dUselessX);
                        tmpArea.setY(dUselessY+dAvailHeight);
                        m_lstUseless.erase(itUseless);
                        m_lstUseless.push_back(tmpArea);
                    }
                    return;
                }
            }
            //废弃在右，可用在左
            else if (dUselessX == dAvailWidth + dAvailX)
            {
                if (dUselessHeight >= dAvailHeight)//合并条件
                {
                    cout << "Merge 废弃在右 可用在左" << endl;
                    itAvail->setWidth(dUselessWidth + dAvailWidth);
                    if (dUselessHeight - dAvailHeight > 0)
                    {
                        CAreaList tmpArea;
                        tmpArea.setHeight(dUselessHeight - dAvailHeight);
                        tmpArea.setWidth(dUselessWidth);
                        tmpArea.setX(dUselessX);
                        tmpArea.setY(dUselessY+dAvailHeight);
                        m_lstUseless.erase(itUseless);
                        m_lstUseless.push_back(tmpArea);
                    }
                }
                return;
            }
        }
    }
}

/*void CLayout::Merge()
{
    CAreaList tmpArea;
    std::list<CAreaList>::iterator itAvail;
    std::list<CAreaList>::iterator itUseless;
    double dAvailX;  //可用空间的尺寸
    double dAvailY;
    double dAvailH;
    double dAvailW;
    double dUselessX;   //废弃空间的尺寸
    double dUselessY;
    double dUselessH;
    double dUselessW;
    if (!m_lstUseless.empty() && !m_lstAvailable.empty())    //合并
    {
        for (itUseless = m_lstUseless.begin(); itUseless != m_lstUseless.end(); itUseless++)
        {
            dUselessX = itUseless->getX();
            dUselessY = itUseless->getY();
            dUselessW = itUseless->getWidth();
            dUselessH = itUseless->getHeight();
            for (itAvail = m_lstAvailable.begin(); itAvail != m_lstAvailable.end(); itAvail++)
            {
                dAvailX = itAvail->getX();
                dAvailY = itAvail->getY();
                dAvailH = itAvail->getHeight();
                dAvailW = itAvail->getWidth();

                if (dAvailX + dAvailW == dUselessX)   //左可用右废弃=============>>>似乎不会出现这种情况
                {
                    if (dAvailY == dUselessY)  //左右一样长（高度），直接合并
                    {
                        itAvail->setWidth(dAvailW + dUselessW);   //X不变，宽度增加
                        m_lstUseless.erase(itUseless);
                        m_lstAvailable.sort(); //排序
                        return;
                    }
                    else if (dAvailY < dUselessY)   //  左长右短，横向分割成两块可用区域
                    {
                        itAvail->setHeight(dAvailH - dUselessH);
                        tmpArea.setX(dAvailX);
                        tmpArea.setY(dUselessY);
                        tmpArea.setWidth(dAvailW + dUselessW);
                        tmpArea.setHeight(dUselessH);
                        m_lstAvailable.push_back(tmpArea);
                        m_lstUseless.erase(itUseless);
                        m_lstAvailable.sort(); //排序
                        return;
                    }
                    else    //  左短右长，右下废弃
                    {
                        itUseless->setHeight(dUselessH - dAvailH);
                        itAvail->setWidth(dAvailW + dUselessW);
                    }
                }

                if (dUselessX + dUselessW == dAvailX)			//左废弃右可用
                {
                    if (dUselessY == dAvailY)  //两块一样高，直接合并
                    {
                        itAvail->setX(dUselessX);    //X左移
                        itAvail->setWidth(dAvailW + dUselessW);  //宽度增加
                        m_lstUseless.erase(itUseless);
                        m_lstAvailable.sort(); //排序
                        return;
                    }
                    else if (dUselessY < dAvailY)  //左长右短，左下废弃
                    {
                        itUseless->setHeight(dUselessH - dAvailH);
                        itAvail->setX(dUselessX);	//X左移
                        itAvail->setWidth(dAvailW + dUselessW);	//宽度增加
                        m_lstAvailable.sort(); //排序
                        return;
                    }
                    else		//  左短右长，横向分割成两块可用区域
                    {
                        itAvail->setHeight(dAvailH - dUselessH);
                        tmpArea.setX(dUselessX);
                        tmpArea.setY(dUselessY);
                        tmpArea.setWidth(dAvailW + dUselessW);
                        tmpArea.setHeight(dUselessH);
                        m_lstAvailable.push_back(tmpArea);
                        m_lstUseless.erase(itUseless);
                        m_lstAvailable.sort(); //排序
                        return;
                    }
                }
            }
        }
    }

}*/

double CLayout::Calculate(int* tour,CPart* Part)
{
    CAreaList tmpArea;
    int nPartNo;//零件编号
    int nCanBePutIn;//能否放下
    int bTrans;
    bool bUseless;//队首空间是废空间
    bool bPartExist;//是否还有待排零件
    list<CAreaList>::iterator itAvail = m_lstAvailable.begin();
    //cout << "Calculate AvailBegin X " << itAvail->getX() << " Y " << itAvail->getY() << " Height " << itAvail->getHeight() << " Width " << itAvail->getWidth() << endl;
    do
    {
        itAvail = m_lstAvailable.begin();
        /*if (!m_lstAvailable.empty())
        {
            Merge(); //合并空间
            //cout << "Calculate MergeEnd" << endl;
        }*/
        //cout << "Calculate AvailBegin X " << itAvail->getX() << " Y " << itAvail->getY() << " Height " << itAvail->getHeight() << " Width " << itAvail->getWidth() << endl;
        bUseless = true;
        bPartExist = false;
        for (int i=0;i<nPartsAmount;i++)
        {
            nPartNo = *(tour + i);
            //cout << "Calculate PartNo " << nPartNo << endl;
            if (Part[nPartNo].getSurplusAmount() > 0)
            {
                nCanBePutIn = CanBePutIn(Part[nPartNo]);
                bPartExist = true;
                int nPutInAmount = 0;
                if (nCanBePutIn != 0)
                {
                    bool bTrans = false;
                    if (nCanBePutIn == -1) bTrans = true;
                    bUseless = false;
                    break;
                    //cout << "能否放入标志 " << nCanBePutIn << endl;
                    //nPutInAmount = PutIn(Part[nPartNo], bTrans);
                    /*if (nPutInAmount == 0)
                    {
                        cout << "Calculate AvailBegin X " << itAvail->getX() << " Y " << itAvail->getY() << " Height " << itAvail->getHeight() << " Width " << itAvail->getWidth() << endl;
                        cout << "Calculate Part H" << Part[nPartNo].getHeight() << " W " << Part[nPartNo].getWidth() << endl;
                        CanBePutIn(Part[nPartNo]);
                        cout << "转置标志 " << nCanBePutIn << endl;
                        PutIn(Part[nPartNo], bTrans);
                        system("pause");
                    }
                    if (nPutInAmount != 0)
                    {
                        bUseless = false;
                        //cout << "Calculate CanPutIn" << endl;
                        break;//找到第一个待排零件
                    }*/

                }
            }
        }
        if (bUseless)
        {
            itAvail = m_lstAvailable.begin();
            tmpArea.setX(itAvail->getX());
            tmpArea.setY(itAvail->getY());
            tmpArea.setWidth(itAvail->getWidth());
            tmpArea.setHeight(itAvail->getHeight());
            m_lstUseless.push_back(tmpArea);
            m_lstAvailable.pop_front();
            if (!m_lstAvailable.empty())
            {
                Merge();
            }
            continue;  //查找下一个可用空间
        }
        else
        {
            //cout << "Calculate PutIn" << endl;
            nCanBePutIn < 0 ? bTrans = true : bTrans = false;
            PutIn(Part[nPartNo], bTrans);
        }
        //cout << "After Tour" << endl;
    } while (!m_lstAvailable.empty() && bPartExist);
    return m_dUsedArea;
}

/*double CLayout::Calculate(int* tour, CPart* Part)
{
    int nPartNo;//零件编号
    while (!m_lstAvailable.empty())
    {
        for (int i = 0; i < nPartsAmount; i++)
        {
            nPartNo = *(tour + i);
            this->Merge();
            //cout << "Calculate After Merge" << endl;
            if (m_lstAvailable.empty()) return m_dUsedArea;
            list<CAreaList>::iterator itAvail = m_lstAvailable.begin();
            int nCanBePutIn = CanBePutIn(Part[nPartNo]);
            int nPutInAmount = 0;
            if (nCanBePutIn != 0)
            {
                nPutInAmount = PutIn(Part[nPartNo], nCanBePutIn);
                //cout << "PutIn Part " << nPartNo << " PartAmount " << Part[nPartNo].getSurplusAmount() << endl;
            }
            if (nPutInAmount == 0)
            {
                bool bUseless = true;
                for (int j = i + 1; j < nPartsAmount; j++)
                {
                    nPartNo = *(tour + j);
                    nCanBePutIn = CanBePutIn(Part[nPartNo]);
                    if (nCanBePutIn != 0)
                    {
                        bUseless = false;
                        break;
                    }
                }
                if (bUseless)
                {
                    CAreaList tmpArea;
                    tmpArea.setX(itAvail->getX());
                    tmpArea.setY(itAvail->getY());
                    tmpArea.setWidth(itAvail->getWidth());
                    tmpArea.setHeight(itAvail->getHeight());
                    m_lstUseless.push_back(tmpArea);
                    m_lstAvailable.pop_front();
                }
            }
        }
    }

    return m_dUsedArea;
}*/


/*void CLayout::showLayoutList()
{
    auto itLayoutList = m_lstLayout.begin();
    int grapWidth = 400, grapHeight = 400;
    initgraph(grapWidth, grapHeight);
    int panelWidth = 200, panelHeight = 200;  //一个平板车尺寸
    CRectangle panel(0, 0, panelWidth, panelHeight, grapWidth, grapHeight); //创建平板车对象
    int tranX = 10, tranY = 10; //x轴和y轴的平移量
    panel.draw(tranX, tranY); //画平板车
    TCHAR s[3];
    int i = 0;
    for (; itLayoutList != m_lstLayout.end(); itLayoutList++)
    {
        CRectangle part(itLayoutList->getX(), itLayoutList->getY(), itLayoutList->getW(), itLayoutList->getH(), grapWidth, grapHeight);
        part.draw(tranX, tranY);
        //cout << "X: " << itLayoutList->getX() << " Y: " << itLayoutList->getY() << " H: " << itLayoutList->getH() << " W: " << itLayoutList->getW() << " ";
        //cout << "Width: " << itLayoutList->getPart().getWidth() * itLayoutList->getHorizonAmount() << " Height: " << itLayoutList->getPart().getHeight() * itLayoutList->getVerticalAmount() << " HorizonAmount: " << itLayoutList->getHorizonAmount() << " VerticalAmount: " << itLayoutList->getVerticalAmount() << endl;
        //swprintf_s(s, _T("%d"), itLayoutList->getPart().getID());
        int Id = itLayoutList->getPart().getID();
        swprintf_s(s, _T("%d"), Id);
        outtextxy(tranX + part.leftX + part.length / 3, grapHeight - part.leftY - part.width/ 2 - tranY, s); //标注数字
        //i++;
    }
    cout << "放入的布局数量 " << i << endl;
    _getch();
    // 关闭图形窗口
    closegraph();
}*/

void CLayout::testMerge()
{
    CAreaList  tmpArea;
    tmpArea.setX(0.0);
    tmpArea.setY(0.0);
    tmpArea.setWidth(20.0);
    tmpArea.setHeight(10.0);
    m_lstAvailable.push_back(tmpArea);
    m_lstAvailable.pop_front();
    auto itAvail = m_lstAvailable.begin();
    cout << "TestMerge BeforeMerge AvailBegin X " << itAvail->getX() << " Y " << itAvail->getY() << " Height " << itAvail->getHeight() << " Width " << itAvail->getWidth() << endl;
    tmpArea.setX(20.0);
    tmpArea.setY(0.0);
    tmpArea.setHeight(5.0);
    tmpArea.setWidth(10.0);
    m_lstUseless.push_back(tmpArea);
    this->Merge();
    if(! m_lstAvailable.empty()) auto itUseless = m_lstUseless.begin();

    cout << "TestMerge AvailBegin X " << itAvail->getX() << " Y " << itAvail->getY() << " Height " << itAvail->getHeight() << " Width " << itAvail->getWidth() << endl;
    //cout << "TestMerge Useless X " << itUseless->getX() << " Y " << itUseless->getY() << " Height " << itUseless->getHeight() << " Width " << itUseless->getWidth() << endl;
}

void CLayout::showLayoutPartNo()
{
    auto p = m_lstLayout.begin();
    cout << "Part number (sequence):" << endl;
    for (; p != m_lstLayout.end(); p++)
    {
        cout << p->getPart().getID() << endl;
    }
}

void CLayout::FindUseless(CPart* data)
{
    if (m_lstAvailable.empty()) return;
    list<CAreaList>::iterator itAvail = m_lstAvailable.begin();
    int Useless = 1;
    for (int i = 0; i < partNum; i++)
    {
        int nCanbePutIn = this->CanBePutIn(data[i]);
        if (nCanbePutIn != 0)
        {
            //cout << "Canputin" << endl;
            Useless = 0;
            return;
        }
    }
    if (Useless)
    {
        CAreaList tmpArea;
        tmpArea.setX(itAvail->getX());
        tmpArea.setY(itAvail->getY());
        tmpArea.setWidth(itAvail->getWidth());
        tmpArea.setHeight(itAvail->getHeight());
        m_lstUseless.push_back(tmpArea);
        //cout << "Useless" << endl;
        //cout << "FindUseless UselessSize " << m_lstUseless.size() << endl;
        m_lstAvailable.pop_front();
        //m_lstAvailable.erase(itAvail);
    }
}
