#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QDebug>
#include<QTimer>
#include<QLabel>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

signals:
  void S1Back();
private:
  int diamond=1000;
  QLabel *dialabel=new QLabel(this);
  int health=10;
  QLabel *hthlabel=new QLabel(this);
  void DrawMapArr(QPainter&);
  void DrawMonster(QPainter&);
};

#endif // PLAYSCENE_H
