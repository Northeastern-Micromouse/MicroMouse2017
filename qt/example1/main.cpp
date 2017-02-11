#include "widget.h"
#include <QApplication>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    int cs = 40;

    QApplication a(argc, argv);

    QGraphicsScene scene(-1 * cs, -1 * cs, 720, 720);

    for(int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            scene.addLine(i * cs, j * cs, i * cs + cs, j * cs);
            scene.addLine(i * cs, j * cs, i * cs, j * cs + cs);
        }
    }

    scene.addLine(cs * 16, 0, cs * 16, cs * 16);
    scene.addLine(0, cs * 16, cs * 16, cs * 16);

    QGraphicsView view(&scene);

    view.show();

    return a.exec();
}
