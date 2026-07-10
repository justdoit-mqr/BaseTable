/****************************************************************************
*
* Copyright (C) 2019-2026 MiaoQingrui. All rights reserved.
* Author: 缪庆瑞 <justdoit_mqr@163.com>
*
****************************************************************************/
/*
 *@author: 缪庆瑞
 *@date:   2019.8.26
 *@brief:  构建自定义Table组件
 * 1.该类继承自QTableWidget，适用于数据量不太大的表格部件显示，使用起来比较方便。而如果表格所承载的数据量比较巨大
 * 则可以使用QTableView，采用MVC框架实现。
 * 2.该类封装了一些常用接口，方便设置/获取表格数据。并提供了一个辅助头文件basetablestyle.h，内部定义了一些样式宏，
 * 可以参考实现各式各样的表格外观。
 * 3.该类提供了垂直滚动条悬浮的功能接口，主要针对早期Qt4版本的触摸程序设计，加宽滚动条方便滑动，而看起来又没那么糟。
 * 而从Qt5开始可以使用QScroller::grabGesture实现整个表格的滑动，一般不再需要刻意加宽滚动条了，所以该功能存在的意义
 * 可能就是让滚动条“浮”在表格上面使其看起来更好看了。
 * 4.如有对表头设计控件的需求，可与提供的CustomHeaderView类配合使用。如需对表格自定义渲染或者自定义编辑器可参考提供
 * 的basetabledelegate委托类实现自定义委托。
 */
#ifndef BASETABLEWIDGET_H
#define BASETABLEWIDGET_H

#include "basetablestyle.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollBar>

class BaseTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit BaseTableWidget(QWidget *parent = 0);
    explicit BaseTableWidget(int row,int column,QWidget *parent = 0);

    /*设置/获取单元格数据(文本、图标、部件以及用户自定义数据等)*/
    void setItemText(int row, int column, QString text, int alignment=Qt::AlignCenter);
    QString getItemText(int row,int column);
    void setItemIcon(int row, int column, QIcon &icon);
    void setItemWidget(int row,int column,QWidget *widget,bool isCenteredLayout=false);
    QWidget *getItemWidget(int row,int column,bool isCenteredLayout=false);
    void setItemData(int row,int column,QVariant variant,int role=Qt::UserRole);
    QVariant getItemData(int row,int column,int role=Qt::UserRole);

    /*其他常用功能接口*/
    void setColumnAutoNumber(int column,int firstNumber=1);//设置某列自动编号
    void setColWidthRowHeight(int columnWidth,int rowHeight);//设置列宽行高
    //设置表格垂直滚动条悬浮显示
    void setVerScrollBarSuspension(int verScrollBarActualWidth=56,
                                   int verScrollBarVisibleWidth=9,bool verScrollBarAsNeeded=false);

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    void initTableProperty();//初始化设置一些表格的默认属性

    bool verScrollBarSuspensionFlag;//垂直滚动条悬浮标记

private slots:
    void verticalScrollBarRangeChangedSlot(int min,int max);//表格垂直滚动条范围改变信号响应槽
};

#endif // BASETABLEWIDGET_H
