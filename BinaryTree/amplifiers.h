#ifndef AMPLIFIERS_H
#define AMPLIFIERS_H
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include<QPushButton>
#include <QPaintEvent>
#include"qpainter.h"
#include<QObject>
#include "usualpushbutton.h"
#include<QVBoxLayout>
#include<QGraphicsDropShadowEffect>
#include "showscene.h"
#include <QDialog>
#include "mainscene.h"

namespace Ui {
class amplifiers;
}

class amplifiers : public QDialog
{
    Q_OBJECT

public:
    //QString str;
    explicit amplifiers(QWidget *parent = 0);
    //记录传入的序列
    void showNode(QString str);
    ~amplifiers();
    void paintEvent(QPaintEvent *event);
private:
    Ui::amplifiers *ui;
    QPushButton * btn1;
    QPushButton * btn2;
};

#endif // AMPLIFIERS_H
