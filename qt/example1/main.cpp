#include "widget.h"
#include <QApplication>
#include <QLabel>
#include <QGraphicsView>
#include "cell.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

int getCoord(int coordNum)
{
    return (2 * coordNum) + 1;
}

Cell** readMaze(string fileName) {

    Cell** maze = new Cell*[16];

    for (int i = 0; i < 16; i++)
    {
        maze[i] = new Cell[16];
    }

    //create maze
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            maze[y][x] = Cell(true, true, true, true, x, y);
        }
    }

    char mazeString[33][33];

    ifstream imaze;

    imaze.open("C:\\Users\\xlug1\\Documents\\Micromouse\\qt\\example1\\maze.txt");

    for (int l = 0; l < 33; l++) {
        for (int m = 0; m < 33; m++) {
            mazeString[l][m] = imaze.get();
        }
        imaze.get();
    }

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {

            if (mazeString[getCoord(i) + 1][getCoord(j)] != '#') {
                (maze[i][j]).down = false;
            }

            if (mazeString[getCoord(i) - 1][getCoord(j)] != '#') {
                (maze[i][j]).up = false;
            }

            if (mazeString[getCoord(i)][getCoord(j) - 1] != '#') {
                (maze[i][j].left) = false;
            }

            if (mazeString[getCoord(i)][getCoord(j) + 1] != '#') {
                (maze[i][j].right) = false;
            }
        }
    }

    return maze;
}

void drawPath(QGraphicsScene &sc, vector<string> dirs) {
    // TO DO - DRAW ANIMATIONS

    int loc[] = {0, 0};

    sc.addEllipse(cs / 4, cs / 4, cs/2, cs/2, QPen(), QBrush(QColor("#FFCCDD")));

    for (string s : dirs) {
        if (s.compare("East ") == 0) {
            loc[1] = loc[1] + 1;
            sc.addEllipse(cs * loc[1] + cs / 4, cs * loc[0] + cs / 4, cs/2, cs/2, QPen(), QBrush(QColor("#FFCCDD")));
        }

        // FIGURE OUT STARTING POINT. TOP LEFT CORNER OR BOTTOM LEFT????
        else if (s.compare("North ") == 0) {
            loc[0] = loc[0] - 1;
            sc.addEllipse(cs * loc[1] + cs / 4, cs * loc[0] + cs / 4, cs/2, cs/2, QPen(), QBrush(QColor("#FFCCDD")));
        }

        else if (s.compare("West ") == 0) {
            loc[1] = loc[1] - 1;
            sc.addEllipse(cs * loc[1] + cs / 4, cs / 4, cs * loc[0] + cs/2, cs/2, QPen(), QBrush(QColor("#FFCCDD")));
        }

        else if (s.compare("South ") == 0) {
            loc[0] = loc[0] + 1;
            sc.addEllipse(cs * loc[1] + cs / 4, cs * loc[1] + cs / 4,  cs/2, cs/2, QPen(), QBrush(QColor("#FFCCDD")));
        }

        else {
            cout << s;
            cout << "invalid direction given" << endl;
        }
    }
}

vector<string> readDirs(string fileName) {
   vector<string> rd = vector<string>();


   ifstream path;
   path.open("C:\\Users\\xlug1\\Documents\\Micromouse\\qt\\example1\\path_txt.txt");

   string dir;

   while(getline(path, dir)) {
       rd.push_back(string(dir));
   }

   return rd;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene(-1 * cs, -1 * cs, 720, 720);

    Cell** maze = readMaze("Hi");
    vector<string> dirList = readDirs("hi");

    // draw the cell
    for(int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            maze[i][j].drawCell(scene);
        }
    }

    scene.addLine(cs * 16, 0, cs * 16, cs * 16);
    scene.addLine(0, cs * 16, cs * 16, cs * 16);

    drawPath(scene ,dirList);

    //qt stuff
    QGraphicsView view(&scene);

    view.show();

    return a.exec();
}
