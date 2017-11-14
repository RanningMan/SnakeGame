#include "food.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>

extern int unit_size;

Food::Food()
{
    setRect(0, 0, unit_size, unit_size);
    setBrush(QBrush((Qt::black)));
}
