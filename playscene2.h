#ifndef PLAYSCENE2_H
#define PLAYSCENE2_H

#include <QMainWindow>
#include <QMessageBox>
#include<QDebug>
#include<QTimer>
#include<QLabel>
#include<QMouseEvent>
#include <QProgressBar>
#include "tower.h"
#include "enemy.h"
#include "buildbutton.h"

class playscene2 : public QMainWindow
{
    Q_OBJECT
public:
    explicit playscene2(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    QVector<Enemy*> EnemyVec;         //怪物数组
     QVector<Tower*> DefeTowerVec; //重要防御塔父类数组
     void ProdEnemy(CoorStr**, int);
     int counter = 0;    //用于产生怪物的计数器
     BuildButton *locBtn[Level2TowerNumber];
     buildTowerBtn *btb[Level2TowerNumber];
     Cannon *can[Level2TowerNumber];
     magicTower *magic[Level2TowerNumber];
     void initialLocBtnAndTower();
     void setButtons();
     void setLabels();
     void BuildTower();
     void setEndScene();
     void showEndScene();
     void setWave();

signals:
  void S2Back();
private:
  int diamond=800;
  QLabel *dialabel=new QLabel(this);
  int health=30;
  QLabel *hthlabel=new QLabel(this);
  int leftwave=7;
  QLabel *wavlabel=new QLabel(this);
  QLabel *winLabel = new QLabel;
  QPixmap temPix1;
  QPixmap temPix2;
  QPixmap buttomMap;
  QPixmap fillMap;
  QRect rect;
  QRect fillRect;
  QRect textRect;
  QString valueStr;
  QFont f;
  double k;
  int x;
  bool Over=false;
  int leftEnemy=0;
};

#endif // PLAYSCENE2_H
