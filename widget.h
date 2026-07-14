/****************************************************************************
*
* Copyright (C) 2022-2026 MiaoQingrui. All rights reserved.
* Author: 缪庆瑞 <justdoit_mqr@163.com>
*
****************************************************************************/
/*
 *@author:  缪庆瑞
 *@date:    2022.09.02
 *@brief:   作为BaseTableWidget使用的demo例程
 */
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QToolButton>
#include "table/customheaderview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void batchCheckBtnSlot(bool checked);
    void songsTableHeaderClickedSlot(int logicalIndex);
    void songsTableCellClickedSlot(int row,int column);

private:
    void initSongsTableWidget();
    void refreshSongsTableText();
    void refreshSongsTableContent(QStringList &rowContentList);
    void sortSongsTableContent();

    Ui::Widget *ui;
    CustomHeaderView *songsTableHeaderView;//表头
    int currentSortColumn;//当前排序列
    Qt::SortOrder currentSortOrder;//当前升降顺序
};
#endif // WIDGET_H
