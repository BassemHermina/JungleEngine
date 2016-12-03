#ifndef MAZE_H
#define MAZE_H
#include"Maze/Parts.hpp"
#include <fstream>


class Maze
{

     Parts* maze[61];

public:

    Maze();
    void drawPhong();
    void drawDepthMap();

};


#endif // Maze_H
