#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QTimer>
Mainscene::Mainscene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mainscene)
{
    ui->setupUi(this);
    //配置主场景
    setFixedSize(1000,700);
    setWindowTitle("StartScene");
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //开始按钮
    MyPushButton *startbtn=new MyPushButton(":/res/Button/Start2.png");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.2);

    //选择关卡
    choice = new Level;
    connect(choice,&Level::LevelBack,this,[=](){
        choice->hide();
        this->show();
    });

    connect(startbtn, &MyPushButton::clicked,[=](){
        qDebug() << "startBtn clicked";
        //产生弹起特效
            startbtn->BounceDown();
            startbtn->BounceUp();
            //延时进入到选择关卡中
            QTimer::singleShot(200, this, [=](){
            //设置levelScenen场景位置
            //choice->setGeometry(this->geometry());
            this->hide();
            choice->show();


            });
    });
}
void Mainscene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Scene/MainScene.JPG");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
Mainscene::~Mainscene()
{
    delete ui;
}

