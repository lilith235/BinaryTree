#ifndef SHOWSCENE_H
#define SHOWSCENE_H
#include <QMainWindow>
#include <QPushButton>
#include "linkedbinarytree.h"


//存储四种节点遍历的顺序
struct Orders{
    string preorder="";
    string inorder="";
    string postorder="";
    string levelorder="";
};

class ShowScene : public QMainWindow
{
    Q_OBJECT
//int x=0;
public:
    Orders oo;
    explicit ShowScene(QWidget *parent = 0);
    //输入两种序列
    bool setInput(QString input1, QString input2);
    bool setInput(string input1, string input2);
    //重写绘图事件
    void paintEvent(QPaintEvent* );
    void walkAciton_clicked(int i);
private:
    linkedBinaryTree<char>* myTree;
signals:

public slots:
};

#endif // SHOWSCENE_H
