#ifndef HIERARCHY_H
#define HIERARCHY_H
#include"monobehavior/monobehavior.hpp"


class hierarchy
{


    monobehaviorClass ** GameObjects;//=new monobehaviorClass*[100];
    //B: da el mfrod array mn no3 el parent class, 3ashan a3raf atool el gameObjects
    //B: mn el array->functionCalls
public:
    static int gameObjectNo;
    hierarchy();
    void test();
    int init();
    bool add(monobehaviorClass * obj);
    void updateGameObjects();
    void drawPhong();
    void drawDepthMap();

};


#endif // HIERARCHY_H
