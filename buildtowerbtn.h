#ifndef BUILDTOWERBTN_H
#define BUILDTOWERBTN_H
#include <QPushButton>
#include <QPropertyAnimation>
#include<QMouseEvent>
#include "config.h"
#include<QDebug>


class buildTowerBtn:public QPushButton
{
public:
    buildTowerBtn();
    void setLoc(int _x ,int _y);
    int getTowerType() { return towerType; }
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private:
    int x, y;
    int towerType = 0;
    int towerChoice = 0;

};

#endif // BUILDTOWERBTN_H
