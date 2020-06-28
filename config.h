#ifndef CONFIG_H
#define CONFIG_H
#include <QString>


//TowerChooseLoc
const int cannonStart_X = 0;
const int cannonEnd_X = 60;
const int cannonStart_Y = 0;
const int cannonEnd_Y = 60;
const int magicStart_X = 60;
const int magicEnd_X = 120;
const int magicStart_Y = 0;
const int magicEnd_Y = 60;

//Level1 Information
const int Level1TowerNumber = 7;
const int Level1Loc_X[Level1TowerNumber] = {110,300,230, 400, 500, 370, 530};
const int Level1Loc_Y[Level1TowerNumber] = {290,215, 410, 80, 330, 400, 450};



//Level2 Information
const int Level2TowerNumber = 10;
const int Level2Loc_X[Level2TowerNumber] = {90,200, 200, 330, 470, 570, 450,700, 600, 450};
const int Level2Loc_Y[Level2TowerNumber] = {300,450, 210, 200, 330, 200, 150, 300, 500, 650};

//Cannon Level Information
const int cannonAttackRange[4] = {0,200,250,300};
const int cannonAttackSpeed[4] = {10,40,50,70};
const int cannonBuildCost[4] = {0,70,90,110};


//MagicTower Level Information
const int magicTowerAttackRange[4] = {0, 250, 300, 350 };
const int magicTowerAttackSpeed[4] = {10, 50, 60, 70};
const int magicTowerBuildCost[4] = {0, 100, 180, 280};


//坐标结构
struct CoorStr
{
    int x;
    int y;

    CoorStr(int x1, int y1) : x(x1), y(y1) {}
};



#endif // CONFIG_H
