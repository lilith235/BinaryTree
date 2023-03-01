#include "showscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QToolButton>
#include <QDebug>
#include <iostream>
#include <string>
#include "signalamplifier.h"
#include "traversescene.h"
#include "binarytreenode.h"
#include "BSTsence.h"
#include "mainscene.h"
using namespace std;

//struct stackNode
//{
//    binaryTreeNode<char>* treeNode;
//    int layer;      // 标记该节点属于第几层
//};


ShowScene::ShowScene(QWidget *parent) : QMainWindow(parent)
{

    //配置场景
    //    设置固定大小
        setFixedSize(1668,808);

        //设置图标
        this->setWindowIcon(QIcon(":/res/icon.png"));
        //设置标题
        this->setWindowTitle("操作二叉树");
        //创建菜单栏
        QMenuBar * bar=menuBar();
        setMenuBar(bar);
        //创建菜单
        QMenu * oneMenu=bar->addMenu("遍历");
        QMenu * twoMenu=bar->addMenu("应用");
        QMenu * threeMenu=bar->addMenu("特例");
        QMenu * fourMenu=bar->addMenu("结束");
        //创建菜单项
        QAction * preAciton=oneMenu->addAction("前序遍历");
        QAction * inAciton=oneMenu->addAction("中序遍历");
        QAction * postAciton=oneMenu->addAction("后序遍历");
        QAction * levelAciton=oneMenu->addAction("层次遍历");
        QAction * signalAmplifier1 =twoMenu->addAction("信号放大器");
        QAction * BSTAciton=threeMenu->addAction("二叉搜索树");
        QAction * deleteAciton=fourMenu->addAction("删除二叉树");


        this->setStyleSheet("QMenuBar {background-color: white; border: 2px solid #27506E;}"
                            "QMenu { background-color: white; border: 1px solid white;}"
                            "QMenu::item { background-color: transparent; padding:8px 32px; margin:0px 8px; border-bottom:1px solid #DBDBDB;}"
                            "QMenu::item:selected {background-color: #E1F7FF;}");
//        事件响应
//        四种遍历
        connect(preAciton,&QAction::triggered,[=](){
            walkAciton_clicked(1);
        });
        connect(inAciton,&QAction::triggered,[=](){
            walkAciton_clicked(2);
        });
        connect(postAciton,&QAction::triggered,[=](){
            walkAciton_clicked(3);
        });
        connect(levelAciton,&QAction::triggered,[=](){
            walkAciton_clicked(4);
        });

//        信号放大器
        connect(signalAmplifier1,&QAction::triggered,[=](){
            //qDebug()<<"到这里还是正常的";
            signalamplifier * sa = new signalamplifier;
            sa->show();
            this->hide();
        });
//        二叉搜索树
        connect(BSTAciton,&QAction::triggered,[=](){
            //qDebug()<<"到这里还是正常的";
            BSTsence * bst = new BSTsence;
            bst->show();
            this->hide();
        });
        connect(deleteAciton,&QAction::triggered,[=](){
            //qDebug()<<"到这里还是正常的";
            MainScene* m=new MainScene;
            m->show();
            this->hide();
        });


        //创建树
        myTree = new linkedBinaryTree<char>;
}

bool ShowScene::setInput(QString input1, QString input2)
{
    // 将QString转化为C++标准模板库里的String
    std::string s1 = input1.toStdString();
    std::string s2 = input2.toStdString();
    try {
        if (s1 != "" && s2 != "")
        {
            myTree->preAndInCreatBinaryTree(s1, s2);

        }
        else if (s1 != "")
        {
            myTree->preCreatBinaryTree(s1);
        }
        else if (s2 != "")
        {
            myTree->levelCreatBinaryTree(s2);
        }
        binaryTreeNode<char>* t = myTree->root;
        myTree->preorders(t);
        myTree->inorders(t);
        myTree->postorders(t);
        myTree->levelorders();
        oo.preorder = myTree->s1;
        oo.inorder = myTree->s2;
        oo.postorder = myTree->s3;
        oo.levelorder = myTree->s4;
//        qDebug()<<"前"<<oo.preorder[0]<<oo.preorder[1]<<oo.preorder[2]<<oo.preorder[3]<<oo.preorder[4]<<oo.preorder[5]<<oo.preorder[6]<<oo.preorder[7];
//        qDebug()<<"中"<<oo.inorder[0]<<oo.inorder[1]<<oo.inorder[2]<<oo.inorder[3]<<oo.inorder[4]<<oo.inorder[5]<<oo.inorder[6]<<oo.inorder[7];
//        qDebug()<<"后"<<oo.postorder[0]<<oo.postorder[1]<<oo.postorder[2]<<oo.postorder[3]<<oo.postorder[4]<<oo.postorder[5]<<oo.postorder[6]<<oo.postorder[7];
//        qDebug()<<"层"<<oo.levelorder[0]<<oo.levelorder[1]<<oo.levelorder[2]<<oo.levelorder[3]<<oo.levelorder[4]<<oo.levelorder[5]<<oo.levelorder[6]<<oo.levelorder[7];

//            qDebug()<<oo.preorder[0];
//            qDebug()<<oo.preorder[4];

    }
    catch (invalidSequence) {
        return false;
    }
    return true;
}

//字符串的版本
bool ShowScene::setInput(string s1, string s2)
{
    try {
        if (s1 != "" && s2 != "")
        {
            myTree->preAndInCreatBinaryTree(s1, s2);

        }
        else if (s1 != "")
        {
            myTree->preCreatBinaryTree(s1);
        }
        else if (s2 != "")
        {
            myTree->levelCreatBinaryTree(s2);
        }
        binaryTreeNode<char>* t = myTree->root;
        myTree->preorders(t);
        myTree->inorders(t);
        myTree->postorders(t);
        myTree->levelorders();
        oo.preorder = myTree->s1;
        oo.inorder = myTree->s2;
        oo.postorder = myTree->s3;
        oo.levelorder = myTree->s4;
//            qDebug()<<oo.preorder[0];
//            qDebug()<<oo.preorder[4];

    }
    catch (invalidSequence) {
        return false;
    }
    return true;
}


void ShowScene::paintEvent(QPaintEvent *)
{
    //创建QPainter对象
    QPainter painter(this);
    //qDebug()<<"这个几次呐";
    // 反锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    //背景图
    QPixmap pix;
    pix.load(":/res/showUI.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //设置字体
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);

    //设置画笔
    QPen penLine;
    penLine.setWidth(2); //线宽
    penLine.setColor(Qt::white); //划线颜色
    penLine.setStyle(Qt::SolidLine);//线的类型，实线、虚线等
    penLine.setCapStyle(Qt::FlatCap);//线端点样式
    penLine.setJoinStyle(Qt::BevelJoin);//线的连接点样式
    painter.setPen(penLine);

    qreal W = this->width();                            // 画布的宽
    qreal H = this->height();                           // 画布的高
    int treeHeight = myTree->getHeight();               // 树的高度
    qreal R = W / (2 * std::pow(2, treeHeight) + 2);    // 节点的半径
    const int layerHeight = (H-4*R) / (treeHeight-1);     // 层高，即垂直偏移量

    // 初始化
    // 节点的定义
    QRectF node(QPointF(-R, -R), QPointF(R, R));
    arrayStack<stackNode> stack;    // 存放右孩子节点
    stackNode qNode;

    arrayStack<QPointF> points;     // 存放右孩子节点相对于当前坐标系统原点的位置
    QPointF point;

    qreal Hoffset;                  // 水平偏移量
    binaryTreeNode<char>* t = myTree->getRoot();
    const qreal Pi = 3.14159;
    int curLayer = 1;
    int curAngle;                   // 当前角度
    qreal deg;                      // 当前弧度

    // 将坐标系统的原点移动到初始位置
    painter.translate(W/2, 2*R);

        while (1)
        {
            painter.drawEllipse(node);
            painter.drawText(node, Qt::AlignCenter, QString(t->element));
            // 设置孩子节点相对于父节点的水平偏移量
            Hoffset = std::pow(2, (treeHeight - curLayer)) * R;
            deg = std::atan(Hoffset / layerHeight);             // 返回的是弧度
            curAngle = 180 / Pi * deg;                          // 将弧度转化为角度
            if (t->rightChild != NULL)
            {
                // 坐标轴逆时针旋转
                painter.rotate(-curAngle);
                //绘制图形路径
                painter.drawLine(0, R, 0, layerHeight / std::cos(deg) - R);
                // 旋转复原
                painter.rotate(curAngle);
                // 右孩子节点压栈
                qNode.treeNode = t->rightChild;
                qNode.layer = curLayer + 1;
                stack.push(qNode);
                // 右孩子相对于当前坐标系统原点的位置压栈
                points.push(QPointF(QPointF(0, 0) + QPointF(Hoffset, layerHeight)));
                painter.save();
            }
            if (t->leftChild != NULL)
            {
                // 坐标轴顺时针旋转
                painter.rotate(curAngle);
                // 绘制边
                painter.drawLine(0, R, 0, layerHeight / std::cos(deg) - R);
                // 旋转复原
                painter.rotate(-curAngle);
                // 原点移动到左孩子节点的位置
                painter.translate(QPointF(QPointF(0, 0) + QPointF(-Hoffset, layerHeight)));
                t = t->leftChild;
                // 层次加1
                curLayer++;
            }
            else {
                if (!stack.empty()) {
                    // 获取到右节点的层次状态
                    stack.pop(qNode);
                    t = qNode.treeNode;
                    curLayer = qNode.layer;
                    // 原点移动到右孩子节点的位置
                    painter.restore();
                    points.pop(point);
                    painter.translate(point);
                }
                else {
                    painter.resetTransform();
                    return;
                }
            }
        }

}

void ShowScene::walkAciton_clicked(int i)
{
    TraverseScene * nse = new TraverseScene(this);
    nse->doIt(oo.preorder,oo.inorder,oo.postorder,oo.levelorder);
    //string str1=oo.preorder;
//    qDebug()<<"前"<<oo.preorder[0]<<oo.preorder[1]<<oo.preorder[2]<<oo.preorder[3]<<oo.preorder[4]<<oo.preorder[5]<<oo.preorder[6]<<oo.preorder[7];
//    qDebug()<<"中"<<oo.inorder[0]<<oo.inorder[1]<<oo.inorder[2]<<oo.inorder[3]<<oo.inorder[4]<<oo.inorder[5]<<oo.inorder[6]<<oo.inorder[7];
//    qDebug()<<"后"<<oo.postorder[0]<<oo.postorder[1]<<oo.postorder[2]<<oo.postorder[3]<<oo.postorder[4]<<oo.postorder[5]<<oo.postorder[6]<<oo.postorder[7];
//    qDebug()<<"层"<<oo.levelorder[0]<<oo.levelorder[1]<<oo.levelorder[2]<<oo.levelorder[3]<<oo.levelorder[4]<<oo.levelorder[5]<<oo.levelorder[6]<<oo.levelorder[7];

    if(i==1)
    nse->chooseWay(oo.preorder,myTree);
    if(i==2)
    nse->chooseWay(oo.inorder,myTree);
    if(i==3)
    nse->chooseWay(oo.postorder,myTree);
    if(i==4)
    nse->chooseWay(oo.levelorder,myTree);
//    qDebug()<<"打开遍历窗口没问题";
    nse->show();
    //this->hide();

    //update();
}
