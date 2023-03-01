#ifndef USUALPUSHBUTTON_H
#define USUALPUSHBUTTON_H
//#pragma execution_character_set("utf-8")
#include<QPushButton>
#include<QTextEdit>
#include<QGraphicsDropShadowEffect>

class usualPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit usualPushButton(QWidget *parent=0);//设置其父窗口
    //重写按钮按下和释放事件
    void mousePressEvent(QMouseEvent* e);//重写按下事件，此方法源自于QPushButton的父类QAbstracetButton。
    void mouseReleaseEvent(QMouseEvent* e);//重写按下离开事件,此方法源自于QPushButton的父类QAbstracetButton

signals:


};

#endif // USUALPUSHBUTTON_H
