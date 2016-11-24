#include "hierarchy.hpp"

#include "Objects/plane.hpp"
#include "Objects/Shell.hpp"
#include "Objects/Suzanne.hpp"

hierarchy::hierarchy()
{
    GameObjects=new monobehaviorClass*[100];
}

int hierarchy::gameObjectNo = 0;

void hierarchy::test(){

     cout << "testing the Hierarchy class .. " << endl;
}

int hierarchy::init()
    {
       // initialize the data positions of all objects msln

    GameObjects[1]->Translate(6.0f, 0.0f, 0.0f);
    GameObjects[1]->Rotate(0.0f, 0.0f, 90.0f);
    GameObjects[1]->Scale(1.0f, 1.0f, 1.0f);

    GameObjects[2]->Translate(-20.0f, 5.0f, 0.0f);
    GameObjects[2]->Rotate(0.0f, 0.0f, 45.0f);
    GameObjects[2]->Scale(1.0f, 1.0f, 1.0f);

    GameObjects[7]->Translate(0.0f, 0.0f, 0.0f);
    GameObjects[7]->Rotate(0.0f, 0.0f, 0.0f);
    GameObjects[7]->Scale(10.0f, 0.4f, 6.0f);

    GameObjects[2]->Translate(6.0f, 3.0f, 10.0f);
    GameObjects[2]->Rotate(0.0f, -45.0f, 0.0f);
    GameObjects[2]->Scale(1.0f, 1.0f, 1.0f);

    GameObjects[3]->Translate(6.0f, -4.0f, 0.0f);
    GameObjects[3]->Rotate(0.0f, 0.0f, 45.0f);
    GameObjects[3]->Scale(1.0f, 1.0f, 1.0f);


    GameObjects[4]->Translate(6.0f, 4.0f,2.0f);
    GameObjects[4]->Rotate(0.0f, -45.0f, 0.0f);
    GameObjects[4]->Scale(1.0f, 1.0f, 1.0f);


    GameObjects[5]->Translate(6.0f, 0.0f, 9.0f);
    GameObjects[5]->Rotate(0.0f, -270.0f, 45.0f);
    GameObjects[5]->Scale(1.0f, 1.0f, 1.0f);


    GameObjects[6]->Translate(-3.0f, 2.0f, 0.0f);
    GameObjects[6]->Rotate(0.0f, 0.0f, 90.0f);
    GameObjects[6]->Scale(1.0f, 1.0f, 1.0f);


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

void hierarchy::drawPhong()
{
    for(int i=0; i<gameObjectNo; i++){
            GameObjects[i]->drawPhong();
    }
}

void hierarchy::drawDepthMap()
{
    for(int i=0; i<gameObjectNo; i++){
            GameObjects[i]->drawDepthMap();
    }
}
