# 智能优化算法在矩形排料问题中的实现 
**大二时算法和数据结构的课设项目**
- Qt实现图形界面
> Qt版本大概要在5.12以上，才能把这个项目跑起来。主要原因是一些控件的信号写法变了，QDoubleSpinBox的信号高版本应该是textChanged,低版本的应该是valueChanged,应该是这个原因，如果你不想更新Qt版本并且熟悉Qt的图形界面，对代码做稍微改一下，就行了。

- 蚁群算法求堆料最优情况
> 大致分为这四个步骤 ，具体可以查看我们的 [答辩ppt](https://github.com/Maserhe/Rectangular_Packing_Problems/blob/master/%E7%AD%94%E8%BE%A9%E6%8A%A5%E5%91%8A/%E7%AE%97%E6%B3%95%E8%AF%BE%E8%AE%BE%E5%9F%BA%E4%BA%8E%E8%9A%81%E7%BE%A4%E7%9A%84%E7%94%9F%E4%BA%A7%E8%B0%83%E5%BA%A6%E7%AE%97%E6%B3%95.pptx)，写的比较详细。

>（1）	路径图的构造

>（2）	信息素更新

>（3）	转移概率

>（4）	适宜值


- 运行效果图


**开始界面**

  ![1](https://i.loli.net/2020/07/13/7Mzpn8we3gubtXT.png)

**导入数据**

  ![2](https://i.loli.net/2020/07/13/wHoG2CkBIXEycS6.png)

**结果绘图**

  ![3](https://i.loli.net/2020/07/13/NZwqQWuYyoFcTA3.png)
