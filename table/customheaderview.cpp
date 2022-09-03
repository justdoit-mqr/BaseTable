/*
 *@author:  缪庆瑞
 *@date:    2020.09.10
 *@brief:   自定义表头组件
 */
#include "customheaderview.h"
#include <QDebug>

CustomHeaderView::CustomHeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation,parent)
{

}
/*
 *@brief:   设置表头控件
 *@author:  缪庆瑞
 *@date:    2020.09.10
 *@param:   widget:控件指针
 *@param:   logicalIndex:控件所在表项的逻辑索引
 */
void CustomHeaderView::setHeaderViewWidget(QWidget *widget, int logicalIndex)
{
    headerViewWidgetMap.insert(logicalIndex,widget);
    if(widget != NULL)
    {
        widget->setParent(this);
    }
}
/*
 *@brief:   设置表项隐藏/显示
 * 注:该函数在基类并没有声明为虚函数，所以这里重写之后需要使用派生类对象直接调用才有效
 *@author:  缪庆瑞
 *@date:    2020.09.10
 *@param:   logicalIndex:表项的逻辑索引
 *@param:   hide:true=隐藏  false=显示
 */
void CustomHeaderView::setSectionHidden(int logicalIndex, bool hide)
{
    //先调用父类函数实现默认功能
    QHeaderView::setSectionHidden(logicalIndex,hide);
    //如果该索引下设置了控件，则同步隐藏/显示控件
    if(headerViewWidgetMap.contains(logicalIndex) &&
            headerViewWidgetMap.value(logicalIndex) != NULL)
    {
        headerViewWidgetMap.value(logicalIndex)->setHidden(hide);
    }
}
/*
 *@brief:   绘制表项
 * 注1:该函数在QHeaderView类中是const成员函数，派生类重写该虚函数时要保留const，否则基类不会调用
 *@author:  缪庆瑞
 *@date:    2020.09.10
 *@param:   painter:绘图设备
 *@param:   rect:对应表项所在的矩形
 *@param:   logicalIndex:表项的逻辑索引
 */
void CustomHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    //先调用父类函数实现默认功能
    QHeaderView::paintSection(painter, rect, logicalIndex);
    //如果该索引下设置了控件，则将控件位置设置到表项所在矩形内
    if(headerViewWidgetMap.contains(logicalIndex) &&
            headerViewWidgetMap.value(logicalIndex) != NULL)
    {
        headerViewWidgetMap.value(logicalIndex)->setGeometry(rect);
        headerViewWidgetMap.value(logicalIndex)->setVisible(true);
    }
}
