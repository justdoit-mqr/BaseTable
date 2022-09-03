/*
 *@author:  缪庆瑞
 *@date:    2022.9.3
 *@brief:   歌曲表格的委托(代理)类
 */
#include "songstabledelegate.h"
#include <QDebug>

SongsTableDelegate::SongsTableDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
    uncheckedPixmap.load(":/resource/icons/pairs/unchecked.png");
    uncheckedPixmap = uncheckedPixmap.scaled(QSize(26,26),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    checkedPixmap.load(":/resource/icons/pairs/checked.png");
    checkedPixmap = checkedPixmap.scaled(QSize(26,26),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    lovingPixmap.load(":/resource/icons/pairs/loving.png");
    lovingPixmap = lovingPixmap.scaled(QSize(26,26),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    lovedPixmap.load(":/resource/icons/pairs/loved.png");
    lovedPixmap = lovedPixmap.scaled(QSize(26,26),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
}
/*
 *@brief:   绘制渲染view item(表项)外观,可以调用QStyle中的函数绘制，也可以使用QPainter的函数绘制
 * 注意:该方法调用的频次比较高,任何可显示item发生变化都会调用该函数,所以内部处理一定要简练
 *@author:  缪庆瑞
 *@date:    2022.9.3
 *@param:   painter:绘图设备
 *@param:   option:包含使用QStyle画item的所有信息
 *@param:   index:模型/视图数据索引
 */
void SongsTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    //先使用默认的代理绘制表项
    QStyledItemDelegate::paint(painter,option,index);
    if(index.column() == NO_COL)//编号列
    {
        //绘制编号
        qApp->style()->drawItemText(painter,option.rect,Qt::AlignCenter,
                                    QApplication::palette(),true,QString("%1").arg(index.row()+1));
    }
    else if(index.column() == BATCH_CHECK_COL)//批量选择列
    {
        //批量选择列图标渲染:根据UserRole的值QVariant(bool)，做不同的图标渲染处理
        if(index.data(Qt::UserRole).toBool())
        {
            qApp->style()->drawItemPixmap(painter,option.rect,Qt::AlignCenter,checkedPixmap);
        }
        else
        {
            qApp->style()->drawItemPixmap(painter,option.rect,Qt::AlignCenter,uncheckedPixmap);
        }
    }
    else if(index.column() == LOVE_COL)//喜欢列
    {
        //批量选择列图标渲染:根据UserRole的值QVariant(bool)，做不同的图标渲染处理
        if(index.data(Qt::UserRole).toBool())
        {
            qApp->style()->drawItemPixmap(painter,option.rect,Qt::AlignCenter,lovedPixmap);
        }
        else
        {
            qApp->style()->drawItemPixmap(painter,option.rect,Qt::AlignCenter,lovingPixmap);
        }
    }
}
