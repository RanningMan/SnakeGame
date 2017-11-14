#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QPointer>

class QGraphicsScene;
class QTimer;

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = nullptr);

    void start();

signals:

public slots:
    void spawn();
    void gameOver();

private:
    void restart();

    QPointer<QGraphicsScene> m_scene;
    QPointer<QTimer> m_timer;
};

#endif // GAMECONTROLLER_H
