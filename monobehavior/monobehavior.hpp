#ifndef MONOBEHAVIOR_H
#define MONOBEHAVIOR_H
#include<iostream>
#include <GL/glew.h>
#include<transformation/transformation.hpp>
// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class monobehaviorClass
{

public:
    virtual bool update();  //B:function to be overriden in child classes
                    //B:function update di el
    //mthya2li el mfrod di tb2a private
    TransformationClass *Transform = new TransformationClass;
    monobehaviorClass(); //B:function to be overriden in child classes

};

#endif // MONOBEHAVIOR_H
