#ifndef SUZANNE_H
#define SUZANNE_H
#include<iostream>
#include <GL/glew.h>
// Include GLFW
#include <GL/glfw.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "monobehavior/monobehavior.hpp"

using namespace std;

class SuzanneClass : public monobehaviorClass
{
    // dol bbytkararo 3la tol fi kol object
public:
    bool update();
    SuzanneClass();
    const char* fileLocation;
    const char* textureLocation;

};

#endif
