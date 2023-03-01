#include "BSTsence.h"
#include "ui_BSTsence.h"
#include "QPainter"
#include "QDebug"
#include "QtMath"
#include "QVector"
#include <QGraphicsDropShadowEffect>
#include <QMenuBar>
#include "mainscene.h"

BSTsence::BSTsence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BSTsence)
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
        setWindowTitle("二叉搜索树的动态创建");


//        美化按钮和输入框


        //调整按钮的尺寸
        ui->addNode->resize(120,50);
        //        设置按钮边框阴影
        QGraphicsDropShadowEffect *shadow_effect3 = new QGraphicsDropShadowEffect(this);
        shadow_effect3->setOffset(5, 5);
        shadow_effect3->setColor(QColor(43, 43, 43));
        shadow_effect3->setBlurRadius(8);
        ui->addNode->setGraphicsEffect(shadow_effect3);

        //调整按钮的尺寸
        ui->closeIT->resize(120,50);
        //        设置按钮边框阴影
        QGraphicsDropShadowEffect *shadow_effect2 = new QGraphicsDropShadowEffect(this);
        shadow_effect2->setOffset(5, 5);
        shadow_effect2->setColor(QColor(43, 43, 43));
        shadow_effect2->setBlurRadius(8);
        ui->closeIT->setGraphicsEffect(shadow_effect2);

        //        设置输入边框阴影
                QGraphicsDropShadowEffect *shadow_effect1 = new QGraphicsDropShadowEffect(this);
                    shadow_effect1->setOffset(5, 5);
                    shadow_effect1->setColor(QColor(43, 43, 43));
                    shadow_effect1->setBlurRadius(8);
               ui->NodeInput->setGraphicsEffect(shadow_effect1);
               this->setStyleSheet("QLineEdit { background-color: #E1F7FF; border:3px solid #E1F7FF; color: #27506E}"
                                   "QPushButton:hover{font:22px; color:#295378; background-color: #E1F7FF; border-width:3px; border-color:#27506E; border-radius: 20px;}"
                                   "QPushButton{font:22px; color:#E1F7FF; background-color: #295378; border-width:3px; border-color:#E1F7FF; border-radius: 20px;}"
                                   "QMenuBar {background-color: white; border: 2px solid #27506E;}"
                                   "QMenu { background-color: white; border: 1px solid white;}"
                                   "QMenu::item { background-color: transparent; padding:8px 32px; margin:0px 8px; border-bottom:1px solid #DBDBDB;}"
                                   "QMenu::item:selected {background-color: #E1F7FF;}");

               connect(ui->closeIT,&usualPushButton::clicked,[=](){
               MainScene* m=new MainScene;
               m->show();
               this->hide();
                      });

}

BSTsence::~BSTsence()
{
    delete ui;
}

void BSTsence::paintEvent(QPaintEvent *)
{
    static int num = 0;
    num ++;
//    qDebug() <<"graph frame:" <<num;
//    QRect rec(x_node*(recWidth+5),y_node*(recHeight+2),recWidth,recHeight);
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/res/mainUI.jpg"));

    //画背景图标
    QPixmap pix;
    pix.load(":/res/logol3.png");
    painter.drawPixmap(0,560,pix);
    QFont font("微软雅黑",18);
    painter.setFont(font);

    if(root!=nullptr)
    drawNode(root,0,0,&painter);

}


void BSTsence::on_addNode_clicked()
{
    int value = ui->NodeInput->text().toInt();
//    qDebug() << "value:" << value;
    if(root == nullptr){
        root = new Node(value);
        //qDebug()  << "add a root:"<< value;
//        root->preOrderTraversal();
        ui->NodeInput->setText("");
        update();
        return ;

    }
    root->addNode(value);
//    root->preOrderTraversal();
    //qDebug() <<"add a node:" << value;
    ui->NodeInput->setText("");
    update();
}

//x,y start at 0
void BSTsence::drawNode(Node* node,int x_node  ,int y_node,QPainter* painter){
    if(node==nullptr)
        return ;

    // 反锯齿
//    painter->setRenderHint(QPainter::Antialiasing);
//    painter->setRenderHint(QPainter::TextAntialiasing);
    //设置字体
    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    painter->setFont(font);
    //设置画笔
    QPen penLine;
    penLine.setWidth(2); //线宽
//    penLine.setColor(Qt::white); //划线颜色
    penLine.setStyle(Qt::SolidLine);//线的类型，实线、虚线等
    penLine.setCapStyle(Qt::FlatCap);//线端点样式
    penLine.setJoinStyle(Qt::BevelJoin);//线的连接点样式
    painter->setPen(penLine);
    QPoint point(getRecPos(y_node,x_node));
    QRect rec(point,size);
//    painter->drawRect(rec);

    painter->setPen(QPen(Qt::green,3));//设置画笔形式  或者Qpen pen; pen.setColor(QColor(40, 115, 216)); pen.setWidth(2);
    painter->drawRect(rec);
    painter->setPen(QPen(Qt::white,3));

    painter->drawText(rec,Qt::AlignCenter,QString::number(node->value()));
//    qDebug() << "drawNode:"<< node->value() << y_node << x_node;

    if(y_node >= 1){
        if(x_node == 1){
            QPoint p1(getRecPos(y_node,x_node));
            QPoint p2(getRecPos(y_node-1,(x_node-1)/2));
            p1+=QPoint(recWidth/2,0);
            p2+=QPoint(recWidth/2,recHeight);
            painter->drawLine(p1,p2);
        }

        else {
            QPoint p1(getRecPos(y_node,x_node));
            QPoint p2(getRecPos(y_node-1,x_node/2));
            p1+=QPoint(recWidth/2,0);
            p2+=QPoint(recWidth/2,recHeight);
            painter->drawLine(p1,p2);
        }
    }

    if(node->left!=nullptr)
        drawNode(node->left,x_node*2,y_node+1,painter);
    if(node->right!= nullptr)
        drawNode(node->right,x_node*2+1,y_node+1,painter);

}

//y x start at 0
QPoint BSTsence::getRecPos(int y_node, int x_node)
{

    //第y层节点和空隙的数量和,用于计算rec的方位
    int numX = qPow(2,y_node) + 1;
    int blockWidth = this->width() / numX;

    try {
        if(x_node>=qPow(2,y_node))
            throw 1;
        if(blockWidth<recWidth)
            throw 2;
    } catch (int e) {
        switch (e) {
        case 1:qDebug() << "Error:x_node >= 2^y_node x,y wrong";break;
        case 2:qDebug() << "Warning:blockWidth<recWidth ,try bigger widget or small tree";break;

        }
    }
    //qDebug() << x_node*blockWidth*2+blockWidth << menuBarHeight+y_node*(recHeight+5);
    return QPoint(x_node*blockWidth+blockWidth,
           menuBarHeight+y_node*(recHeight+levelMagin));

}
