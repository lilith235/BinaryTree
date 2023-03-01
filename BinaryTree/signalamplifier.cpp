#include "signalamplifier.h"
#include "ui_signalamplifier.h"
#include "BTtree.h"
#include "qpainter.h"
#include <qDebug>
#include <qstring.h>
#include <QGraphicsDropShadowEffect>
#include <string>
#include "amplifiers.h"
#include <QInputDialog>
#include "mainscene.h"
#include <queue>
#include <iostream>
using namespace std;

typedef enum { L, R } tagtype;

typedef struct
{
    BTtree* ptr;
    tagtype tag;
}stacknode;

typedef struct
{
    stacknode Elem[100];
    int top;
} Stack;

stacknode Pop(Stack& S)
{
    stacknode c;
    c = S.Elem[S.top];
    S.top = S.top - 1;
    return c;
}

void Push(stacknode x, Stack& S)
{
    S.top = S.top + 1;
    S.Elem[S.top] = x;
}

typedef struct
{
    char data, parent, tag;
    int weight;
} Bnode;

typedef struct           //队列
{
    BTtree* ele[100];
    int front, rear;
}Squeue;

void Makenull(Squeue& Q)
{
    Q.front = 0;
    Q.rear = 99;
}

//创建树
Bnode p;
Squeue q;
char wuhu[20];//存放应放置放大器的结点
int i=0;//控制输入

signalamplifier::signalamplifier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signalamplifier)
{

    ui->setupUi(this);

    //    设置图标
        setWindowIcon(QIcon(":/res/icon.png"));

    //    设置标题
        setWindowTitle("信号放大器");

    //        设置按钮
            addO = new usualPushButton(this);
            addO->setText("添加");
            //按钮的位置
            addO->move(100,740);

            finishO = new usualPushButton(this);
            finishO->setText("完成");
            //按钮的位置
            finishO->move(290,740);

            closeO = new usualPushButton(this);
            closeO->setText("取消");
            //按钮的位置
            closeO->move(480,740);

            connect(closeO,&usualPushButton::clicked,[=](){
            MainScene* m=new MainScene;
            m->show();
            this->hide();
            //parent->hide();
                   });

     //        设置显示结点个数的标签
            count=0;
            //countShow = new QLabel(this);
            QString str = QString::number(count);
            ui->countShow->setText(str);

            //        设置输入边框阴影
                    QGraphicsDropShadowEffect *shadow_effect1 = new QGraphicsDropShadowEffect(this);
                        shadow_effect1->setOffset(5, 5);
                        shadow_effect1->setColor(QColor(43, 43, 43));
                        shadow_effect1->setBlurRadius(8);
                   ui->selfO->setGraphicsEffect(shadow_effect1);
                   QGraphicsDropShadowEffect *shadow_effect2 = new QGraphicsDropShadowEffect(this);
                       shadow_effect2->setOffset(5, 5);
                       shadow_effect2->setColor(QColor(43, 43, 43));
                       shadow_effect2->setBlurRadius(8);
                  ui->parentO->setGraphicsEffect(shadow_effect2);
                  QGraphicsDropShadowEffect *shadow_effect3 = new QGraphicsDropShadowEffect(this);
                      shadow_effect3->setOffset(5, 5);
                      shadow_effect3->setColor(QColor(43, 43, 43));
                      shadow_effect3->setBlurRadius(8);
                 ui->weightO->setGraphicsEffect(shadow_effect3);
                 QGraphicsDropShadowEffect *shadow_effect4 = new QGraphicsDropShadowEffect(this);
                     shadow_effect4->setOffset(5, 5);
                     shadow_effect4->setColor(QColor(43, 43, 43));
                     shadow_effect4->setBlurRadius(8);
                ui->comboBox->setGraphicsEffect(shadow_effect4);

            this->setStyleSheet("QLineEdit { background-color: #E1F7FF; border:3px solid #E1F7FF; color: #27506E}"
                                "#label{ color: #E1F7FF}"
                                "#label2{ color: #E1F7FF}"
                                "#label3{ color: #E1F7FF}"
                                "#label4{ color: #E1F7FF}"
                                "#label5{ color: #E1F7FF}"
                                "#countShow{ color: #00B050}"
                                "QComboBox{ background-color: #27506E;selection-background-color: #27506E; color: #E1F7FF}"
                                );
//    逻辑实现部分

                root = new BTtree();
                root = NULL;
                Makenull(q);
//                添加结点
                connect(addO,&usualPushButton::clicked,[=](){
                    addOClicked();
                    count++;
          //        设置显示结点个数的标签
                    QString str = QString::number(count);
                    ui->countShow->setText(str);
                    ui->selfO->setText("");
                    ui->parentO->setText("");
                    ui->weightO->setText("");
                       });
//                完成创建树，弹出输入最大衰减量界面
                connect(finishO,&usualPushButton::clicked,[=](){
                    //printBTtree();
                    bool bOk = false;
                    QString sName = QInputDialog::getText(this,
                                                             "衰减量",
                                                             "设置容忍值",
                                                             QLineEdit::Normal,
                                                             "3",
                                                             &bOk
                                                             );

                        if (bOk && !sName.isEmpty()) {
                            int tolerance;//最大衰减量
                            tolerance = sName.toInt();

                            Amplifier(root, tolerance);
                            //std::cout<<"在这里"<<wuhu<<endl;
//                            将char[]转换为String
//                            for(int j=0;j<=i-1;j++){
//                                strrr+=wuhu[i];
//                            }
                            //qDebug()<<"出来的是啥"<<wuhu[0]<<wuhu[1]<<wuhu[2];
                            //qDebug("十进制：%d", i);
                            //qDebug()<<"哈哈哈"<<strrr[0]<<strrr[1]<<strrr[2]
                            QString ss= QString::fromLocal8Bit(wuhu);
//                            qDebug()<<"这个是"<<ss;
                            amplifiers *am=new amplifiers(this);
                            am->showNode(ss);
                            am->show();
                            root=NULL;
                            i=0;
                            count=0;
                            s=NULL;
                            QString str = QString::number(count);
                            ui->countShow->setText(str);
                        }
                       });

}

void signalamplifier::paintEvent(QPaintEvent *event)
{
    QPainter resPainter(this);
       resPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/res/RepeaterBG.jpg"));
       //画背景图标
       QPixmap pix;
       pix.load(":/res/logol2.png");
//     pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
       resPainter.drawPixmap(0,0,pix);
}

signalamplifier::CreatBT()                   //按逻辑结构建立二叉树，依次输入结点、父结点、标号、权值
{
//    while (p.data != '0')
//    {
        s = new BTtree();
        s->data = p.data;
        s->weight = p.weight;
        s->lchild = s->rchild = NULL;
        q.rear = (q.rear + 1) % 100;
        q.ele[q.rear] = s;
        if (p.parent == '0')
            root = s;
        else
        {
            while (q.rear + 1 % 100 != q.front && q.ele[q.front]->data != p.parent)
                q.front = (q.front + 1) % 100;
            if (q.ele[q.front]->data == p.parent)
            {
                if (p.tag == 'L')
                    q.ele[q.front]->lchild = s;
                else
                    q.ele[q.front]->rchild = s;
            }
        }
        //cin >> p.data >> p.parent >> p.tag >> p.weight;
   // }
    //return root;
}

void signalamplifier::addOClicked(){
    //std::string typehh;
    std::string selfhh;
    std::string parenthh;
    int weighthh;
    int  numm  =  ui->comboBox->currentIndex();
    //根
    if(numm==0){
        p.tag='0';
        p.weight=0;
        p.parent='0';
        QString input1 = ui->selfO->text();
        selfhh = input1.toStdString();
        p.data=selfhh[0];
        parenthh="0";
    }
    else if(numm==1){
        p.tag='L';
        QString input3 = ui->weightO->text();
        weighthh = input3.toInt();
        p.weight=weighthh;
        QString input1 = ui->selfO->text();
        selfhh = input1.toStdString();
        p.data=selfhh[0];
        QString input2 = ui->parentO->text();
        parenthh = input2.toStdString();
        p.parent=parenthh[0];
    }
    else {
        p.tag='R';
        QString input3 = ui->weightO->text();
        weighthh = input3.toInt();
        p.weight=weighthh;
        QString input1 = ui->selfO->text();
        selfhh = input1.toStdString();
        p.data=selfhh[0];
        QString input2 = ui->parentO->text();
        parenthh = input2.toStdString();
        p.parent=parenthh[0];
    }
    CreatBT() ;
//    qDebug()<<"添加节点";
}

void signalamplifier::Amplifier(BTtree * sb, int tol)                     //设置信号放大器函数
{
    BTtree* t;
    Stack s;
    stacknode x;
    s.top = 0;
    t = sb;
    do
    {
        while (t != NULL)
        {
            x.ptr = t;
            x.tag = L;
            Push(x, s);
            t = t->lchild;
        }
        while (s.top != 0 && s.Elem[s.top].tag == R)
        {
            x = Pop(s);
            t = x.ptr;
            if (t->lchild == NULL && t->rchild == NULL)
            {
                t->D = 0;                          //初始化
            }
            else if (t->lchild == NULL && t->rchild != NULL)
            {
                t->D = t->rchild->D + t->rchild->weight;              //只有右子树时当前最大衰减量
                if (t->D > tol)                  //大于容忍值则设置放大器
                {
//                    cout << "放置放大器";
                    wuhu[i] = t->rchild->data;
//                    qDebug()<<"1"<<t->rchild->data;
                    i++;
                    t->D = t->rchild->weight;
                }

            }
            else if (t->lchild != NULL && t->rchild == NULL)      //只有左子树时当前最大衰减量
            {
                t->D = t->lchild->D + t->lchild->weight;
                if (t->D > tol)                  //大于容忍值则放置放大器
                {
//                    cout << "放置放大器";
                    wuhu[i] = t->lchild->data;
//                    qDebug()<<"2"<<t->lchild->data;
                    i++;
                    t->D = t->lchild->weight;
                }
            }
            else if ((t->lchild->D + t->lchild->weight) > (t->rchild->D + t->rchild->weight))        //左子树衰减量大于右子树
            {
                t->D = t->lchild->D + t->lchild->weight;             //更新最大衰减量
                if (t->D > tol)
                {
//                    cout << "放置放大器";              //放置放大器
                    wuhu[i] = t->lchild->data;
//                    qDebug()<<"3"<<t->lchild->data;
                    i++;
                    if ((t->rchild->D + t->rchild->weight) > (t->lchild->weight))         //进一步比较
                    {
                        t->D = t->rchild->D + t->rchild->weight;        //更新
                        if (t->D > tol)
                        {
//                            cout << "放置放大器";
                            wuhu[i] = t->rchild->data;
//                            qDebug()<<"4"<<t->rchild->data;
                            i++;
                            if ((t->rchild->weight) > (t->lchild->weight))                //进一步比较
                                t->D = t->rchild->weight;
                            else
                                t->D = t->lchild->weight;       //更新
                        }
                    }
                    else
                        t->D = t->lchild->weight;        //更新
                }
            }
            else if ((t->rchild->D + t->rchild->weight) >= (t->lchild->D + t->lchild->weight))       //右子树衰减量大于左子树
            {
                t->D = t->rchild->D + t->rchild->weight;
                if (t->D > tol)
                {
//                    cout << "放置放大器";         //大于容忍值放置放大器
//                    cout << t->rchild->data << endl;
                    wuhu[i] = t->rchild->data;
//                    qDebug()<<"5"<<t->rchild->data;
                    i++;
                    if ((t->lchild->D + t->lchild->weight) > (t->rchild->weight))         //进一步比较
                    {
                        t->D = t->lchild->D + t->lchild->weight;         //更新
                        if (t->D > tol)
                        {
//                            cout << "放置放大器";
//                            cout << t->lchild->data << endl;
                            wuhu[i] = t->lchild->data;
//                            qDebug()<<"6"<<t->lchild->data;
                            i++;
                            if ((t->rchild->weight) > (t->lchild->weight))                //进一步比较
                                t->D = t->rchild->weight;
                            else
                                t->D = t->lchild->weight;
                        }
                    }
                    else
                        t->D = t->rchild->weight;
                }
            }
        }
        if (s.top != 0)
        {
            s.Elem[s.top].tag = R;
            t = s.Elem[s.top].ptr->rchild;
        }
    } while (s.top != 0);

}
//debug用，打印出树
void signalamplifier::printBTtree(){
    BTtree* btn = root;
        queue<BTtree*> q;
        q.push(root);
        //char str[50];
//        qDebug()<< "开始";
        for (int i = 0; !q.empty(); i++) {
            //qDebug()<<"i="<<i;
            //str[i] = q.front()->element;
//            qDebug()<< q.front()->data;
            if (q.front()->lchild) {
                q.push(q.front()->lchild);
            }
            if (q.front()->rchild) {
                q.push(q.front()->rchild);
            }
            q.pop();
        }
        //s4=str;
}

signalamplifier::~signalamplifier()
{
    delete ui;
}
