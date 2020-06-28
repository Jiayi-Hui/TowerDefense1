#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QSound>
#include <cmath>
#include "playscene.h"
#include "mypushbutton.h"
#include "tower.h"
#include "config.h"


PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{

    this->setFixedSize(900,700);
    this->setWindowTitle("Play Scene 1");
    initialLocBtnAndTower();
    setButtons();
    setLabels();
    BuildTower();
    QSound* BGM=new QSound("qrc:/res/BackgroundMusic/BGM01.wav");
     QSound* Death=new QSound("qrc:/res/Sound/Bird.wav");
    //返回按钮
        MyPushButton *BackBtn = new MyPushButton(":/res/Button/Back.png");
        BackBtn->setParent(this);
        BackBtn->move(0.9*(this->width()-BackBtn->width()), 50);
        connect(BackBtn, &MyPushButton::clicked,[=](){
            qDebug() << "BackBtn clicked";
            BackBtn->BounceDown();
            BackBtn->BounceUp();
            BGM->stop();
            QTimer::singleShot(200, this, [=](){
                emit this->S1Back();
            });
        });

         //插入怪物定时器
        QTimer* timer = new QTimer(this);
        timer->start(1200);
         connect(timer,&QTimer::timeout,[=]()
           {
                   //设置路径点
            CoorStr* Waypointarr[] =
           {
            new CoorStr(0,this->height()*0.5), new CoorStr(50,this->height()*0.5), new CoorStr(100,this->height()*0.5),new CoorStr(160,this->height()*0.5), new CoorStr(160,this->height()*0.5-50), new CoorStr(160,this->height()*0.5-100),
            new CoorStr(160,this->height()*0.5-150),new CoorStr(160,this->height()*0.5-200),new CoorStr(200,this->height()*0.5-220),new CoorStr(250,this->height()*0.5-220),new CoorStr(300,this->height()*0.5-220),new CoorStr(350,this->height()*0.5-220),
            new CoorStr(420,this->height()*0.5-220),new CoorStr(420,this->height()*0.5-150),new CoorStr(420,this->height()*0.5-100),new CoorStr(420,this->height()*0.5-50),new CoorStr(420,this->height()*0.5),new CoorStr(420,this->height()*0.5+50),
            new CoorStr(420,this->height()*0.5+140),new CoorStr(470,this->height()*0.5+140),new CoorStr(520,this->height()*0.5+140),new CoorStr(570,this->height()*0.5+140),new CoorStr(670,this->height()*0.5+140),new CoorStr(670,this->height()*0.5+80),
            new CoorStr(670,this->height()*0.5),new CoorStr(670,this->height()*0.5-50),new CoorStr(670,this->height()*0.5-80),new CoorStr(770,this->height()*0.5-80),new CoorStr(770,this->height()*0.5-130)
            };

            //每条路径的结点个数
            int PathLength = sizeof(Waypointarr)/sizeof(CoorStr*);
            ProdEnemy(Waypointarr,PathLength);
            //更新怪物坐标
            for (auto Moni = EnemyVec.begin(); Moni != EnemyVec.end(); Moni++)
           {
                 (*Moni)->updatePosition();
            }
           });

         //点击开始按钮怪物移动
         QTimer* timer2 = new QTimer(this);
         MyPushButton *startBtn = new MyPushButton(":/res/Button/stt.png");
         startBtn->setParent(this);
         startBtn->move(10, this->height()*0.53);
         connect(startBtn, &MyPushButton::clicked, [=](){
             timer2->start(100);
              BGM->play();
         connect(timer2,&QTimer::timeout,[=]()
           {
               //怪物移动
               for (auto Moni = EnemyVec.begin(); Moni != EnemyVec.end(); Moni++)
{
//                   if((*Moni)->GetId()!=4)
//                        leftEnemy++;
                   if((*Moni)->Move()) //怪物走到终点
                   {
                       delete *Moni;
                       EnemyVec.erase(Moni);    //删除这个怪物
                       if((*Moni)->GetId()!=4)
                            health--;          //生命数量-1
                       else health-=0;
                       if(health==0)
                       {
                           BGM->stop();
                           QSound* Lose=new QSound("qrc:/res/Sound/Lose2.wav");
                          Lose->play();
                           QMessageBox message(QMessageBox::NoIcon, "Lose", "Game over！");
                                message.setIconPixmap(QPixmap(":/res/Button/GameOver.png"));
                                message.exec();
                       }
                       hthlabel->setText(QString("%1").arg(health));

                       break;
                   }
               }
               update();   //绘图
           });
          });

         //攻击判断
           QTimer* timer3 = new QTimer(this);
           timer3->start(1000);
           connect(timer3,&QTimer::timeout,[=]()
                            {
                              for(int j = 0; j < Level1TowerNumber; j ++)
                                 { can[j]->temInterval += 5;
                                  if(can[j]->temInterval >= can[j]->attackSpeed)
                                     {    for (auto Moni = EnemyVec.begin(); Moni != EnemyVec.end(); Moni++)
                                         {
                                             if(can[j]->judgeRect.intersects((*Moni)->m_Rect) && (*Moni)->isAlive&&(*Moni)->GetId()!=4)
                                             {
                                                 can[j]->shoot((*Moni)->GetX(), (*Moni)->GetY());
                                                 qDebug() << "Attack1！";
                                                 (*Moni)->health -= 2;
                                                 if((*Moni)->health <= 0)
                                                 {
                                                     this->diamond += (*Moni)->orihealth;
                                                     (*Moni)->isAlive = false;
                                                      dead++;
                                                      if(counter==46&&leftEnemy==0)
                                                      {
                                                          QSound* Win=new QSound("qrc:/res/Sound/Win.wav");
                                                           Win->play();
                                                           QMessageBox message(QMessageBox::NoIcon, "Win", "Congratulations！");
                                                                message.setIconPixmap(QPixmap(":/res/Button/Victory.png"));
                                                                message.exec();
                                                      }
                                                 }can[j]->temInterval = 0;
                                                 break;

                                             }
                                      }
                                  }
                              }
                              for(int j = 0; j < Level1TowerNumber; j ++)
                                              {
                                                  magic[j]->temInterval += 5;
                                                  if(magic[j]->temInterval >= magic[j]->attackSpeed)
                                                  {
                                                      for (auto Moni = EnemyVec.begin(); Moni != EnemyVec.end(); Moni++)
                                                            {
                                                         if(magic[j]->judgeRect.intersects((*Moni)->m_Rect) && (*Moni)->isAlive&&(*Moni)->GetId()!=4)
                                                             {
                                                                magic[j]->shoot((*Moni)->GetX(), (*Moni)->GetY());
                                                                 (*Moni)->health -= 3;
                                                                 qDebug() << "Attack2!";

                                                                if((*Moni)->health <3)
                                                             {
                                                                 this->diamond += (*Moni)->orihealth;
                                                               (*Moni)->isAlive = false;
                                                                delete *Moni;
                                                                EnemyVec.erase(Moni);
                                                                Death->play();
                                                                 dead++;
                                                                 if(counter==46&&leftEnemy==0)
                                                                 {
                                                                     QSound* Win=new QSound("qrc:/res/Sound/Win.wav");
                                                                      Win->play();
                                                                      QMessageBox message(QMessageBox::NoIcon, "Win", "Congratulations！");
                                                                           message.setIconPixmap(QPixmap(":/res/Button/Victory.png"));
                                                                           message.exec();
                                                                 }
                                                                qDebug() << "Deleted";

                                                         }
                                                            break;
                                                             magic[j]->temInterval = 0;
                                           }
                                         }
                                       }
                                 }
                            dialabel->setText(QString("%1").arg(diamond));
                     });
           if(dead==leftEnemy&&dead!=0)
           {
               QSound* Win=new QSound("qrc:/res/Sound/Win.wav");
                Win->play();
                QMessageBox message(QMessageBox::NoIcon, "Win", "Congratulations！");
                     message.setIconPixmap(QPixmap(":/res/Button/Victory.png"));
                     message.exec();
           }
}
//产生怪物
void PlayScene::ProdEnemy(CoorStr** Waypointarr, int PathLength)
{
     if(counter >= 0 && counter <= 5)
     {EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,1));
            leftEnemy++;}
     else  if( counter <= 12)
     {EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,4));
      leftwave=3;
      wavlabel->setText(QString("%1/4").arg(leftwave));}
     else  if( counter <= 16)
     {EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,2));
     leftEnemy++;}
     else  if( counter <= 20)
     {EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,4));
      leftwave=2;
      wavlabel->setText(QString("%1/4").arg(leftwave));}
     else  if( counter <= 26)
        { EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,2));
     leftEnemy++;}
     else  if( counter <= 30)
        { EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,1));
     leftEnemy++;}
     else  if( counter <= 40)
     {EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,4));
      leftwave=1;
      wavlabel->setText(QString("%1/4").arg(leftwave));}
     else  if( counter <= 45)
     {EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,2));
      leftwave=0;
      wavlabel->setText(QString("%1/4").arg(leftwave));
     leftEnemy++;}
    counter++;
     update();
}
void PlayScene::initialLocBtnAndTower()
{
    for(int i = 0; i < Level1TowerNumber; i ++)
    {
        magic[i] = new magicTower(Level1Loc_X[i], Level1Loc_Y[i]);
        can[i] = new Cannon(Level1Loc_X[i], Level1Loc_Y[i]);
        locBtn[i] = new BuildButton();
        locBtn[i]->setParent(this);
        locBtn[i]->move(Level1Loc_X[i], Level1Loc_Y[i]);
        locBtn[i]->setLoc(Level1Loc_X[i], Level1Loc_Y[i]);
        btb[i] = new buildTowerBtn;
        btb[i]->setParent(this);
        btb[i]->move(-200, -200);
    }

}
void PlayScene::setButtons(){
        MyPushButton *HthBtn = new MyPushButton(":/res/Button/Hth.png");
        HthBtn->setParent(this);
        HthBtn->move(155, 30);
        MyPushButton *DiaBtn = new MyPushButton(":/res/Button/Coin1.png");
        DiaBtn->setParent(this);
        DiaBtn->move(20, 30);
        DiaBtn->setFixedSize(HthBtn->width(),HthBtn->height());
        MyPushButton *WavBtn = new MyPushButton(":/res/Button/stt1.png");
        WavBtn->setParent(this);
        WavBtn->move(20, this->height()-100);
}
//设置标签
void PlayScene::setLabels(){
    dialabel->move(90, 45);       //位置
    setStyleSheet("color:white");   //设置颜色
    dialabel->setFont(QFont("Arial Unicode MS", 24));             //设置金钱标签属性
    dialabel->setText(QString("%1").arg(diamond));    //显示金钱信息
    hthlabel->move(230,45);   //设置控件位置和大小
    hthlabel->setFont(QFont("Arial Unicode MS", 24));
    hthlabel->setText(QString("%1").arg(health));
    wavlabel->move(80,this->height()-90);
    wavlabel->setFont(QFont("Arial Unicode MS", 24));             //设置金钱标签属性
    wavlabel->setText(QString("%1/4").arg(leftwave));
}
void  PlayScene::BuildTower(){
    for(int i = 0; i < Level1TowerNumber; i ++)
    {
        connect(locBtn[i], &BuildButton::clicked, [=](){
                if(locBtn[i]->GetLevelStatus() == 0)
                {
                    btb[i]->move(Level1Loc_X[i]-20, Level1Loc_Y[i]-20);

                    connect(btb[i], &buildTowerBtn::clicked, [=](){

                        if(this->diamond >= can[i]->buildCost||this->diamond>= magic[i]->buildCost)
                        {
                                                if(btb[i]->getTowerType() == 1)
                                                {

                                                    locBtn[i]->getTowerCannon(can[i], btb[i]->getTowerType());
                                                    btb[i]->move(-200, -200);
                                                    can[i]->built=true;
                                                    diamond-= can[i]->buildCost;
                                                }

                                                else if(btb[i]->getTowerType() == 2)
                                                {
                                                    locBtn[i]->getTowerMagic(magic[i], btb[i]->getTowerType());
                                                    btb[i]->move(-200, -200);
                                                    magic[i]->built=true;
                                                    diamond-= magic[i]->buildCost;
                                                }
                        }
                        else  QMessageBox::warning(NULL, "warning", "No Money!");

                        dialabel->setText(QString("%1").arg(diamond));
                      });

                }

                 dialabel->setText(QString("%1").arg(diamond));
        });
    }
}
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
   painter.setRenderHint(QPainter::Antialiasing);    //设置抗锯齿
    pix.load(":/res/BGScene/S04.jpg");//背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    for (auto moni : EnemyVec)//画出怪物
   { painter.drawPixmap(moni->GetX(), moni->GetY(), moni->GetWidth(), moni->GetHeight(), QPixmap(moni->GetImgPath()));
        if(moni->GetId()!=4)
        {
                leftEnemy++;
        rect = QRect(moni->GetX()+17, moni->GetY()-10, 30, 10);
        textRect = QRect(moni->GetX()+17, moni->GetY()-10, 30, 10);
        buttomMap = QPixmap(":/res/Monster/radius_back.png");
        fillMap = QPixmap(":/res/Monster/radius_front.png");
        f = QFont("Microsoft YaHei", 10, QFont::Bold);
        //画进度条
        rect.moveTo(moni->GetX()+17, moni->GetY()-10);
        textRect.moveTo(moni->GetX()+17, moni->GetY()-10);
        painter.drawPixmap(rect, buttomMap);
        painter.drawPixmap(fillRect, fillMap);
        //画文字
        painter.setFont(f);
        painter.setPen(QColor("#555555"));
        painter.drawText(textRect, Qt::AlignCenter, valueStr);
        valueStr = QString("%1%").arg(QString::number(100*(moni->GetHealth())/(moni->orihealth)));
    }
}

    for(int i = 0; i < Level1TowerNumber; i++)//画子弹
    {
        if(can[i]->onAttackStatus)
                {
                    can[i]->paintBullet(painter,can[i]->_level);
                    can[i]->onAttackStatus = false;
                }

                if(magic[i]->onAttackStatus)
                {
                    magic[i]->paintBullet(painter,magic[i]->_level);
                    magic[i]->onAttackStatus = false;
                }

    }
}



