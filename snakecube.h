#ifndef SNAKECUBE_H
#define SNAKECUBE_H

#include <QGraphicsRectItem>
#include <QPointer>

enum SnakeCubeState
{
    HEAD, TAIL, BODY
};

enum Direction
{
    RIGHT, LEFT, UP, DOWN
};

class SnakeCube : public QGraphicsRectItem, public QObject
{
public:
    SnakeCube();
    SnakeCube(int x, int y);
    void turnUp();
    void turnDown();
    void turnRight();
    void turnLeft();
    void move();
    bool handleTailCollision();
    bool handleHeadCollision();
    bool handleBodyCollision();

    QPointer<SnakeCube> getPreviousCube() const;
    void setPreviousCube(const QPointer<SnakeCube> cube);

    SnakeCubeState getState() const;
    void setState(const SnakeCubeState &state);

    Direction getMovingDirection() const;
    void setMovingDirection(const Direction &movingDirection);

    QPointF getFoodEatenPosition() const;
    void setFoodEatenPosition(const QPointF &foodEatenPosition);
    void clearFoodPosition();

    QPointF getPrevPos() const;
    void setPrevPos(const QPointF &prevPos);

private:
    SnakeCubeState m_state;
    Direction m_movingDirection;
    QPointF m_foodEatenPosition;
    QPointer<SnakeCube> m_previousCube;
    QPointF m_prevPos;
};

#endif // SNAKECUBE_H
