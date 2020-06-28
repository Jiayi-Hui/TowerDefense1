#ifndef BUILDBUTTON_H
#define BUILDBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include<QMouseEvent>
#include<QDebug>
#include "buildtowerbtn.h"
#include "config.h"
#include "cannon.h"
#include "magictower.h"
class BuildButton:public QPushButton
{
public:
    BuildButton();
    void setLoc(int _x, int _y);
    int GetLevelStatus(){ return levelStatus; }
    void changeStatusInto(QString changeImg);
    void getTowerCannon(Cannon *_cn, int _towerChoice);
    void getTowerMagic(magicTower *_ma, int _towerChoice);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    int levelStatus = 0;

    //鼠标点击事件函数及其实现

private:
    QPixmap pix;
    QString normalImgPath;
    int x, y;
    Cannon *cn;
    magicTower *ma;
    int towerChoice = 0;
};

#endif // BUILDBUTTON_H
