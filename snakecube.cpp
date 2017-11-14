#include "snakecube.h"

#include <QkeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPointer>
#include <QList>

#include "food.h"

extern int unit_size;
extern int window_height;
extern int window_width;

SnakeCube::SnakeCube()
    : m_movingDirection(Direction::RIGHT),
      m_state(SnakeCubeState::HEAD),
      m_foodEatenPosition(QPointF(-1, -1)),
      m_prevPos(QPointF(-1, -1))
{
    setRect(0, 0, unit_size, unit_size);
}

SnakeCube::SnakeCube(int x, int y)
{
    setRect(x, y, unit_size, unit_size);
}

void SnakeCube::turnUp()
{
    if(m_state == SnakeCubeState::HEAD)
    {
        if(m_movingDirection == Direction::LEFT || m_movingDirection == Direction::RIGHT)
        {
            m_movingDirection = Direction::UP;
        }
    }
}

void SnakeCube::turnDown()
{
    if(m_state == SnakeCubeState::HEAD)
    {
        if(m_movingDirection == Direction::LEFT || m_movingDirection == Direction::RIGHT)
        {
            m_movingDirection = Direction::DOWN;
        }
    }
}

void SnakeCube::turnRight()
{
    if(m_state == SnakeCubeState::HEAD)
    {
        if(m_movingDirection == Direction::UP || m_movingDirection == Direction::DOWN)
        {
            m_movingDirection = Direction::RIGHT;
        }
    }
}

void SnakeCube::turnLeft()
{
    if(m_state == SnakeCubeState::HEAD)
    {
        if(m_movingDirection == Direction::UP || m_movingDirection == Direction::DOWN)
        {
            m_movingDirection = Direction::LEFT;
        }
    }
}

void SnakeCube::move()
{
    setPrevPos(pos());
    if(m_state == SnakeCubeState::HEAD)
    {
        switch (m_movingDirection)
        {
            case Direction::UP:
                setPos(x(), y() - unit_size);
                if(y() < 0)
                    setPos(x(), window_height - unit_size);
                break;
            case Direction::DOWN:
                setPos(x(), y() + unit_size);
                if(y() > window_height)
                    setPos(x(), 0);
                break;
            case Direction::RIGHT:
                setPos(x() + unit_size, y());
                if(x() > window_width)
                    setPos(0, y());
                break;
            case Direction::LEFT:
                setPos(x() - unit_size, y());
                if(x() < 0)
                    setPos(window_width - unit_size, y());
                break;
            default:
                break;
        }
    }
    else
    {
        setPos(m_previousCube->getPrevPos());
    }
}

bool SnakeCube::handleTailCollision()
{
    QList<QGraphicsItem*> colliding_items = collidingItems(Qt::ContainsItemBoundingRect);
    for(const auto& item : colliding_items)
    {
        if(typeid(*item) == typeid(Food))
        {
            m_foodEatenPosition.setX(item->x());
            m_foodEatenPosition.setY(item->y());
            if(m_state == SnakeCubeState::TAIL)
                m_state = SnakeCubeState::BODY;
            scene()->removeItem(item);
            delete item;
            return true;
        }
    }
    return false;
}

bool SnakeCube::handleHeadCollision()
{
    QList<QGraphicsItem*> colliding_items = collidingItems(Qt::ContainsItemBoundingRect);
    for(const auto& item : colliding_items)
    {
        if(typeid(*item) == typeid(SnakeCube))
        {
            return false;
        }
    }
    return true;
}

bool SnakeCube::handleBodyCollision()
{
    return true;
}

void SnakeCube::clearFoodPosition()
{
    m_foodEatenPosition = QPointF();
}

QPointF SnakeCube::getPrevPos() const
{
    return m_prevPos;
}

void SnakeCube::setPrevPos(const QPointF &prevPos)
{
    m_prevPos = prevPos;
}

QPointer<SnakeCube> SnakeCube::getPreviousCube() const
{
    return m_previousCube;
}

void SnakeCube::setPreviousCube(const QPointer<SnakeCube> cube)
{
    m_previousCube = cube;
}

SnakeCubeState SnakeCube::getState() const
{
    return m_state;
}

void SnakeCube::setState(const SnakeCubeState &state)
{
    m_state = state;
}

Direction SnakeCube::getMovingDirection() const
{
    return m_movingDirection;
}

void SnakeCube::setMovingDirection(const Direction &movingDirection)
{
    m_movingDirection = movingDirection;
}

QPointF SnakeCube::getFoodEatenPosition() const
{
    return m_foodEatenPosition;
}

void SnakeCube::setFoodEatenPosition(const QPointF &foodEatenPosition)
{
    m_foodEatenPosition = foodEatenPosition;
}
