#ifndef MAGICTOWER_H
#define MAGICTOWER_H
#include "tower.h"
#include "config.h"
class magicTower:public Tower
{
public:
    magicTower();
    magicTower(int _x,int _y);
    int dirX, dirY;
    int temInterval = 0;
    virtual int updateTower(int level);
    void setDirLoc(int x, int y);
    void shoot(int x, int y);
    void paintBullet(QPainter &paint,int level);
    int _level;
};

#endif // MAGICTOWER_H
