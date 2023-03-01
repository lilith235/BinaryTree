#include "ergodicsequenceinput.h"
#include "ui_ergodicsequenceinput.h"
#include "usualpushbutton.h"
#include <QMessageBox>
#include <QPainter>

ErgodicSequenceInput::ErgodicSequenceInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErgodicSequenceInput)
{

    ui->setupUi(this);

    this->setWindowTitle("创建一棵二叉树");
//    去掉标题栏问号按钮
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

        //分别创建两个输入框，用于输入前序和中序

        LE1 = new QLineEdit(this);
        //指定输入框位于父窗口中的位置
        LE1->move(150,100);
        //设置提示信息
        LE1->setPlaceholderText("前序序列");
        //让输入框显示“一键清除”按钮
        LE1->setClearButtonEnabled(true);

        LE2 = new QLineEdit(this);
        //指定输入框位于父窗口中的位置
        LE2->move(150,160);
        //设置提示信息
        LE2->setPlaceholderText("中序序列");
        //让输入框显示“一键清除”按钮
        LE2->setClearButtonEnabled(true);



//        设置确认按钮
        btn1 = new usualPushButton(this);
        btn1->setText("确认");
        //按钮的位置
        btn1->move(90,290);

//        转入下一个场景
        connect(btn1,&usualPushButton::clicked,[=](){
    //               弹出输出二叉树窗口和菜单
        this->btnCreat_clicked(parent);
               });

//        设置取消按钮
        btn2 = new usualPushButton(this);
        btn2->setText("取消");
        //按钮的位置
        btn2->move(390,290);
        connect(btn2,&QPushButton::clicked,this,&QWidget::close);

           //建立信息和槽，当用户点击并释放按钮后，该按钮隐藏。
//           QObject::connect(btn1,&QPushButton::clicked,btn1,&QPushButton::hide);

        //指定窗口的尺寸和显示文字的大小
        this->resize(600,400);
        this->setFont(QFont("宋体",18));

        //        设置输入边框阴影
                QGraphicsDropShadowEffect *shadow_effect1 = new QGraphicsDropShadowEffect(this);
                    shadow_effect1->setOffset(5, 5);
                    shadow_effect1->setColor(QColor(43, 43, 43));
                    shadow_effect1->setBlurRadius(8);
               LE1->setGraphicsEffect(shadow_effect1);

               QGraphicsDropShadowEffect *shadow_effect2 = new QGraphicsDropShadowEffect(this);
                   shadow_effect2->setOffset(5, 5);
                   shadow_effect2->setColor(QColor(43, 43, 43));
                   shadow_effect2->setBlurRadius(8);
               LE2->setGraphicsEffect(shadow_effect2);

               this->setStyleSheet("QLineEdit { background-color: #E1F7FF; border:3px solid #E1F7FF; color: #27506E}");
        //this->setStyleSheet("QLineEdit { border-top: 5px solid qlineargradient(y0:0, y1:1,stop: 0 #ececef, stop: 1 white);border-left: 5px solid qlineargradient(x0:0, x1:1,stop: 0 #ececef, stop: 1 white);border-bottom: 5px solid qlineargradient(y0:0, y1:1,stop: 0 white, stop: 1  #ececef);border-right: 5px solid qlineargradient(x0:0, x1:1,stop:  0 white, stop: 1 #ececef); }");


}

void ErgodicSequenceInput::btnCreat_clicked(QWidget *parent)
{
    QString input1 = this->LE1->text();
    QString input2 = this->LE2->text();
    ShowScene *p = new ShowScene;
    if (p->setInput(input1, input2))
    {
        p->show();
        this->hide();
        parent->hide();
     }
    else
        QMessageBox::warning(this, "警告", "无效的输入");
}

//    背景图
    void ErgodicSequenceInput::paintEvent(QPaintEvent *event)
    {
        QPainter resPainter(this);
           resPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/res/input.jpg"));
    }

ErgodicSequenceInput::~ErgodicSequenceInput()
{
    delete ui;
}
