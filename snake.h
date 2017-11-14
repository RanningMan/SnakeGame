#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QList>

class QKeyEvent;
class SnakeCube;
enum Direction;

class Snake : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
     Snake();
     void keyPressEvent(QKeyEvent* e);

signals:
    void spawnFood();
    void biteSelf();

public slots:
    void move();

private:
    void grow(QPointF pos, Direction direction);

    QList<QPointer<SnakeCube>> m_snakeCubes;
};

#endif // SNAKE_H
