#ifndef MAINSCENE_H
#define MAINSCENE_H
#include "ergodicsequenceinput.h"
#include <QCloseEvent>
#include <QMainWindow>
#include <QFile>


namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();
//    背景图
    void paintEvent(QPaintEvent *event);
//    关闭确认窗口
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainScene *ui;
    ErgodicSequenceInput *ergodicSequenceInput;//添加私有成员，为一个ergodicSequenceInput窗口的指针
};

#endif // MAINSCENE_H
