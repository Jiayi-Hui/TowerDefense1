#include "magictower.h"

magicTower:: magicTower(int _x,int _y)
{
    built = true;
    locX = _x;
    locY = _y;
    buildCost = magicTowerBuildCost[0];
    attackSpeed = magicTowerAttackSpeed[0];
    attackRange = magicTowerAttackRange[0];
    judgeRect.setWidth(attackRange);
    judgeRect.setHeight(attackRange);
    judgeRect.moveTo(locX - attackRange*0.3 , locY - attackRange*0.4 );

}
int magicTower::updateTower(int level)
{
    attackSpeed = magicTowerAttackSpeed[level];
    attackRange = magicTowerAttackRange[level];
    buildCost = magicTowerBuildCost[level];
    judgeRect.setWidth(attackRange);
    judgeRect.setHeight(attackRange);
    judgeRect.moveTo(locX - attackRange*0.3 , locY - attackRange*0.4 );
    _level=level;
    return level;
}

void magicTower::setDirLoc(int x, int y)
{
    dirX = x;
    dirY = y;
}
void magicTower::shoot(int _dirX, int _dirY)
{
    setDirLoc(_dirX, _dirY);
    onAttackStatus = true;
    bullet.load(":/res/Bullet/bl21.png");
}
void magicTower::paintBullet(QPainter &paint,int level)
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
