#include "buildbutton.h"

BuildButton::BuildButton()
{
    this->normalImgPath = ":/res/Button/Build1.png";
    QPixmap pix;
    pix.load(normalImgPath);
    this->setFixedSize( pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));
}
void BuildButton::setLoc(int _x, int _y)
{
    x = _x;
    y = _y;
}
void BuildButton::changeStatusInto(QString changeImg)
{
    normalImgPath = changeImg;
}
void BuildButton::mousePressEvent(QMouseEvent *ev)
{
    pix.load(normalImgPath);
    this->setFixedSize( pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));

    if(ev->button() == Qt::LeftButton)
    {

        if(levelStatus == 0||levelStatus > 3)
        {
            return QPushButton::mousePressEvent(ev);
        }

        if(towerChoice == 1)
        {
            cn->updateTower(levelStatus);
            QString str = QString(":/res/Tower/tw1%1.png").arg(levelStatus);
            changeStatusInto(str);
        }

        else if(towerChoice == 2)
        {
            ma->updateTower(levelStatus);
            QString str = QString(":/res/Tower/tw2%1.png").arg(levelStatus);
            changeStatusInto(str);
        }
        levelStatus ++;
        return QPushButton::mousePressEvent(ev);
    }

    else if(ev->button() == Qt::RightButton)
    {
        levelStatus = 0;

        if(towerChoice == 1)
        {

            cn->updateTower(levelStatus);
        }

        else if(towerChoice == 2)
        {

            ma->updateTower(levelStatus);
        }

        towerChoice = 0;

        normalImgPath = ":/res/Button/Build1.png";
        return QPushButton::mousePressEvent(ev);
    }

    return QPushButton::mousePressEvent(ev);
}
void BuildButton::mouseReleaseEvent(QMouseEvent *ev)
{
    pix.load(normalImgPath);
    this->setFixedSize( pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));
    return QPushButton::mouseReleaseEvent(ev);
}
void BuildButton::getTowerCannon(Cannon *_ar, int _towerChoice)
{
    towerChoice = _towerChoice;
    cn = _ar;
    levelStatus =1;
    cn->updateTower(levelStatus);
    changeStatusInto(":/res/Tower/tw11.png");

}
void BuildButton::getTowerMagic(magicTower *_ma, int _towerChoice)
{
    towerChoice = _towerChoice;
    ma =_ma;
    levelStatus  =1;
    ma->updateTower(levelStatus);
    changeStatusInto(":/res/Tower/tw21.png");
}
