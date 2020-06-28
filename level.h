#ifndef LEVEL_H
#define LEVEL_H

#include <QMainWindow>
#include<QMenuBar>
#include<QPainter>
#include<QPixmap>
#include<QDebug>
#include<QTimer>

#include "mypushbutton.h"
#include "playscene.h"
#include "playscene2.h"
class Level : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    PlayScene * S1=NULL;
    playscene2 * S2=NULL;

signals:
    void LevelBack();//自定义信号告诉主场景点击了返回

};

#endif // LEVEL_H
