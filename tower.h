#ifndef TOWER_H
#define TOWER_H

#include <QPixmap>
#include <QPainter>
#include <QRect>

class Tower
{
public:

    int getX() { return locY; }
    int getY() { return locX; }
    virtual int updateTower(int level)=0;
    int attackRange;
    int attackSpeed;
    int buildCost;
    bool built = false;
    bool onAttackStatus = false;
    int locX, locY;
    QPixmap bullet;
    QRect judgeRect;

private:
     QPixmap towerImg;

signals:

};

#endif // TOWER_H
