#ifndef CANNON_H
#define CANNON_H
#include "tower.h"
#include "config.h"
class Cannon:public Tower
{
public:
    Cannon();
    Cannon(int _x,int _y);
    int temInterval = 0;
    int dirX, dirY;
    virtual int updateTower(int level);
    void setDirLoc(int x, int y);
    void shoot(int x, int y);
    void paintBullet(QPainter &paint,int level);
    int _level;

};

#endif // CANNON_H
