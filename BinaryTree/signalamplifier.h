#ifndef SIGNALAMPLIFIER_H
#define SIGNALAMPLIFIER_H
#include "BTtree.h"
#include <QPaintEvent>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "usualpushbutton.h"
#include <QWidget>

namespace Ui {
class signalamplifier;
}

class signalamplifier : public QWidget
{
    Q_OBJECT

public:
    explicit signalamplifier(QWidget *parent = 0);
    ~signalamplifier();
    void paintEvent(QPaintEvent *event);
    void Amplifier(BTtree * sb, int tol);//设置信号放大器函数
    CreatBT();//按逻辑结构建立二叉树，依次输入结点、父结点、标号、权值
    void printBTtree();
    //输入节点
    void addOClicked();

private:
    Ui::signalamplifier *ui;

    usualPushButton *addO;
    usualPushButton *finishO;
    usualPushButton *closeO;
    //        设置显示结点个数的标签
    //QLabel *countShow;
    int count;

    //创建树
    BTtree *root, *s;
};

#endif // SIGNALAMPLIFIER_H
