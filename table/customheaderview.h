/*
 *@author:  缪庆瑞
 *@date:    2020.09.10
 *@brief:   自定义表头组件
 *
 * 1.该表头组件继承自QHeaderView，通过重写虚函数(paintSection())，实现表头的自定义显示。
 * 2.目前该组件主要实现了设置表头控件的功能，通过调用setHeaderViewWidget()接口，可以将
 * 控件设置到指定的表项中，显示时自动调整控件位置，还可以调用setSectionHidden()函数设置
 * 控件与表项同步显示/隐藏。
 * 注:最初采用"QHeaderView::setIndexWidget(QHeaderView::model()->index(0,n),widget);"方式
 * 设置表头控件,但该方式并不能自动调整控件的位置，还需要手动移动控件到指定的位置“move(
 * QHeaderView::sectionPosition(n,0)"，同样控件也不能自动跟随表项隐藏，不过这些还都能解
 * 决。最大的问题是当使用QTableWidget部件调用setRowCount(0)时，会自动析构掉表头中设置
 * 的控件，查看了setRowCount的源码，但依旧没有找到控件被析构的原因。虽然setIndexWidget()
 * 将控件的所有权传递给了QHeaderView，但即便设置成空行，表头也不会被析构，不知道控件
 * 怎么就被删除了。
 */
#ifndef CUSTOMHEADERVIEW_H
#define CUSTOMHEADERVIEW_H

#include <QHeaderView>

class CustomHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit CustomHeaderView(Qt::Orientation orientation,QWidget *parent = 0);

    void setHeaderViewWidget(QWidget *widget,int logicalIndex);//设置表头控件

    /*函数重写*/
    void setSectionHidden(int logicalIndex, bool hide);//设置表头某一个section隐藏/显示

protected:
    virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

private:
    /*表头控件参数*/
    QMap<int,QWidget*> headerViewWidgetMap;


signals:

public slots:
};

#endif // CUSTOMHEADERVIEW_H
