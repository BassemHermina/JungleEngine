#include "Maze.hpp"
Maze::Maze()
{
    string obj,txt;
    double x,y,z;
    ifstream file;
    file.open("test.bisho");
    int i=0;
    while(!file.eof())
    {
        file>>obj;
        file>>txt;
        file>>x;
        file>>y;
        file>>z;
        maze[i]=new Parts(obj,txt,-x,y,z);
        mazeBboxes[i] = new Bounding_box (maze[i]);
        i++;
    }
    file.close();

}

void Maze::drawPhong()
{
    for (int i=0;i<61;i++)
    {
        maze[i]->drawPhong();
        if (i!=0)
        mazeBboxes[i]->draw2();
    }
}

void Maze::drawDepthMap()
{
    for(int i=0;i<61;i++)
    {
        maze[i]->drawDepthMap();
    }
}
