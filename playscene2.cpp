#include "mypushbutton.h"
#include "playscene2.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QSound>

playscene2::playscene2(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(900,700);
    this->setWindowTitle("Play Scene 2");
    initialLocBtnAndTower();
    setButtons();
    setLabels();
    BuildTower();
    QSound* BGM=new QSound("qrc:/res/BackgroundMusic/BGM02.wav");

    //返回按钮
        MyPushButton *BackBtn = new MyPushButton(":/res/Button/Back.png");
        BackBtn->setParent(this);
        BackBtn->move(0.9*(this->width()-BackBtn->width()), 50);
      //点击返回
        connect(BackBtn, &MyPushButton::clicked,[=](){
            qDebug() << "BackBtn clicked";
            BackBtn->BounceDown();
            BackBtn->BounceUp();
             BGM->stop();
            QTimer::singleShot(200, this, [=](){
                emit this->S2Back();
            });

        });

        QTimer* timer = new QTimer(this);      //用于插入怪物定时器
        timer->start(1000);
         connect(timer,&QTimer::timeout,[=]()
           {
                   //设置路径点
            CoorStr* Waypointarr[] =
           {
            new CoorStr(0,this->height()*0.6), new CoorStr(50,this->height()*0.6), new CoorStr(120,this->height()*0.6),new CoorStr(120,this->height()*0.6-50), new CoorStr(120,this->height()*0.6-150),  new CoorStr(120,this->height()*0.6-250), new CoorStr(120,this->height()*0.6-350),
            new CoorStr(170,this->height()*0.6-350),new CoorStr(260,this->height()*0.6-350),new CoorStr(260,this->height()*0.6-250),new CoorStr(260,this->height()*0.6-150),new CoorStr(360,this->height()*0.6-150),new CoorStr(480,this->height()*0.6-150),new CoorStr(480,this->height()*0.6-250),
                new CoorStr(480,this->height()*0.6-350),new CoorStr(630,this->height()*0.6-350),new CoorStr(630,this->height()*0.6-250),new CoorStr(630,this->height()*0.6-130),new CoorStr(630,this->height()*0.6-20),new CoorStr(520,this->height()*0.6-20),new CoorStr(420,this->height()*0.6-20),
                new CoorStr(420,this->height()*0.6+80),new CoorStr(420,this->height()*0.6+150),new CoorStr(520,this->height()*0.6+150),new CoorStr(640,this->height()*0.6+150)};

            //每条路径的结点个数
            int PathLength = sizeof(Waypointarr)/sizeof(CoorStr*);
            ProdEnemy( Waypointarr,PathLength);
            for (auto Moni = EnemyVec.begin(); Moni != EnemyVec.end(); Moni++)
            (*Moni)->updatePosition();
           });
         QTimer* timer2 = new QTimer(this);

         MyPushButton *startBtn = new MyPushButton(":/res/Button/stt2.png");
         startBtn->setParent(this);
         startBtn->move(10, this->height()*0.61);
         connect(startBtn, &MyPushButton::clicked, [=](){
             timer2->start(100);
             BGM->play();
        connect(timer2,&QTimer::timeout,[=]()
          {
              //怪物移动
              for (auto Moni = EnemyVec.begin(); Moni != EnemyVec.end(); Moni++)

                  if((*Moni)->Move()) //怪物走到终点
                  {
                      delete *Moni;
                      EnemyVec.erase(Moni);    //删除这个怪物
                      if((*Moni)->GetId()==1)
                           health-=2;          //生命数量-1
                      else if((*Moni)->GetId()==2)
                           health-=4;
                      else if((*Moni)->GetId()==3)
                           health-=6;
                      else health-=0;
                      if(health<=2&&health>=0)
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
              update();   //绘图
          });
          });
           QTimer* timer3 = new QTimer(this);
           timer3->start(100);
           connect(timer3,&QTimer::timeout,[=]()
                            {
                              for(int j = 0; j < Level2TowerNumber; j ++)
                                 { can[j]->temInterval += 5;
                                  if(can[j]->temInterval >= can[j]->attackSpeed)
                                     {    for (auto Moni = EnemyVec.begin(); Moni != EnemyVec.end(); Moni++)
                                         {
                                             if(can[j]->judgeRect.intersects((*Moni)->m_Rect) && (*Moni)->isAlive&&(*Moni)->GetId()!=4)
                                             {
                                                 can[j]->shoot((*Moni)->GetX(), (*Moni)->GetY());
                                                 qDebug() << "Attack1！";
                                                 (*Moni)->health -= 3;
                                                 if((*Moni)->health <= 0)
                                                 {
                                                     this->diamond += (*Moni)->orihealth;
                                                     (*Moni)->isAlive = false;
                                                     leftEnemy--;
                                                     delete *Moni;
                                                     EnemyVec.erase(Moni);
                                                     if(counter==74&&leftEnemy==0)
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
                              for(int j = 0; j < Level2TowerNumber; j ++)
                                              {
                                                  magic[j]->temInterval += 5;
                                                  if(magic[j]->temInterval >= magic[j]->attackSpeed)
                                                  {
                                                      for (auto Moni = EnemyVec.begin(); Moni != EnemyVec.end(); Moni++)
                                                            {
                                                         if(magic[j]->judgeRect.intersects((*Moni)->m_Rect) && (*Moni)->isAlive&&(*Moni)->GetId()!=4)
                                                             {
                                                                magic[j]->shoot((*Moni)->GetX(), (*Moni)->GetY());
                                                                 (*Moni)->health -= 4;
                                                                 qDebug() << "Attack2!";

                                                                if((*Moni)->health <= 0)
                                                             {
                                                                 this->diamond += (*Moni)->orihealth;
                                                                (*Moni)->isAlive = false;
                                                                delete *Moni;
                                                                EnemyVec.erase(Moni);
                                                                leftEnemy--;
                                                                if(counter==74&&leftEnemy==0)
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
}
void playscene2::ProdEnemy(CoorStr** Waypointarr, int PathLength){
    if(counter==1)
    { EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,4));
        leftwave=6;
        setWave();}
    else if(counter<= 3)
        EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,1));
     else  if( counter <= 10)
         EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,2));
      else  if( counter <= 14)
          EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,1));
     else if( counter <= 19)
         { EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,4));
         leftwave=5;
        setWave();}
    else if( counter <= 24)
         EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,3));
    else if( counter <= 30)
         {EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,4));
         leftwave=4;
        setWave();}
    else if( counter <= 38)
         EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,1));
    else if( counter <= 45)
    { EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,4));
         leftwave=3;
        setWave();}
    else if( counter <= 50)
         EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,2));
    else if( counter <= 57)
    { EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,4));
         leftwave=2;
        setWave();}
    else if( counter <= 63)
         EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,3));
    else if( counter <= 70)
    { EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,4));
         leftwave=1;
        setWave();}
    else if( counter <= 73)
    { EnemyVec.push_back(new Enemy(Waypointarr,PathLength,Waypointarr[0]->x,Waypointarr[0]->y,3));
        leftwave=0;
        setWave();}
    counter++;          //计数器+1
     update();
}
void playscene2::setWave(){
     wavlabel->setText(QString("%1/6").arg(leftwave));
}
void playscene2::initialLocBtnAndTower()
{
    for(int i = 0; i < Level2TowerNumber; i ++)
    {
        magic[i] = new magicTower(Level2Loc_X[i], Level2Loc_Y[i]);
        can[i] = new Cannon(Level2Loc_X[i], Level2Loc_Y[i]);
        locBtn[i] = new BuildButton();
        locBtn[i]->setParent(this);
        locBtn[i]->move(Level2Loc_X[i], Level2Loc_Y[i]);
        locBtn[i]->setLoc(Level2Loc_X[i], Level2Loc_Y[i]);
        btb[i] = new buildTowerBtn;
        btb[i]->setParent(this);
        btb[i]->move(-200, -200);
    }

}
void playscene2::setButtons(){
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
void playscene2::setLabels(){
    dialabel->move(90, 45);       //位置
    setStyleSheet("color:white");   //设置颜色
    dialabel->setFont(QFont("Arial Unicode MS", 24));             //设置金钱标签属性
    dialabel->setText(QString("%1").arg(diamond));    //显示金钱信息
    hthlabel->move(230,45);   //设置控件位置和大小
    hthlabel->setFont(QFont("Arial Unicode MS", 24));
    hthlabel->setText(QString("%1").arg(health));
    wavlabel->move(80,this->height()-90);
    wavlabel->setFont(QFont("Arial Unicode MS", 24));             //设置金钱标签属性
    wavlabel->setText(QString("%1/6").arg(leftwave));
}
//塔的建造并升级
void playscene2::BuildTower(){
    for(int i = 0; i < Level2TowerNumber; i ++)
    {
        connect(locBtn[i], &BuildButton::clicked, [=](){
                if(locBtn[i]->GetLevelStatus() == 0)
                {
                    btb[i]->move(Level2Loc_X[i]-20, Level2Loc_Y[i]-20);

                    connect(btb[i], &buildTowerBtn::clicked, [=](){
                                                if(btb[i]->getTowerType() == 1 && this->diamond >= can[i]->buildCost)
                                                {

                                                    locBtn[i]->getTowerCannon(can[i], btb[i]->getTowerType());
                                                    btb[i]->move(-200, -200);
                                                     diamond-= can[i]->buildCost;
                                                }

                                                else if(btb[i]->getTowerType() == 2 && this->diamond>= magic[i]->buildCost)
                                                {
                                                    locBtn[i]->getTowerMagic(magic[i], btb[i]->getTowerType());
                                                    btb[i]->move(-200, -200);
                                                     diamond-= magic[i]->buildCost;
                                                }
                                                else   QMessageBox::warning(NULL, "warning", "No Money!");


                                                 dialabel->setText(QString("%1").arg(diamond));
                                                });

                }

                 dialabel->setText(QString("%1").arg(diamond));
        });
    }
}
void playscene2::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/BGScene/S03.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    for (auto moni : EnemyVec)//画出怪物
    painter.drawPixmap(moni->GetX(), moni->GetY(), moni->GetWidth(), moni->GetHeight(), QPixmap(moni->GetImgPath()));
    for(int i = 0; i < Level2TowerNumber; i ++)
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


