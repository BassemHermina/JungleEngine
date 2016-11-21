#ifndef PLANE_H
#define PLANE_H
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

class PlaneClass : public monobehaviorClass
{
    // dol bbytkararo 3la tol fi kol object
public:
    bool update();
    PlaneClass();
    const char* fileLocation;
    const char* textureLocation;

};

#endif
