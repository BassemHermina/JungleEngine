#ifndef MAZE_H
#define MAZE_H
#include"Maze/Parts.hpp"
#include <fstream>
#include "Physx/BoundingBox.hpp"


class Maze
{



public:

    //Bassem NEW
    Parts* maze[61];
    Bounding_box *mazeBboxes[61];
    Maze();
    void drawPhong();
    void drawDepthMap();

};


#endif // Maze_H
