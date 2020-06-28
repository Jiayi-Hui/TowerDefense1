#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>
#include<QMouseEvent>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QString normalImg, QString pressImg="");
    //参数1 正常显示图片 参数2 按下后显示图片
    QString normalImgPath;//保存传入的默认实现路径
    QString pressImgPath;//保存按下后显示的图片路径

    void BounceUp();
    void BounceDown();
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

signals:

};

#endif // MYPUSHBUTTON_H
