#include "level.h"
#include "mypushbutton.h"
#include <QDebug>
Level::Level(QWidget *parent) : QMainWindow(parent)
{
 //配置选择关卡场景
    this->setFixedSize(900,700);
    //设置图标
    this->setWindowTitle("Choose Your Level");
    this->setWindowIcon(QIcon(":/res/Tower/f4f27b1fd2b54349b6a61b9e47ec0a3e.png"));

    //创建菜单栏
            QMenuBar *bar = menuBar();
            setMenuBar(bar);
            QMenu *startMenu = bar->addMenu("tool");
            QAction * quitAction = startMenu->addAction("quit");
            connect(quitAction, &QAction::triggered, [=](){
                this->close();
            });


            //返回按钮
                MyPushButton *BackBtn = new MyPushButton(":/res/Button/Back.png");
                BackBtn->setParent(this);
                BackBtn->move(0.9*(this->width()-BackBtn->width()), 50);

                    MyPushButton *ChsBtn = new MyPushButton(":/res/Button/Select.png");
                    ChsBtn->setParent(this);
                    ChsBtn->move(0.37*this->width(), 50);
              //点击返回
                connect(BackBtn, &MyPushButton::clicked,[=](){
                    qDebug() << "BackBtn clicked";
                    BackBtn->BounceDown();
                    BackBtn->BounceUp();
                    QTimer::singleShot(200, this, [=](){
                        emit this->LevelBack();
                    });

                });
            //关卡按钮
                  MyPushButton *level1Btn = new MyPushButton(":/res/Button/2.png");
                  MyPushButton *level2Btn = new MyPushButton(":/res/Button/3.png");
                  MyPushButton *level3Btn = new MyPushButton(":/res/Button/4.png");
                  level1Btn->setParent(this);
                  level2Btn->setParent(this);
                  level3Btn->setParent(this);
                  level1Btn->move(62,110);
                  level2Btn->move(260,170);
                  level3Btn->move(115,370);

                    S1 =new PlayScene;
                    S2 =new playscene2;



                    //监听level1的返回按钮
                            connect(S1, &PlayScene::S1Back, [=](){
                                this->setGeometry(S1->geometry());
                                S1->hide();
                                this->show();
                            });


                            connect(level1Btn, &MyPushButton::clicked, [=](){
                                level1Btn->BounceDown();
                                level1Btn->BounceUp();
                                QTimer::singleShot(200,this,[=](){
                                    S1->setGeometry(this->geometry());
                                    this->hide();
                                    S1->show();
                                });
                            });
                            //监听level2的返回按钮
                            connect(S2, &playscene2::S2Back, [=](){
                                this->setGeometry(S2->geometry());
                                S2->hide();
                                this->show();
                            });
                            connect(level2Btn, &MyPushButton::clicked, [=](){
                                level2Btn->BounceDown();
                                level2Btn->BounceUp();
                                QTimer::singleShot(200,this,[=](){
                                   S2->setGeometry(this->geometry());
                                    this->hide();
                                   S2->show();
                                });
                            });




}

void Level::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Scene/Choice.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
