#ifndef SHELL_H
#define SHELL_H
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

class ShellClass : public monobehaviorClass
{
    // dol bbytkararo 3la tol fi kol object
public:
    bool update();
    ShellClass();
    const char* fileLocation;
    const char* textureLocation;

};

#endif
