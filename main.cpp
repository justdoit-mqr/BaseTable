#include "widget.h"

#include <QApplication>
#include <QScrollerProperties>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置滚动属性(针对当前触摸屏滚动参数进行针对性调优)
    QScrollerProperties properties;
    properties.setScrollMetric(QScrollerProperties::DecelerationFactor, 0.2);//减速系数，越大减速越快
    properties.setScrollMetric(QScrollerProperties::MaximumVelocity,0.5);//松手后的惯性速度最大值
    properties.setScrollMetric(QScrollerProperties::DragVelocitySmoothingFactor,0.4);//拖动速度平滑 越小越稳定也越慢
    properties.setScrollMetric(QScrollerProperties::AxisLockThreshold,0.99);//轴锁定
    properties.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy,
                               QScrollerProperties::OvershootAlwaysOff);//关闭水平越界
    properties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy,
                               QScrollerProperties::OvershootAlwaysOff);//关闭垂直越界
    QScrollerProperties::setDefaultScrollerProperties(properties);

    Widget w;
    w.resize(860,600);
    w.show();
    return a.exec();
}
