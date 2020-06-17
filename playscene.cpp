#include "playscene.h"
#include "mypushbutton.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>

PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{

    this->setFixedSize(900,700);
    this->setWindowTitle("Play Scene 1");


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
                emit this->S1Back();
            });

        });
        MyPushButton *HthBtn = new MyPushButton(":/res/Button/Hth.png");
        HthBtn->setParent(this);
        HthBtn->move(155, 30);
        MyPushButton *DiaBtn = new MyPushButton(":/res/Button/Coin1.png");
        DiaBtn->setParent(this);
        DiaBtn->move(20, 30);
        DiaBtn->setFixedSize(HthBtn->width(),HthBtn->height());

}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/BGScene/S04.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
