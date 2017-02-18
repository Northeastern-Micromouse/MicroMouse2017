#include "widget.h"
#include <QApplication>
#include <QLabel>
#include <QGraphicsView>
#include "cell.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Cell maze[16][16];

    //create maze
    for(int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            maze[x][y] = Cell(true, true, true, true, x, y);
        }
    }

    QGraphicsScene scene(-1 * cs, -1 * cs, 720, 720);

    // draw the cell
    for(int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            maze[i][j].drawCell(scene);
        }
    }

    scene.addLine(cs * 16, 0, cs * 16, cs * 16);
    scene.addLine(0, cs * 16, cs * 16, cs * 16);

    //qt stuff
    QGraphicsView view(&scene);

    view.show();

    return a.exec();
}
