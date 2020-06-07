#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QSound>
Mainscene::Mainscene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mainscene)
{
    ui->setupUi(this);
    //配置主场景
    setFixedSize(900,700);
    setWindowTitle("Scene1");
    QSound * voice = new QSound(":/res/BackGroundMusic/BGM11.wav",this);
    voice->play();
}
void Mainscene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/BGScene/map_export_1591535411087.jpeg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

Mainscene::~Mainscene()
{
    delete ui;
}

