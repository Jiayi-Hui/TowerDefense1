#include "mypushbutton.h"
MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
        if(!ret)
        {
            qDebug() << "load error!";
            return;
        }

    //设置图片大小
    this->setFixedSize(pix.width(),pix.height());
    //设置图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标及其大小
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));


}
void MyPushButton::BounceUp()
{
    //创建动画对象
        QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    //设置时间间隔，单位为ms
            animation1->setDuration(200);
    //设置起始位置
            animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //创建结束位置
            animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线， QEasingCurve::OutBounce为弹跳效果
            animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
            animation1->start();
}

void MyPushButton::BounceDown()
{

QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");

    animation1->setDuration(200);

    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    animation1->setEasingCurve(QEasingCurve::OutBounce);

    animation1->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *ev)
{
        if(this->pressImgPath != "")
        {
            QPixmap pix;
            pix.load(this->pressImgPath);
            this->setFixedSize(pix.width(),pix.height());
            this->setStyleSheet("QPushButton{border:0px}");
            this->setIcon(pix);
            this->setIconSize(QSize(pix.width(),pix.height()));
        }

        return QPushButton::mousePressEvent(ev);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *ev)
{
    if(this->pressImgPath != "")
    {
        QPixmap pix;
        pix.load(this->normalImgPath);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //让父类执行其他内容
        return QPushButton::mouseReleaseEvent(ev);
}
