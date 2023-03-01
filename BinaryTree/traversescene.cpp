#include "traversescene.h"
#include "usualpushbutton.h"
#include "binarytreenode.h"
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include "showscene.h"

//struct stackNode
//{
//    binaryTreeNode<char>* treeNode;
//    int layer;      // 标记该节点属于第几层
//};

TraverseScene::TraverseScene(QWidget *parent) : QMainWindow(parent)
{
    //配置场景
    //    设置固定大小
        setFixedSize(1668,808);
        //设置图标
        this->setWindowIcon(QIcon(":/res/icon.png"));
        //设置标题
        this->setWindowTitle("遍历二叉树");

        //        设置按钮
                nextButton = new usualPushButton(this);
                nextButton->setText("继续");
                nextButton->move(80,30);
//                进行下一个节点的遍历
                connect(nextButton,&usualPushButton::clicked,[=](){
                    nextButton_clicked();
                       });

                quitButton = new usualPushButton(this);
                quitButton->setText("结束");
                quitButton->move(80,100);
                connect(quitButton,&usualPushButton::clicked,[=](){
                    //quitButton_clicked();
                    this->close();
                       });

                //connect(quitButton,&QPushButton::clicked,this,&QWidget::close);

}

void TraverseScene::chooseWay(string a,linkedBinaryTree<char>* theTree )
{
    theWay = a;
    myTree = theTree;
    //指针初始化为根节点
    popo = myTree->getRoot();
}

void TraverseScene::paintEvent(QPaintEvent *)
{

    //创建QPainter对象
    QPainter painter(this);
    // 反锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    //背景图
    QPixmap pix;
    pix.load(":/res/showUI.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //设置字体
    QFont font;
    font.setPointSize(14);
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
    const qreal Pi = 3.14159;
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
    int curLayer = 1;
    int curAngle;                   // 当前角度
    qreal deg;                      // 当前弧度

    // 将坐标系统的原点移动到初始位置
    painter.translate(W/2, 2*R);

    //初始二叉树
        while (1)
        {
            if(t->element==theWay[num])
            {
                painter.setPen(Qt::green); //划线颜色
                //qDebug()<<t->element<<"X"<<theWay[num]<<endl;
            }
            painter.drawEllipse(node);
            painter.drawText(node, Qt::AlignCenter, QString(t->element));
            painter.setPen(Qt::white);//恢复画笔颜色
            //
//            qDebug()<<t->element<<"X"<<theWay[num]<<endl;

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
                    //num++;
                    return;
                }
            }
            painter.setPen(Qt::white); //划线颜色
        }

}

void TraverseScene::nextButton_clicked()
{
    //已经遍历完一遍
//    if(num-1==myTree->getSize())
//    {
//        qDebug()<<"num"<<num;
//        qDebug()<<"myTree->getSize()"<<myTree->getSize();
//        QMessageBox box(QMessageBox::Information, "遍历结束","请返回主界面");
//        box.setStandardButtons(QMessageBox::Ok | QMessageBox::No|QMessageBox::Cancel);
////        box.setButtonText(QMessageBox::Ok, QString("好的"));
////        box.setButtonText(QMessageBox::No, QString("2"));
////        box.setButtonText(QMessageBox::Cancel, QString("取 消"));
//        int button = box.exec();
//        if (button == QMessageBox::Ok)
//           quitButton_clicked();
//        else
//            return;
//    }
//    else
//    {
        TraverseScene * nse1 = new TraverseScene;
        num++;
        //qDebug()<<num;
        nse1->num=this->num;
        nse1->theWay = this->theWay;
        nse1->myTree = this->myTree;
        nse1->doIt(this->thepre,this->thein,this->thepost,this->thelevel);
        //指针初始化为根节点
        popo = myTree->getRoot();
        qDebug()<<"打开遍历窗口没问题";
        qDebug()<<this->num;
        nse1->show();
        this->close();
//    }

    //update();
}

//初始化四种序列
void TraverseScene::doIt(string s1, string s2, string s3, string s4)
{
    thepre=s1;
    thein=s2;
    thepost=s3;
    thelevel=s4;
}

//void TraverseScene::quitButton_clicked()
//{
//    ShowScene *p = new ShowScene;
//    if (thepre!=""&&thein!="")
//    {
//        p->setInput(thepre,thein);
//        p->show();
//        this->hide();
//        //parent->hide();
//     }
//    else
//        QMessageBox::warning(this, "警告", "无效的输入");
//}




