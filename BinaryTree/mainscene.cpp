#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include "mypushbutton.h"
#include "ergodicsequenceinput.h"

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

//    配置主场景

//    设置固定大小
    setFixedSize(1668,808);

//    设置无边框
//    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

//    设置图标
    setWindowIcon(QIcon(":/res/icon.png"));

//    设置标题
    setWindowTitle("二叉树");

//    开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);/*宽度：屏幕宽度一半减去按钮宽度的一半，高度：水边设置*/
    connect(startBtn,&MyPushButton::clicked,[=](){
//           qDebug()<<"点击开始";
           startBtn->zoom1();
           startBtn->zoom2();

//               弹出输入二叉树序列窗口
                 QTimer::singleShot(200,this,[=](){
//                    新建一个窗口对象，其中this指定其父对象就是mainscene，在销毁mainscene也会销毁子对象
                    ergodicSequenceInput = new ErgodicSequenceInput(this);
                    ergodicSequenceInput->setModal(false);//设置为非模态
                    ergodicSequenceInput->show();

                 });

           });
}

void MainScene::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton result=QMessageBox::question(this,"确认","确认退出吗？",
            QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,QMessageBox::No);
    if(result==QMessageBox::Yes)
        event->accept();
    else
        event->ignore();

}



void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter resPainter(this);
//       QPixmap pix;
//       pix.load(":/res/MenuSceneBg.png");
       resPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/res/mainUI.jpg"));

       //画背景图标
       QPixmap pix;
       pix.load(":/res/Title.png");
//       pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
       resPainter.drawPixmap(0,0,pix);


}

MainScene::~MainScene()
{
    delete ui;
}


