/*
 *@file:   basetabledelegate.cpp
 *@author: 缪庆瑞
 *@date:   2022.9.3
 */
#include "basetabledelegate.h"
#include <QDebug>

BasetableDelegate::BasetableDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{

}

BasetableDelegate::~BasetableDelegate()
{

}
#ifdef USE_CUSTOM_EDITOR
/*
 *@brief:   创建编辑器,重写该方法取代view的默认编辑器
 *@author:  缪庆瑞
 *@date:    2022.9.3
 *@param:   parent:编辑器的父部件
 *@param:   option:包含使用QStyle画item的所有信息，在该方法中一般用不到
 *@param:   index:模型/视图数据索引
 */
QWidget *BasetableDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug()<<"create editor "<<index.row()<<index.column();
    //可以只针对某个表项(或者某行某列)自定义代理编辑器
    if(isNeedCustomEdit(index))
    {
        QSpinBox *editor = new QSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    //其他情况使用默认的代理编辑器
    else
    {
         return QStyledItemDelegate::createEditor(parent, option, index);
    }
}
/*
 *@brief:   从model中取数据填到代理编辑器中
 *@author:  缪庆瑞
 *@date:    2022.9.3
 *@param:   editor:代理编辑器
 *@param:   index:模型/视图数据索引
 */
void BasetableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug()<<"set editor "<<index.row()<<index.column();
    /*因为该函数与createEditor等是一组不可分割的函数，所以需要使用相同的判断条件同步
     *使用自定义的代理编辑器或者默认的代理编辑器。
     */
    if(isNeedCustomEdit(index))
    {
        //将edit转换成上面创建的类型
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        //获取model中某个index索引下的对应角色的值
        int value = index.model()->data(index, Qt::EditRole).toInt();
        //设置编辑器显示的值
        spinBox->setValue(value);
    }
    //设置数据到默认的代理编辑器
    else
    {
        QStyledItemDelegate::setEditorData(editor,index);
    }

}
/*
 *@brief:   将编辑器设置的数据写入到model中
 *@author:  缪庆瑞
 *@date:    2022.9.3
 *@param:   editor:代理编辑器
 *@param:   model:item model
 *@param:   index:模型/视图数据索引
 */
void BasetableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    qDebug()<<"set model "<<index.row()<<index.column();
    /*因为该函数与createEditor等是一组不可分割的函数，所以需要使用相同的判断条件同步
     *使用自定义的代理编辑器或者默认的代理编辑器。
     */
    if(isNeedCustomEdit(index))
    {
        //将edit转换成上面创建的类型
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        //获取编辑器的值
        int value = spinBox->value();
        //将数据写入item model
        model->setData(index, value, Qt::EditRole);
        /*数据写入item model后,编辑结束,稍后清理编辑器内存.
         *也可以发送closeEditor()信号让view在不需要时自动清理
         */
        spinBox->deleteLater();
    }
    //从默认的代理编辑器取数据写入model
    else
    {
        QStyledItemDelegate::setModelData(editor,model,index);
    }
}
/*
 *@brief:   设置编辑器的显示位置以及样式
 *@author:  缪庆瑞
 *@date:    2022.9.3
 *@param:   editor:代理编辑器
 *@param:   option:包含使用QStyle画item的所有信息
 *@param:   index:模型/视图数据索引
 */
void BasetableDelegate::updateEditorGeometry(QWidget *editor,
                                             const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //qDebug()<<"updateEditorGeometry "<<index.row()<<index.column();
    /*因为该函数与createEditor等是一组不可分割的函数，所以需要使用相同的判断条件同步
     *使用自定义的代理编辑器或者默认的代理编辑器。
     */
    if(isNeedCustomEdit(index))
    {
        //设置编辑器的大小和位置
        editor->setGeometry(option.rect);
        editor->setStyleSheet("border-width:2px 0px 2px 0px;"
                              "border-style:solid;"
                              "border-color:blue;");
    }
    //更新默认代理编辑器位置
    else
    {
        QStyledItemDelegate::updateEditorGeometry(editor,option,index);
    }
}
/*
 *@brief:   判断表项是否需要自定义代理编辑器
 * 由于重写的那几个编辑器相关的函数都是const 成员函数，不能修改成员数据，也不能调用
 * 非const成员函数，所以该函数必须定义成const类型
 *@author:  缪庆瑞
 *@date:    2022.9.3
 *@param:   index:模型/视图数据索引
 *@return:  true=需要　　false=不需要
 */
bool BasetableDelegate::isNeedCustomEdit(const QModelIndex &index) const
{
    if(index.row()==0 && index.column()==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
#endif
#ifdef USE_CUSTOM_PAINT
/*
 *@brief:   绘制渲染view item(表项)外观,该方法调用的频次比较高,任何item发送变化等会调用该函数
 * 注意如果表项上设置了cellWidget,那么绘制时会在部件的后面绘制
 *@author:  缪庆瑞
 *@date:    2022.9.3
 *@param:   painter:绘图设备
 *@param:   option:包含使用QStyle画item的所有信息
 *@param:   index:模型/视图数据索引
 */
void BasetableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    //qDebug()<<"paint "<<index.row()<<index.column();
    if(isNeedCustomPainter(index))
    {
        /*使用QStyle的函数绘制格式化字符串*/
        /*int num = index.model()->data(index, Qt::DisplayRole).toInt();
        //将item数据转换成带0x的十六进制文本
        QString hexText = QString("0x%1").arg(num,0,16);
        //获取项风格设置  const类型不能直接修改,拷贝一个副本修改
        QStyleOptionViewItem myOption = option;
        myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;
        //绘制文本　如果继承自QItemDelegate类，则可以直接用drawDisplay()
        qApp->style()->drawItemText( painter, myOption.rect , myOption.displayAlignment,
                                     QApplication::palette(), true,hexText );*/

        /*使用QPainter绘制方框*/
        /*painter->setPen(QPen(QBrush(Qt::blue), 4));
        painter->drawRect(option.rect);*/

        /*为选中行的两边画线*/
        if(option.state & QStyle::State_Selected)
        {
            painter->setPen(QPen(QBrush(Qt::blue), 2));
            QPoint p1,p2;
            if(index.column()==0)
            {
                p1= option.rect.topLeft();
                p2 = option.rect.bottomLeft();
                painter->drawLine(p1,p2);
            }
            else if(index.column()==1)
            {
                p1= option.rect.topRight();
                p2 = option.rect.bottomRight();
                painter->drawLine(p1,p2);
            }
        }
    }
    //使用默认的代理绘制item
    else
    {
        QStyledItemDelegate::paint(painter,option,index);
    }
}
/*
 *@brief:   判断表项是否需要自定义代理绘制
 * 由于重写的paint()是const 成员函数,不能修改成员数据,也不能调用非const成员函数,
 * 所以该函数必须定义成const类型
 *@author:  缪庆瑞
 *@date:    2022.9.3
 *@param:   index:模型/视图数据索引
 *@return:  true=需要　　false=不需要
 */
bool BasetableDelegate::isNeedCustomPainter(const QModelIndex &index) const
{
    if(index.column()==0 || index.column()==1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
#endif


