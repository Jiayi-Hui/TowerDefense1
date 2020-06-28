#include "cannon.h"

Cannon::Cannon(int _x,int _y)
{
    built = true;
    locX = _x;
    locY = _y;
     buildCost = cannonBuildCost[0];
     attackSpeed = cannonAttackSpeed[0];
     attackRange = cannonAttackRange[0];
     judgeRect.setWidth(attackRange);
     judgeRect.setHeight(attackRange);
     judgeRect.moveTo(locX - attackRange*0.3 , locY - attackRange*0.4);

}
void Cannon::setDirLoc(int x, int y)
{
    dirX = x;
    dirY = y;
}
int Cannon::updateTower(int level)
{
    attackSpeed = cannonAttackSpeed[level];
    attackRange = cannonAttackRange[level];
    buildCost = cannonBuildCost[level];
    judgeRect.setWidth(attackRange);
    judgeRect.setHeight(attackRange);
    judgeRect.moveTo(locX - attackRange*0.3 , locY - attackRange*0.4);
    _level=level;
    return level;
}

void Cannon::shoot(int _dirX, int _dirY)
{
    setDirLoc(_dirX, _dirY);
    onAttackStatus = true;
    bullet.load(":/res/Bullet/bl1.png");
}

void Cannon::paintBullet(QPainter &paint,int level)
{
    switch(level)
    {
    case 0:
    {   int perStepX1 = (dirX - locX)/3;
        int perStepY1= (dirY - locY)/3;
         for(int i = 0; i < 3; i ++)
        paint.drawPixmap(locX + perStepX1 * (i+1), locY + perStepY1*(i + 1), bullet.width(), bullet.height(), bullet);
        break;}
    case 1:
       { int perStepX2 = (dirX - locX)/6;
        int perStepY2 = (dirY - locY)/6;
        for(int i = 0; i < 4; i ++)
            paint.drawPixmap(locX + perStepX2 * (i+1), locY + perStepY2*(i + 1), bullet.width(), bullet.height(), bullet);}
    }
}
