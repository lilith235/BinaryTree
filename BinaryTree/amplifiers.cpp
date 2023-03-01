#include "amplifiers.h"
#include "ui_amplifiers.h"

amplifiers::amplifiers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::amplifiers)
{
    ui->setupUi(this);
    this->setWindowTitle("信号放大器");
//    去掉标题栏问号按钮
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    //指定窗口的尺寸和显示文字的大小
    this->resize(600,400);
    this->setFont(QFont("宋体",18));

    //        设置确认按钮
            btn1 = new usualPushButton(this);
            btn1->setText("确认");
            //按钮的位置
            btn1->move(90,290);

    //        关闭窗口
            connect(btn1,&QPushButton::clicked,this,&QWidget::close);

    //        设置退出按钮
            btn2 = new usualPushButton(this);
            btn2->setText("退出");
            //按钮的位置
            btn2->move(390,290);
            connect(btn2,&usualPushButton::clicked,[=](){
            MainScene* m=new MainScene;
            m->show();
            this->hide();
            parent->hide();
                   });

            this->setStyleSheet("#supernum{ color: #00B050}");
}

//    背景图
    void amplifiers::paintEvent(QPaintEvent *event)
    {
        QPainter resPainter(this);
           resPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/res/input.jpg"));
    }

    void amplifiers::showNode(QString str)
    {
        //    设置序列显示
        //    qDebug()<<"这个是"<<str;
            ui->supernum->setText (str);
    }

amplifiers::~amplifiers()
{
    delete ui;
}
