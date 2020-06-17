#include "playscene2.h"
#include "mypushbutton.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>

playscene2::playscene2(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(900,700);
    this->setWindowTitle("Play Scene 2");

    //返回按钮
        MyPushButton *BackBtn = new MyPushButton(":/res/Button/Back.png");
        BackBtn->setParent(this);
        BackBtn->move(0.9*(this->width()-BackBtn->width()), 50);
      //点击返回
        connect(BackBtn, &MyPushButton::clicked,[=](){
            qDebug() << "BackBtn clicked";
            BackBtn->BounceDown();
            BackBtn->BounceUp();
            QTimer::singleShot(200, this, [=](){
                emit this->S2Back();
            });

        });
        MyPushButton *HthBtn = new MyPushButton(":/res/Button/Hth.png");
        HthBtn->setParent(this);
        HthBtn->move(155,this->height()-80);
        MyPushButton *DiaBtn = new MyPushButton(":/res/Button/Coin1.png");
        DiaBtn->setParent(this);
        DiaBtn->move(20, this->height()-80);
        DiaBtn->setFixedSize(HthBtn->width(),HthBtn->height());
}
void playscene2::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/BGScene/S03.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
