/*
 *@author: 缪庆瑞
 *@date:   2019.8.26
 *@brief:  构建自定义Table组件
 */
#include "basetablewidget.h"
#include <QHBoxLayout>
#include <QDebug>

BaseTableWidget::BaseTableWidget(QWidget *parent) :
    QTableWidget(parent),verScrollBarSuspensionFlag(false)
{
    initTableProperty();
}

BaseTableWidget::BaseTableWidget(int row,int column,QWidget *parent) :
    QTableWidget(row,column,parent),verScrollBarSuspensionFlag(false)
{
    initTableProperty();
}
/*
 *@brief:   设置item文本
 *@author:  缪庆瑞
 *@date:    2019.8.26
 *@param:   row:指定行
 *@param:   column:指定列
 *@param:   text:设置的文本
 *@param:   alignment:文本居中方式,默认居中
 */
void BaseTableWidget::setItemText(int row, int column, QString text,int alignment)
{
    //移除原有的控件,不然有控件的话无法显示文本,没有控件的话该函数不做什么
    this->removeCellWidget(row,column);
    //先获取指定行列的QTableWidgetItem，没有则新建
    QTableWidgetItem *item = this->item(row,column);
    if(item)
    {
        item->setText(text);
        item->setTextAlignment(alignment);
    }
    else
    {
        item = new QTableWidgetItem(text);
        item->setTextAlignment(alignment);
        this->setItem(row,column,item);
    }
}
/*
 *@brief:   获取item显示的文本
 *@author:  缪庆瑞
 *@date:    2020.06.01
 *@param:   row:指定行
 *@param:   column:指定列
 *@return:  QString:显示的文本,item不存在则返回空串
 */
QString BaseTableWidget::getItemText(int row, int column)
{
    QTableWidgetItem *item = this->item(row,column);
    QString itemText;
    if(item)
    {
        itemText = item->text();
    }
    return itemText;
}
/*
 *@brief:   设置item图标
 *@author:  缪庆瑞
 *@date:    2022.9.2
 *@param:   row:指定行
 *@param:   column:指定列
 *@param:   icon:设置的图标
 */
void BaseTableWidget::setItemIcon(int row, int column, QIcon &icon)
{
    //移除原有的控件,不然有控件的话无法显示文本,没有控件的话该函数不做什么
    this->removeCellWidget(row,column);
    //先获取指定行列的QTableWidgetItem，没有则新建
    QTableWidgetItem *item = this->item(row,column);
    if(item)
    {
        item->setIcon(icon);
    }
    else
    {
        item = new QTableWidgetItem(icon,"");
        this->setItem(row,column,item);
    }
}
/*
 *@brief:   设置item部件
 *@author:  缪庆瑞
 *@date:    2019.8.26
 *@param:   row:指定行
 *@param:   column:指定列
 *@param:   widget:设置的小部件
 *@param:   isCenteredLayout:是否对小部件设置居中布局，默认为false
 */
void BaseTableWidget::setItemWidget(int row, int column, QWidget *widget, bool isCenteredLayout)
{
    /* 因为setCellWidget()默认将控件完全填充到表格中,对于固定大小的部件，无法居中对齐，所以
     * 这里在设置的小部件之上加了一层layoutWidget,实现居中对齐
     * 注：setCellWidget()内部会对旧的widget自动调用deletelater，如果重设了某个单元格的部件
     * 之前的部件会被清理，注意野指针现象。*/
    if(isCenteredLayout)
    {
        //先为控件设置objectname，方便findchild查找控件对象
        widget->setObjectName("cellWidget");
        QWidget *layoutWidget = new QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout(layoutWidget);
        layout->setMargin(0);
        layout->addWidget(widget);
        this->setCellWidget(row,column,layoutWidget);
    }
    else
    {
        this->setCellWidget(row,column,widget);
    }
}
/*
 *@brief:   获取item部件
 *@author:  缪庆瑞
 *@date:    2019.9.3
 *@param:   row:指定行
 *@param:   column:指定列
 *@param:   isCenteredLayout:小部件是否设置了居中布局，默认为false
 *@return:   如果单元格存放控件返回指定控件,否则返回NULL
 */
QWidget *BaseTableWidget::getItemWidget(int row, int column, bool isCenteredLayout)
{
    if(this->cellWidget(row,column)!=NULL)
    {
        QWidget *itemWidget;
        if(isCenteredLayout)
        {
            itemWidget = this->cellWidget(row,column)->findChild<QWidget *>("cellWidget");
            if(itemWidget==0)
            {
                return NULL;
            }
        }
        else
        {
            itemWidget = this->cellWidget(row,column);
        }
        /*返回的是QWidget类型指针，而具体存放的一般是其子类对象,所以使用时需要用
         * qobject_cast强制转换为子类对象指针才能操作子类的相关功能
         * 例:qobject_cast <BaseToolButton *>(baseTableWidget->getItemWidget(2,0));*/
        return itemWidget;
    }
    else
    {
        return NULL;
    }
}
/*
 *@brief:   设置item指定角色对应的数据
 *@author:  缪庆瑞
 *@date:    2020.05.29
 *@param:   row:指定行
 *@param:   column:指定列
 *@param:   variant:数据,支持Qt常用的大多数类型
 *@param:   role:指定角色，默认为UserRole,由开发者自行决定用途。
 *Qt自带了很多角色，QTableWidgetItem的很多接口，其实内部就是通过setData()设置固定角色数据实现的
 */
void BaseTableWidget::setItemData(int row, int column, QVariant variant, int role)
{
    //先获取指定行列的QTableWidgetItem，没有则新建
    QTableWidgetItem *item = this->item(row,column);
    if(item)
    {
        item->setData(role,variant);
    }
    else
    {
        item = new QTableWidgetItem();
        item->setData(role,variant);
        this->setItem(row,column,item);
    }
}
/*
 *@brief:   获取item指定角色对应的数据
 *@author:  缪庆瑞
 *@date:    2020.05.29
 *@param:   row:指定行
 *@param:   column:指定列
 *@param:   role:指定角色，默认为UserRole,由开发者自行决定用途
 *@return:   QVariant:如果item不存在,返回无效的QVariant
 */
QVariant BaseTableWidget::getItemData(int row, int column, int role)
{
    QTableWidgetItem *item = this->item(row,column);
    QVariant variant;
    if(item)
    {
        variant = item->data(role);
    }
    return variant;
}
/*
 *@brief:   设置某列的所有行自动编号
 *@author:  缪庆瑞
 *@date:    2022.9.2
 *@param:   column:列号
 *@param:   firstNumber:初始编号，默认为1
 */
void BaseTableWidget::setColumnAutoNumber(int column, int firstNumber)
{
    int rowNum = this->rowCount();
    for(int i=0;i<rowNum;i++)
    {
        this->setItemText(i,column,QString::number(i+firstNumber));
    }
}
/*
 *@brief:   设置列宽和行高,这里是通过表头设置的,所有行列都一致
 * 注:表格的列宽和行高不会自动随着布局调整，所以需要手动设置
 *@author:  缪庆瑞
 *@date:    2019.8.26
 *@param:   columnWidth:列宽
 *@param:   rowHeight:行高
 */
void BaseTableWidget::setColWidthRowHeight(int columnWidth, int rowHeight)
{
    this->verticalHeader()->setDefaultSectionSize(rowHeight);
    this->horizontalHeader()->setDefaultSectionSize(columnWidth);
}
/*
 *@brief:   设置表格的垂直滚动条悬浮在表格内容上面
 * 注1:QAbstractScrollArea(表格继承自该类)的滚动条区域默认是通过布局的方式添加到部件中的，
 * 所以当滚动条区域显示时，它就会占用部件的一部分空间导致表格内容区空间减小。同时在触摸屏上为
 * 了更灵敏的滑动效果(注:Qt5可以使用QScroller::grabGesture手势捕获，实现整个区域的滑动效
 * 果，但Qt4还没有该功能，必须借助滚动条滑动)，垂直滚动条的宽度不可以过小，这就导致右侧滚动条
 * 在整个表格中显得有些突兀。该方法通过重设滚动条的父对象使其脱离原有布局，然后根据表格的size
 * 设置滚动条的大小和位置，使其悬浮在表格内容的右侧
 * 注2:滚动条悬浮会设置Qt::ScrollBarAlwaysOff关闭原始的布局空间占用，如果需要让滚动条按需显
 * 示则可以设置该方法的第三个参数为true，内部处理会根据滚动条的范围变化自动显示/隐藏。
 *@author:  缪庆瑞
 *@date:    2020.08.13
 *@param:   verScrollBarActualWidth:滚动条的实际宽度(固定宽度是为了后面自动调整位置)
 *@param:   verScrollBarVisibleWidth:滚动条可见区域宽度(从视觉上让滚动条看起来比实际窄一些)
 *@param:   verScrollBarAsNeeded:true=按需显示  false=总是显示
 */
void BaseTableWidget::setVerScrollBarSuspension(int verScrollBarActualWidth,
                                                int verScrollBarVisibleWidth, bool verScrollBarAsNeeded)
{
    verScrollBarSuspensionFlag = true;//置悬浮标记为true
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭垂直滚动条的布局空间占用
    this->verticalScrollBar()->setFixedWidth(verScrollBarActualWidth);
    this->verticalScrollBar()->setParent(this);
    this->verticalScrollBar()->setStyleSheet(QString(BASETABLE_V_SCROLLBAR_STYLE)
                                             .arg(verScrollBarActualWidth-verScrollBarVisibleWidth));//设置默认样式表
    if(verScrollBarAsNeeded)//按需显示
    {
        this->verticalScrollBar()->setVisible(false);//初始不显示
        connect(this->verticalScrollBar(),SIGNAL(rangeChanged(int,int)),
                this,SLOT(verticalScrollBarRangeChangedSlot(int,int)));
    }
    else//总是显示
    {
        this->verticalScrollBar()->setVisible(true);
        disconnect(this->verticalScrollBar(),SIGNAL(rangeChanged(int,int)),
                   this,SLOT(verticalScrollBarRangeChangedSlot(int,int)));
    }
}
/*
 *@brief:   部件大小调整事件处理
 * 注：通常在部件尺寸改变以及第一次显示时被自动调用
 *@author:  缪庆瑞
 *@date:    2020.08.13
 *@param:   event:大小事件
 */
void BaseTableWidget::resizeEvent(QResizeEvent *event)
{
    QTableWidget::resizeEvent(event);
    //如果设置了垂直滚动条悬浮，则根据表格当前size设置滚动条的大小和位置
    if(verScrollBarSuspensionFlag)
    {
        this->verticalScrollBar()->setFixedHeight(this->height());
        this->verticalScrollBar()->move(this->width()-this->verticalScrollBar()->width(),0);
    }
}
/*
 *@brief:   初始化设置表格的一些默认属性
 *这里可根据项目表格的统一风格进行自由设定，特例化在类外单独调用QTableWidget的接口即可
 *@author:  缪庆瑞
 *@date:    2019.08.26
 */
void BaseTableWidget::initTableProperty()
{
    this->setFocusPolicy(Qt::NoFocus);//无焦点
    //this->setGridStyle(Qt::NoPen);//设置网格线样式
    this->setShowGrid(false);//不显示网格线
    this->verticalHeader()->setVisible(false);//隐藏垂直表头
    this->horizontalHeader()->setVisible(false);//隐藏水平表头
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格不可编辑
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭水平滚动条
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭垂直滚动条
    this->setSelectionMode(QAbstractItemView::SingleSelection);//设置选中的模式 单选
    this->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中的行为 整行选中
    //this->setAlternatingRowColors(true);//设置行颜色交替　需要设置样式表alternate-background-color选项
}
/*
 *@brief:   表格垂直滚动条范围改变信号响应槽
 * 该槽主要用来根据范围自动显示/隐藏滚动条
 *@author:  缪庆瑞
 *@date:    2020.11.04
 *@param:   min:最小值
 *@param:   max:最大值
 */
void BaseTableWidget::verticalScrollBarRangeChangedSlot(int min, int max)
{
    if(min != max && max>0)
    {
        this->verticalScrollBar()->setVisible(true);
    }
    else
    {
        this->verticalScrollBar()->setVisible(false);
    }
}
