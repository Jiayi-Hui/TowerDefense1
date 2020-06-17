#ifndef TOWER_H
#define TOWER_H

#include <QObject>

class Tower : public QObject
{
    Q_OBJECT
public:
    explicit Tower(QObject *parent = nullptr);

signals:

};

#endif // TOWER_H
