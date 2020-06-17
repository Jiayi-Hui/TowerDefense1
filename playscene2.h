#ifndef PLAYSCENE2_H
#define PLAYSCENE2_H

#include <QMainWindow>
#include<QDebug>
#include<QTimer>

class playscene2 : public QMainWindow
{
    Q_OBJECT
public:
    explicit playscene2(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:
  void S2Back();
};

#endif // PLAYSCENE2_H
