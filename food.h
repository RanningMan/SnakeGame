#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QGraphicsRectItem>

class Food : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Food();

signals:

public slots:

};

#endif // FOOD_H
