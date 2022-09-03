/*
 *@author:  缪庆瑞
 *@date:    2020.08.13
 *@brief:   提供基类表格使用的一些样式宏定义,可参考实现各式各样的表格外观
 */
#ifndef BASETABLESTYLE_H
#define BASETABLESTYLE_H

/* 表格-水平表头样式
 * QHeaderView:用来控制整个表头部件
 * QHeaderView::up-arrow 控制升序图标
 * QHeaderView::down-arrow 控制降序图标
 * QHeaderView::section  控制表头的每一个表项  border-style可控制表头项的网格线
 * QHeaderView::section:first 控制表头的第一个表项
 * QHeaderView::section:last 控制表头的最后一个表项
*/
//1.显示右侧滚动条区域的水平表头样式
/*#define BASETABLE_H_HEADER_STYLE "QHeaderView{\
border-top-left-radius:8px;\
background-color:#2d76b6;min-height:46px;max-height:46px;}\
QHeaderView::section{\
border-style:none;color:white;background-color:#2d76b6;\
border-top-left-radius:8px;border-top-right-radius:8px;}\
QHeaderView::up-arrow{\
width:15px;right:20px;image: url(:/resource/icons/pairs/order_asc.png);}\
QHeaderView::down-arrow{\
width:15px;right:20px;image: url(:/resource/icons/pairs/order_desc.png);}"*/

//2.不显示右侧滚动条区域的水平表头样式
#define BASETABLE_H_HEADER_STYLE "QHeaderView{\
border-top-left-radius:8px;border-top-right-radius:8px;\
background-color:#2d76b6;min-height:46px;max-height:46px;}\
QHeaderView::section{\
border-style:none;color:white;background-color:#2d76b6;\
border-top-left-radius:8px;border-top-right-radius:8px;}\
QHeaderView::up-arrow{\
width:15px;right:20px;image: url(:/resource/icons/pairs/order_asc.png);}\
QHeaderView::down-arrow{\
width:15px;right:20px;image: url(:/resource/icons/pairs/order_desc.png);}"


/* 表格-垂直滚动条样式
 * QScrollBar::vertical：滑块垂直移动的槽
 *          width:控制槽的宽度
 *          margin:可用来为上下两个按钮设置空间
 * QScrollBar::handle:vertical：垂直滑块
 *          宽度可以由vertical的width和padding控制
 *          min-height表示最小高度
 * QScrollBar::sub-line,add-line:vertical：上下两个子控件按钮
 *          height:控制按钮高度，一般使用subcontrol-origin指定的空间
 *          subcontrol-origin:margin表明子控件放在上面指定的margin空间里
 * QScrollBar::up-arrow,down-arrow:vertical：子控件按钮中的箭头,默认只是一个矩形部件
 *          height,width:可控制箭头部件的宽高
 *          border-image:用来设置箭头图片
 * QScrollBar::add-page:vertical,::sub-page:vertical：滑块槽内的上下翻页按钮
 */
//1.显示在右侧滚动条区域的垂直滚动条样式
/*#define BASETABLE_V_SCROLLBAR_STYLE "QScrollBar:vertical{\
width: 36px;margin:46px 0px -1px 0px;background:transparent;\
border-bottom:1px solid #dee1e1;border-bottom-right-radius:6px;}\
QScrollBar::handle:vertical{\
border-radius:2px;margin:2px 1px 2px 29px;\
background:#2d76b6;min-height:60px;}\
QScrollBar::sub-line:vertical {\
border-top-right-radius:8px;background-color:#2d76b6;\
height:46px;subcontrol-origin:margin;}\
QScrollBar::add-line:vertical {\
height:0px;subcontrol-origin:margin;}\
QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{\
background:none;}"*/
//2.不显示在右侧滚动条区域的垂直滚动条样式(内部使用了一个%参数，用来控制滚动条左侧margin)
#define BASETABLE_V_SCROLLBAR_STYLE "QScrollBar:vertical{\
margin:46px 0px 2px 0px;background:transparent;}\
QScrollBar::handle:vertical{\
border-radius:2px;margin:2px 1px 2px %1px;\
background:#2d76b6;min-height:60px;}\
QScrollBar::sub-line:vertical {\
height:46px;subcontrol-origin:margin;background:none;}\
QScrollBar::add-line:vertical {\
height:2px;subcontrol-origin:margin;background:none;}\
QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{\
background:none;}"

/* 表格部件样式
 * QTableWidget:控制整个表格内容部件
 *        alternate-background-color:指定交替行颜色，前提是要调用setAlternatingRowColors(true)
 *        selection-background-color:选中背景色,经过测试发现该属性只在嵌入式平台有效
 *        margin-bottom:-1px，配合垂直滚动条槽底部的margin，避免滚动条底部超出表格边界
 *        outline:none，去除单元格虚线框
 * QTableWidget::item:selected:用来控制选择item的样式，比如背景色。
 * QTableWidget::item:!alternate:指定非交替行的颜色,不指定默认使用表格的背景色作为非交替行颜色
 * QTableWidget::item:alternate:指定交替行颜色
 */
#define BASETABLE_STYLE "QTableWidget{\
border-radius:8px;border:1px solid #cfd4d5;font-size:12pt;\
color:#333333;background-color:white;outline:none;}\
QTableWidget::item{border-bottom:1px solid #c7c7c7;}\
QTableWidget::item:!alternate{background-color:white;}\
QTableWidget::item:alternate{background-color:#f4f7f7;}\
QTableWidget::item:selected{background-color:#b9d5ed;color:black;}"



#endif // BASETABLESTYLE_H
