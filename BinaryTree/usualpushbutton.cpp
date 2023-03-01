#include "usualpushbutton.h"
#include<QIcon>
#include<QPropertyAnimation>//动画特效头文件
#include<QRect>

usualPushButton::usualPushButton(QWidget *parent) : QPushButton(parent)
{
    this->setStyleSheet("QPushButton:hover{font:22px; color:#295378; background-color: #E1F7FF; border-width:3px; border-color:#27506E; border-radius: 20px;}"
                        "QPushButton{font:22px; color:#E1F7FF; background-color: #295378; border-width:3px; border-color:#E1F7FF; border-radius: 20px;}");

    //调整按钮的尺寸
    this->resize(120,50);
    //        设置按钮边框阴影
    QGraphicsDropShadowEffect *shadow_effect3 = new QGraphicsDropShadowEffect(this);
    shadow_effect3->setOffset(5, 5);
    shadow_effect3->setColor(QColor(43, 43, 43));
    shadow_effect3->setBlurRadius(8);
    this->setGraphicsEffect(shadow_effect3);
}

void usualPushButton::mousePressEvent(QMouseEvent *e)
{
    return QPushButton::mousePressEvent(e);

}

void usualPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    return QPushButton::mouseReleaseEvent(e);
}
