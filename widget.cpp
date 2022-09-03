/*
 *@author:  缪庆瑞
 *@date:    2022.09.02
 *@brief:   作为BaseTableWidget使用的demo例程
 */
#include "widget.h"
#include "ui_widget.h"
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    initSongsTableWidget();
    refreshSongsTableText();
    on_pushButton_clicked();
}

Widget::~Widget()
{
    delete ui;
}
//刷新(重置)列表
void Widget::on_pushButton_clicked()
{
    QFile songsFile("./test/songs.txt");
    if(!songsFile.exists())
    {
        return;
    }
    if(songsFile.open(QIODevice::ReadOnly))
    {
        char buf[1024];
        QStringList rowContentList;
        while(songsFile.readLine(buf,1024)>0)
        {
            rowContentList.append(QString::fromUtf8(buf));
        }
        refreshSongsTableContent(rowContentList);
    }
}
//批量选择按钮响应槽
void Widget::batchCheckBtnSlot(bool checked)
{
    int rowCount = ui->songsTableWidget->rowCount();
    for(int i=0;i<rowCount;i++)
    {
        ui->songsTableWidget->setItemData(i,1,checked);
    }
}
//表头点击响应槽  logicalIndex：表头逻辑索引，即列号
void Widget::songsTableHeaderClickedSlot(int logicalIndex)
{
    /* 因为当开启了表头的排序指示器(setSortIndicatorShown)显示后，在表头项被点击时会自动切换
     * 排序指示器到当前点击的项，然而我们的需求是表格中只有指定的列才具有排序功能，所以在该槽
     * 内如果检测到点击的是非排序列，需要将排序指示器恢复到原来的状态*/
    if((logicalIndex<2) || (logicalIndex>4))
    {
        songsTableHeaderView->setSortIndicator(currentSortColumn,currentSortOrder);
        return;
    }
    //点击的是排序列则记录当前排序指示器状态
    currentSortColumn = songsTableHeaderView->sortIndicatorSection() ;
    currentSortOrder = songsTableHeaderView->sortIndicatorOrder();
    //排序
    sortSongsTableContent();
}
//表格单元格点击响应槽
void Widget::songsTableCellClickedSlot(int row, int column)
{
    //批量选择列
    if(column == SongsTableDelegate::BATCH_CHECK_COL ||
            column == SongsTableDelegate::LOVE_COL)
    {
        bool checkState = ui->songsTableWidget->getItemData(row,column).toBool();
        ui->songsTableWidget->setItemData(row,column,!checkState);
    }
}
//初始化歌曲表格
void Widget::initSongsTableWidget()
{
    ui->songsTableWidget->setRowCount(10);
    ui->songsTableWidget->setColumnCount(7);
    /******设置表格属性******/
    ui->songsTableWidget->setAlternatingRowColors(true);//启用交替行颜色
    ui->songsTableWidget->setStyleSheet(BASETABLE_STYLE);//设置表格样式表
    //ui->songsTableWidget->setShowGrid(true);//显示网格线
    //为表格部件安装委托
    songsTableDelegate = new SongsTableDelegate(this);
    ui->songsTableWidget->setItemDelegate(songsTableDelegate);
    //为表格部件设置自定义水平表头
    songsTableHeaderView = new CustomHeaderView(Qt::Horizontal,this);
    ui->songsTableWidget->setHorizontalHeader(songsTableHeaderView);
    //设置表格列宽
    ui->songsTableWidget->setColumnWidth(0,50);//编号
    ui->songsTableWidget->setColumnWidth(1,60);//批量选择/未选择
    ui->songsTableWidget->setColumnWidth(2,320);//歌曲名称
    ui->songsTableWidget->setColumnWidth(3,120);//歌手
    ui->songsTableWidget->setColumnWidth(4,120);//时长
    ui->songsTableWidget->setColumnWidth(5,60);//喜欢
    //设置表格行高
    ui->songsTableWidget->verticalHeader()->setDefaultSectionSize(50);//设置行高
    connect(ui->songsTableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(songsTableCellClickedSlot(int,int)));
    /******设置滚动条属性******/
    ui->songsTableWidget->setVerScrollBarSuspension();//设置垂直滚动条悬浮功能
    /*******设置水平表头属性*******/
    currentSortColumn = 2,
    currentSortOrder = Qt::AscendingOrder;
    songsTableHeaderView->setVisible(true);//显示水平表头
    songsTableHeaderView->setSortIndicatorShown(true);//显示排序指示器
    songsTableHeaderView->setSortIndicator(currentSortColumn,currentSortOrder);//设置初始排序列
    //songsTableHeaderView->setClickable(true);//设置表头可点击,旧接口
    songsTableHeaderView->setSectionsClickable(true);//设置表头可点击
    songsTableHeaderView->setHighlightSections(false);//选中时表头不高亮
    //songsTableHeaderView->setResizeMode(QHeaderView::Fixed);//表头不可调节大小,旧接口
    songsTableHeaderView->setSectionResizeMode(QHeaderView::Fixed);//表头不可调节大小
    songsTableHeaderView->setMinimumSectionSize(20);//设置列的最小大小，避免最后一列的推荐大小过大触发水平滚动条
    songsTableHeaderView->setStretchLastSection(true);//最后一列自适应大小,避免因列宽偏差导致最后一列出问题(留空或超长)
    songsTableHeaderView->setStyleSheet(BASETABLE_H_HEADER_STYLE);//水平表头样式
    //给水平表头的批量选择列项添加一个‘全选/全不选’按钮
    batchCheckBtn = new QToolButton(songsTableHeaderView);
    batchCheckBtn->setFixedSize(60,46);//固定大小与表头section相同
    batchCheckBtn->setCheckable(true);
    QIcon icon;
    QSize iconSize = QSize(26,26);
    icon.addFile(":/resource/icons/pairs/unchecked.png",iconSize,QIcon::Normal,QIcon::Off);
    icon.addFile(":/resource/icons/pairs/checked.png",iconSize,QIcon::Normal,QIcon::On);
    batchCheckBtn->setIcon(icon);
    batchCheckBtn->setIconSize(iconSize);
    batchCheckBtn->setStyleSheet("border-style:none;");
    connect(batchCheckBtn,SIGNAL(clicked(bool)),this,SLOT(batchCheckBtnSlot(bool)));
    songsTableHeaderView->setHeaderViewWidget(batchCheckBtn,SongsTableDelegate::BATCH_CHECK_COL);
    connect(songsTableHeaderView,SIGNAL(sectionClicked(int)),this,SLOT(songsTableHeaderClickedSlot(int)));
}
//刷新静态文本
void Widget::refreshSongsTableText()
{
    //设置表头
    QStringList horizontaHeaderLables;
    horizontaHeaderLables.append(tr("编号"));
    horizontaHeaderLables.append("");//批量选择/未选择
    horizontaHeaderLables.append(tr("歌曲名称"));
    horizontaHeaderLables.append(tr("歌手"));
    horizontaHeaderLables.append(tr("时长"));
    horizontaHeaderLables.append(tr("最爱"));
    horizontaHeaderLables.append("");
    ui->songsTableWidget->setHorizontalHeaderLabels(horizontaHeaderLables);
}
//刷新表格内容显示  rowContentList:行内容列表
void Widget::refreshSongsTableContent(QStringList &rowContentList)
{
    int rowCount = rowContentList.size();
    ui->songsTableWidget->setRowCount(rowCount);

    /*循环刷新表格显示*/
    for(int i=0;i<rowCount;i++)
    {
        QString rowContent = rowContentList.at(i);
        QStringList rowItemList = rowContent.split(";");
        //编号(由委托自动处理)
        //复选状态(由委托处理)
        ui->songsTableWidget->setItemData(i,1,false);//默认不选中
        //歌曲名称
        ui->songsTableWidget->setItemText(i,2,rowItemList.at(1));
        //歌手
        ui->songsTableWidget->setItemText(i,3,rowItemList.at(0));
        //时长
        ui->songsTableWidget->setItemText(i,4,rowItemList.at(2));
        //喜欢(由委托处理)
        ui->songsTableWidget->setItemData(i,5,QVariant(rowItemList.at(3)).toBool());
    }
    /*排序*/
    sortSongsTableContent();
}
//排序内容
void Widget::sortSongsTableContent()
{
    //sortItems内部会设置水平表头的排序指示器
    ui->songsTableWidget->sortItems(currentSortColumn,currentSortOrder);
    if(ui->songsTableWidget->rowCount()>0)
    {
        ui->songsTableWidget->selectRow(0);//排序后默认选中首行
    }
    //编号列重新排序(编号列改由委托直接根据行号绘制，这里排序后就不用再重新排序了)
    //ui->songsTableWidget->setColumnAutoNumber(0);
}


