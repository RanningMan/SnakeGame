#include "snake.h"

#include <QkeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPointer>

#include "food.h"
#include "snakecube.h"

extern int unit_size;

Snake::Snake()
{
    QPointer<SnakeCube> cube = new SnakeCube();
    addToGroup(cube);
    m_snakeCubes.push_back(cube);
}

void Snake::keyPressEvent(QKeyEvent* e)
{
    for(auto cube : m_snakeCubes)
    {
        switch (e->key())
        {
            case Qt::Key_Up:
                cube->turnUp();
                break;
            case Qt::Key_Down:
                cube->turnDown();
                break;
            case Qt::Key_Left:
                cube->turnLeft();
                break;
            case Qt::Key_Right:
                cube->turnRight();
                break;
            default:
                break;
        }
    }
}

void Snake::grow(QPointF pos, Direction direction)
{
    QPointer<SnakeCube> cube = new SnakeCube();
    addToGroup(cube);
    cube->setState(SnakeCubeState::TAIL);
    cube->setMovingDirection(direction);
    cube->setPreviousCube(m_snakeCubes.back());
    m_snakeCubes.push_back(cube);
    if(!pos.isNull())
    {
        cube->setPos(pos.x(), pos.y());
        cube->clearFoodPosition();
    }
    else
    {
        qDebug() << "Invalid food position";
    }
}

void Snake::move()
{
    for(auto cube : m_snakeCubes)
    {
        cube->move();
        if(cube->getState() == SnakeCubeState::HEAD)
        {
            if(!cube->handleHeadCollision())
            {
                biteSelf();
            }
        }
        if(cube->getState() == SnakeCubeState::TAIL || cube->getState() == SnakeCubeState::HEAD && m_snakeCubes.size() == 1)
        {
            if(cube->handleTailCollision())
            {
                grow(cube->getFoodEatenPosition(), cube->getMovingDirection());
                if(cube->getState() == SnakeCubeState::TAIL)
                {
                    cube->setState(SnakeCubeState::BODY);
                }
                spawnFood();
            }
        }
    }
}
