#ifndef SHELL_H
#define SHELL_H
#include<iostream>
#include <GL/glew.h>
#include<transformation/transformation.hpp>
// Include GLFW
#include <GL/glfw.h>
#include"monobehavior/monobehavior.hpp"
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "fileLoaders/controls.hpp"
using namespace std;

class ShellClass : public monobehaviorClass
{
    // dol bbytkararo 3la tol fi kol object


public:
    bool update();
    ShellClass();
    const char* fileLocation;
    const char* textureLocation;
    GLuint Texture;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    bool res; //for function loadOBJ
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normalbuffer;

    glm::mat4 ProjectionMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ModelMatrix;
    glm::mat4 MVP;

    //required functions to view the object
    void generateAndBindBuffers();
    void sendDatatoBuffers();

    //after viewing the object ( after calling glDrawArrays )
    void disableAttribsAfterDraw();

    //draw the object
    void draw();

    void updateMVPaccordingToPressKeys();
};

#endif // MONOBEHAVIOR_H
