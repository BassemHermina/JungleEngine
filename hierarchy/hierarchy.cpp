#include "hierarchy.hpp"

hierarchy::hierarchy()
{
}

int hierarchy::gameObjectNo = 0;

void hierarchy::test(){

     cout << "testing the Hierarchy class .. " << endl;
}

int hierarchy::init()
    {
       // initialize the data positions of all objects msln

    }

bool hierarchy::add(monobehaviorClass * obj)
    {
        GameObjects[gameObjectNo++]=obj;
    }


void hierarchy::updateGameObjects()
    {
        for(int i=0; i<gameObjectNo; i++){
            GameObjects[i]->update();
        }
    }
