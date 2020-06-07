#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Mainscene; }
QT_END_NAMESPACE

class Mainscene : public QMainWindow
{
    Q_OBJECT

public:
    Mainscene(QWidget *parent = nullptr);
    ~Mainscene();

    //画背景图
    void paintEvent(QPaintEvent *);
private:
    Ui::Mainscene *ui;
};
#endif // MAINSCENE_H
