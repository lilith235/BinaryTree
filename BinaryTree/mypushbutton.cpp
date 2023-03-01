#include "mypushbutton.h"
#include<QIcon>
#include<QPropertyAnimation>//动画特效头文件
#include<QRect>

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
    icomShow(normalImg);
}

void MyPushButton::icomShow(QString path)
{
    QPixmap pix;
    bool ret=pix.load(path);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(),pix.height());/*设置图片固定大小*/
    this->setStyleSheet("QPushButton{border:0px;}");/*设置不规则图片样式*/
    this->setIcon(pix);/*设置图标*/
    this->setIconSize(QSize(pix.width(),pix.height()));/*设置图标大小*/


}

void MyPushButton::zoom1()
{
   zoom(0,10);
}

void MyPushButton::zoom2()
{
    zoom(10,0);
}

void MyPushButton::zoom(int upy,int dpy)
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");/*创建动态对象*/
    animation->setDuration(200);//设置动画时间间隔
    //QRect(this->x(),this-y(),this->width(),this->height());
    animation->setStartValue(QRect(QPoint(this->x(),this->y()+upy),QPoint(this->width(),this->height())));/*起始位置*/
    animation->setEndValue(QRect(QPoint(this->x(),this->y()+dpy),QPoint(this->width(),this->height())));/*起始位置*/
    animation->setEasingCurve(QEasingCurve::OutBounce);/*设置弹跳效果*/
    animation->start();/*设置开始弹跳*/
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!=""){//传入的按下图片不为空，说明需要有按下状态切换图片
        icomShow(this->pressImgPath);
    }
    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);

}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath!=""){//传入的按下图片不为空，说明需要切换成初始的图片
        icomShow(this->normalImgPath);
    }
    return QPushButton::mouseReleaseEvent(e);
}


