#ifndef PLAYSCENE_H
#define PLAYSCENE_H

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
#include "mypushbutton.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
   QVector<Enemy*> EnemyVec;         //怪物数组
    QVector<Tower*> DefeTowerVec; //重要防御塔父类数组
    void paintEvent(QPaintEvent *);
    void ProdEnemy(CoorStr**, int);
    BuildButton *locBtn[Level1TowerNumber];
    buildTowerBtn *btb[Level1TowerNumber];
    Cannon *can[Level1TowerNumber];
    magicTower *magic[Level1TowerNumber];
    void setButtons();
    void setLabels();
    void initialLocBtnAndTower();
    void BuildTower();


signals:
  void S1Back();

private:
  int diamond=1200;
  QLabel *dialabel=new QLabel(this);
  int health=12;
  QLabel *hthlabel=new QLabel(this);
  int leftwave=4;
  QLabel *wavlabel=new QLabel(this);
  QLabel *winLabel = new QLabel;
  QLabel *loseLabel = new QLabel;
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
  int counter = 0;    //用于产生怪物的计数器
  int dead=0;
};

#endif // PLAYSCENE_H
