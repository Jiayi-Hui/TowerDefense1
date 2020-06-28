#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QDebug>
#include<QTimer>

#include "mypushbutton.h"
#include "level.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Mainscene; }
QT_END_NAMESPACE

class Mainscene : public QMainWindow
{
    Q_OBJECT

public:
    Mainscene(QWidget *parent = nullptr);
    ~Mainscene();

    //画背景图
    void paintEvent(QPaintEvent *);
    Level * choice= NULL;
private:
    Ui::Mainscene *ui;
};
#endif // MAINSCENE_H
