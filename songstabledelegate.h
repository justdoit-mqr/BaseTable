/*
 *@author:  缪庆瑞
 *@date:    2022.9.3
 *@brief:   歌曲表格的委托(代理)类
 *
 * 1.delegate(委托)建立在model/view上,负责管理用户交互,而view仅仅作为model数据的展示和简单用户
 * 输入处理.可以通过该类实现对view(表格)显示的自定义，表格可以只负责数据，而让委托类完成显示处理。
 * 该委托类继承自QStyledItemDelegate,也可以继承QItemDelegate ,Qt Assistant建议用户最好继承自
 * QStyledItemDelegate.这两个类在绘制代理和为item提供编辑器上面是独立的,没什么联系,互不影响;
 * 不同的是QStyledItemDelegate默认使用当前widget或者qApp的style来绘制item(的代理),即如果程序
 * 设置了部件或者应用的风格(用QSS或其他定义方式),QStyledItemDelegate会使用这个风格设置.
 *
 * 2.该类主要提供对编号列的文本渲染以及“批量选择”、"喜欢"列的图标进行渲染。
 * 使用委托drawItemPixmap的方式渲染单元格图片相较于QTableWidgetItem的setIcon()，它
 * 可以解决居中问题。相比设置cellWidget它也有很大的性能优势(设置cellWidget需要事先new出相应的
 * 部件对象，当所需部件较多时即占空间又费时间)。
 *
 */
#ifndef SONGSTABLEDELEGATE_H
#define SONGSTABLEDELEGATE_H

#include <QObject>
#include <QApplication>
#include <QPainter>
#include <QPixmap>
#include <QStyledItemDelegate>

class SongsTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    //测试表格委托列索引
    enum DelegateColIndex
    {
        NO_COL=0,//编号列(文本列)
        BATCH_CHECK_COL=1,//批量选择(图标列)
        LOVE_COL=5//喜欢(图标列)
    };

    SongsTableDelegate(QObject *parent=0);

    /*view 表项外观渲染*/
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                   const QModelIndex &index) const ;//绘制渲染view item(表项)外观

private:
    QPixmap uncheckedPixmap;//批量未选中图标
    QPixmap checkedPixmap;//批量选中图标

    QPixmap lovingPixmap;//将会喜欢
    QPixmap lovedPixmap;//喜欢

signals:

public slots:

};

#endif // SONGSTABLEDELEGATE_H
