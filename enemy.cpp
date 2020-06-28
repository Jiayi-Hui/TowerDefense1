#include "enemy.h"
#include <QPixmap>
#include "config.h"

Enemy::Enemy(CoorStr **pointarr, int arrlength, int x, int y, int fid) :mx(x), my(y), id(fid)
{
    for(int i = 0; i < arrlength; i++)      //将传进来的数组插入到Waypoint动态数组
        Waypoint.push_back(pointarr[i]);

    switch (id)
    {
    case 1://怪物1
        health = 10;   //生命值
        orihealth=10;
        mwidth = 64, mheight = 64;  //宽高
        ImgPath = ":/res/Monster/Bird/5_1_n_b.png";
        break;
    case 2://怪物2
        health = 15;   //生命值
        orihealth=15;
        mwidth = 70, mheight = 70;  //宽高
        ImgPath = ":/res/Monster/Pig/1_1_n_d.png";
        break;
    case 3://怪物3
        health = 20;   //生命值
        orihealth=20;
        mwidth = 70, mheight = 70;  //宽高
        ImgPath = ":/res/Monster/Dragon/1_3_e_m.png";
        break;
    case 4://空白
        health = 15;   //生命值
        orihealth=15;
        mwidth = 70, mheight = 70;  //宽高
        break;
    }
    this->m_Rect.setWidth(mwidth);
    this->m_Rect.setHeight(mheight);
    m_Rect.moveTo(GetX(), GetY());

}
//怪物按设定路径点移动
bool Enemy::Move()
{
    if(Waypoint.empty())
        return true;

    //如果第一个路径点的y小于怪物原本的路径点，则怪物向下走
    if (Waypoint.at(0)->y > my) //下
    {
        my += mspeed;
        return false;
    }

    if (Waypoint.at(0)->x < mx) //左
    {
        mx -= mspeed;
        return false;
    }

    if (Waypoint.at(0)->x > mx) //右
    {
        mx += mspeed;
        return false;
    }

    if (Waypoint.at(0)->y < my) //上
    {
        my -= mspeed;
        return false;
    }

    //如果怪物的坐标和路径点坐标几乎重合，则删除这个路径点
    if (Waypoint.at(0)->y == my && Waypoint.at(0)->x == mx)
    {
        Waypoint.erase(Waypoint.begin());       //从数组中删除
    }
    return false;
}
int Enemy::GetX() const       //获取横坐标
{
    return mx;
}

int Enemy::GetY() const       //获取横坐标
{
    return my;
}

int Enemy::GetWidth() const   //获取宽
{
    return mwidth;
}

int Enemy::GetHeight() const  //获取高
{
    return mheight;
}

QString Enemy::GetImgPath() const //获取图片路径
{
    return ImgPath;
}

int Enemy::GetId() const      //获取编号
{
    return id;
}

int Enemy::GetHealth() const  //获取生命值
{
    return health;
}
void Enemy::updatePosition(){
    m_Rect.moveTo(mx, my);
}

