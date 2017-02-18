#include "cell.h"

Cell::Cell(bool l, bool r, bool u, bool d, int x, int y) {
    this->left = l;
    this->right = r;
    this->up = u;
    this->down = d;
    this->x = x;
    this->y = y;
}

Cell::Cell() {
}

QGraphicsScene& Cell::drawCell(QGraphicsScene& scene){
    if (up) {
        scene.addLine(x * cs, y * cs, x * cs + cs, y * cs);
    }

    if (left) {
        scene.addLine(x * cs, y * cs, x * cs, y * cs + cs);
    }

    return scene;
}
