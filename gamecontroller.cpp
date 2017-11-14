#include "gamecontroller.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointer>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QProcess>
#include <stdlib.h>
#include <iostream>

#include "snake.h"
#include "food.h"

extern int unit_size;

GameController::GameController(QObject *parent) : QObject(parent) {}

void GameController::start()
{
    m_scene = new QGraphicsScene();
    QPointer<QGraphicsView> view = new QGraphicsView(m_scene);

    m_scene->setSceneRect(0, 0, 800, 600);
    view->setFixedSize(800, 600);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // TODO: USE SINGLETON
    QPointer<Snake> snake = new Snake();
    m_scene->addItem(snake);
    snake->setFlag(QGraphicsItem::ItemIsFocusable);
    snake->setFocus();

    m_timer = new QTimer();
    m_timer->start(300);
    connect(m_timer, SIGNAL(timeout()), snake, SLOT(move()));

    QPointer<Food> food = new Food();
    m_scene->addItem(food);
    food->setPos(m_scene->width() / 2, m_scene->height() / 2);

    connect(snake, SIGNAL(spawnFood()), this, SLOT(spawn()));
    connect(snake, SIGNAL(biteSelf()), this, SLOT(gameOver()));

    view->show();
}

void GameController::spawn()
{
    QPointer<Food> food = new Food();
    m_scene->addItem(food);
    int x = (rand() % (700 / unit_size)) * unit_size;
    int y = (rand() % (500 / unit_size)) * unit_size;
    food->setPos(x, y);
}

void GameController::gameOver()
{
    m_timer->stop();
    QMessageBox msgBox;
    msgBox.setText("Game Over!");
    msgBox.setInformativeText("Restart?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Ok:
            restart();
            break;
        case QMessageBox::Close:
            QApplication::quit();
            break;
        default:
            break;
    }
}

void GameController::restart()
{
    QPointer<QProcess> process = new QProcess();
    process->startDetached("SnakeGame", QStringList());
    QApplication::quit();
}
