#ifndef ERGODICSEQUENCEINPUT_H
#define ERGODICSEQUENCEINPUT_H
#include <QDialog>
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


namespace Ui {
class ErgodicSequenceInput;
}

class ErgodicSequenceInput : public QDialog
{
    Q_OBJECT

public:
    explicit ErgodicSequenceInput(QWidget *parent = 0);
    //    背景图
    void paintEvent(QPaintEvent *event);
    void btnCreat_clicked(QWidget *parent);
    ~ErgodicSequenceInput();
    ShowScene * showScene = NULL;

private slots:


private:
    Ui::ErgodicSequenceInput *ui;
    QLineEdit *LE1;
    QLineEdit *LE2;
    usualPushButton *btn1;
    QPushButton *btn2;
};

#endif // ERGODICSEQUENCEINPUT_H
