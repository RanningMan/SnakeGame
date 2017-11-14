#include <QApplication>
#include <QPointer>

#include "gamecontroller.h"

int unit_size = 50;
int window_height = 600;
int window_width = 800;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // TODO: Use singleton
    QPointer<GameController> game = new GameController();
    game->start();

    return a.exec();
}
