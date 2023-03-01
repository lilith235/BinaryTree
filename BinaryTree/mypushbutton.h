#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#pragma execution_character_set("utf-8")
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>

class MyPushButton : public QPushButton
{
    Q_OBJECT
  public:
      //explicit MyPushButton(QWidget *parent = nullptr);
//    构造函数 参数1 正常显示的图片路径 参数2 按下后显示的图片路径
      MyPushButton(QString normalImg,QString pressImg="");
      QString normalImgPath;//保存用户传入的默认显示路径
      QString pressImgPath;

      //
      void icomShow(QString path);

      //弹跳特效
      void zoom1();//向下跳
      void zoom2();//向上跳
      void zoom(int upy=0,int dpy=0);//跳转函数


      //重写按钮按下和释放事件
      void mousePressEvent(QMouseEvent *e);
      void mouseReleaseEvent(QMouseEvent *e);
  signals:

};

#endif // MYPUSHBUTTON_H
