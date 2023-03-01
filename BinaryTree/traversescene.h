#ifndef TRAVERSESCENE_H
#define TRAVERSESCENE_H
#include <QPushButton>
#include <QMainWindow>
#include "arrayqueue.h"
#include "arraystack.h"
#include "linkedbinarytree.h"
#include <QRectF>
#include <string>

struct stackNode
{
    binaryTreeNode<char>* treeNode;
    int layer;      // 标记该节点属于第几层
};

class TraverseScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit TraverseScene(QWidget *parent = 0);
    //选择遍历方式
    void chooseWay(string a,linkedBinaryTree<char>* Thetree );
    //重写绘图事件
    void paintEvent(QPaintEvent* );

    //初始化四种序列
    void doIt(string s1, string s2, string s3, string s4);
    //结束遍历
    void quitButton_clicked();
    //前序遍历绘图事件中调用方法
    void preOrder();
    //继续遍历下一个节点的方法
    void nextButton_clicked();


private:
    //存储遍历的树
    linkedBinaryTree<char>* myTree;
    QPushButton *nextButton;
    QPushButton *quitButton;

    //表示遍历的方式
    string theWay;
    //前中后层四中序列
    string thepre="";
    string thein="";
    string thepost="";
    string thelevel="";
    //表示经过的节点
    int num=0;
    //遍历时指向当前遍历节点的指针
    binaryTreeNode<char>* popo;
    //存储遍历的树
    arrayQueue<stackNode> * myqueue;
    arrayStack<stackNode> * mystack;

signals:

public slots:
};

#endif // TRAVERSESCENE_H
