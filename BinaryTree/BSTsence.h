#ifndef BSTSENCE_H
#define BSTSENCE_H

#include <QMainWindow>
#include "QPainter"
#include "BSTnode.h"
#include "QSize"

QT_BEGIN_NAMESPACE
namespace Ui { class BSTsence; }
QT_END_NAMESPACE

class BSTsence : public QMainWindow
{
    Q_OBJECT

public:
    BSTsence(QWidget *parent = nullptr);
    ~BSTsence();


private:
    Ui::BSTsence *ui;
    Node* root = nullptr;
    const int recWidth = 50;
    const int recHeight = 30;
    const QSize size = QSize(50,30);
    const int menuBarHeight = 30 ;
    const int levelMagin = 10;

protected:
    void paintEvent(QPaintEvent *event) override;
    void drawNode(Node* node,int x_node,int y_node,QPainter* painter);
    QPoint getRecPos(int y_node,int x_node);

private slots:
    void on_addNode_clicked();
};
#endif // BSTSENCE_H
