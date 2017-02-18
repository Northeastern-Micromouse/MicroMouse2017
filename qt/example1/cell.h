#ifndef CELL_H
#define CELL_H
#include <QGraphicsScene>

const int cs = 40;

class Cell
{
private:
    bool left;
    bool right;
    bool up;
    bool down;

    int x;
    int y;
public:
    QGraphicsScene& drawCell(QGraphicsScene& scene);
    Cell();
    Cell(bool l, bool r, bool u, bool d, int x, int y);
};

#endif // CELL_H
