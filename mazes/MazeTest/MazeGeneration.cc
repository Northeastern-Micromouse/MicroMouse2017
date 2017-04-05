#include<iostream>
#include<cstdlib>
#include<stack>
#include<ctime>
#include <fstream>

namespace MazeGen
{
    const unsigned int NORTH=0;
    const unsigned int SOUTH=1;
    const unsigned int EAST=2;
    const unsigned int WEST=3;
    const unsigned int COLUMN=33;
    const unsigned int ROW=33;


    int nGood = 0; //Initialize nGood; nGood holds # of good moves
    int locX = 1, locY = 1;

    void printGrid(char grid[ROW][COLUMN])
    {
        
        //Only want to print final grid
        system("clear"); // system("cls") in Conio.h on Windows
        for (int i = 0; i < ROW; i++)
        {       
            for(int j = 0; j < COLUMN; j++)
            {
               std::cout << grid[i][j]<< ' ';       
            }
        std::cout << std::endl;
        }
        std::cout<<"-----------------------------------"<<std::endl;
    }

    /*
    Output Maze to textfile
    */
    void KeepMaze(char grid[ROW][COLUMN])
    {
        std::ofstream myfile;
        myfile.open("maze.txt");
        for (int i = 0; i < ROW; i++)
        {
            for(int j = 0; j < COLUMN; j++)
            {
                myfile << grid[i][j]<<' '; // no space
            } 
            
            myfile<<std::endl;
        }
    }

    int moveEW(int direction, int x){
        if (direction == EAST)
        {
            //cout << "moving east" << endl;
                return x + 1;
        }
        else if (direction == WEST)
        {
            //cout << "moving west" << endl;
                return x - 1;
        }
        else
                return x;
    }

    int moveNS(int direction, int y){
        if (direction == NORTH)
        {
            //cout << "moving north" << endl;
                return y - 1;
        }   
        else if (direction == SOUTH)
        {
            //cout << "moving south" << endl;
                return y + 1;
        }
        else
                return y;
    }

    bool isGood(int x, int y, int direction, char grid[ROW][COLUMN])
    {
        x = moveEW(direction,x);
        y = moveNS(direction,y);
        x = moveEW(direction,x);
        y = moveNS(direction,y);

        if (grid[y][x] == ' ' || x >= (COLUMN - 1) || x <= 0 || y <= 0 || y >= (ROW - 1))
        {
            return false;
        }

        if (grid[y][x] != ' ')
        {
            return true;
        }

        return false;
    }

    main(){
    char grid[ROW][COLUMN];

    // initialize grid
    for (int i = 0; i < ROW; i++){
                for(int j = 0; j < COLUMN; j++){
                        grid[i][j] = '#';
                }
        }
      
      grid[1][1]=' ';
      
      //Set the center of the maze
      int x_center = (((COLUMN-1)/2)-1);
      int y_center = (((ROW-1)/2)-1);
      grid[x_center][y_center] = ' ';
      grid[x_center+1][y_center]=' ';
      grid[x_center][y_center+1]=' ';
      grid[x_center+2][y_center] = ' ';
      grid[x_center][y_center+2] = ' ';
      grid[x_center+1][y_center+1] = ' ';
      grid[x_center+1][y_center+2] = ' ';
      grid[x_center+2][y_center+1] = ' ';
      grid[x_center+2][y_center+2] = ' ';
      grid[x_center+3][y_center+2] = ' ';


    //initialize srand with seed
    srand(time(0));

    //init stacks for xy coords
    std::stack<int> xValues;
    std::stack<int> yValues;

    nGood = 0;
    int direction = 0;

    do{
        //find ngood moves
        for (int i = 0; i < 4; i++)
        {
            if(isGood(locX,locY,i,grid))
            {
                nGood++;
            }
        }

        // if only 1 good move, move there
        
        if (nGood == 1){
            if (isGood(locX,locY,NORTH,grid))
            {
                locY = moveNS(NORTH,locY);
                grid[locY][locX] = ' ';
                locY = moveNS(NORTH,locY);
            }
            else if (isGood(locX,locY,SOUTH,grid))
            {
                    locY = moveNS(SOUTH,locY);
                    grid[locY][locX] = ' ';
                    locY = moveNS(SOUTH,locY);
            }
            else if (isGood(locX,locY,EAST,grid))
            {
                     locX = moveEW(EAST,locX);
                     grid[locY][locX] = ' ';
                     locX = moveEW(EAST,locX);
            }
                        else if (isGood(locX,locY,WEST,grid))
                        {
                                locX = moveEW(WEST,locX);
                                grid[locY][locX] = ' ';
                                locX = moveEW(WEST,locX);
                        }
                            
            grid[locY][locX] = ' ';
        }

        // if no good moves, move back in stack
        else if (nGood == 0){
            locX = xValues.top();
            locY = yValues.top();
            xValues.pop();
            yValues.pop();
            //cout<<"backtracking"<<endl;
        }

        //if more than 1 good move, push stack
        else if (nGood > 1){
            xValues.push(locX);
            yValues.push(locY);

            //Here the direction to move is randomly chosen
            do{
                direction = rand() % 4;
            }while (!isGood(locX,locY,direction,grid));
            

            locX = moveEW(direction,locX);
            locY = moveNS(direction,locY);
            grid[locY][locX] = ' ';
            
            locX = moveEW(direction,locX);
            locY = moveNS(direction,locY);
        
        }

        int locx_2;
        int locy_2;
        
        // set grid
        grid[locY][locX] = ' ';
      
        //reset nGood value
                nGood = 0;

    }while(!xValues.empty());

    // Create Loops
    for (int i = 0; i < 30; i++) //10
    {
        int x = rand() % 16;
        int y = rand() % 16;

        if (x == 7 | x == 8 | x == 9)
        {
            if (y != 7 && y != 8 && y != 9 && y!=0)
            {
                grid[2*x][2*y+1] = ' ';
            }
        }
        else if(x!=0 && y!=0)
        {
            grid[2*x][2*y+1] = ' ';
        }
    }
    //Print final maze
    printGrid(grid);

    //Output final maze to textfile
    KeepMaze(grid);
    }
}
