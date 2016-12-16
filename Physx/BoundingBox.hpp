#ifndef BBOX_H
#define BBOX_H
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
#include "Objects/Harry_frames.hpp"
#include "Maze/Parts.hpp"

using namespace std;

class Bounding_box
{

public:
    Bounding_box(monobehaviorClass*);
    Bounding_box(Parts*);
    ~Bounding_box();

    void UpdateLocationWithObject();
    void UpdateLocationWithObject2(); //used with Harryframes class
    // just to handle differences in the class structure between
    //Harry frames and the Monobehaviour class
    void draw();
    void draw2();

    //handler ysh-awer 3l object we kol ma yt7arak yt7aak m3ah
    // Cube 1x1x1, centered on origin
    GLfloat vertices[108] = {
        // Positions
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,

        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f
    };

    GLuint verticesBuffer;
    GLfloat
        min_x, max_x,
        min_y, max_y,
        min_z, max_z;

    //handler ysh-awer 3l object
    monobehaviorClass *theObject;
    Parts * MazeObject; //Parts class object
    glm::vec3 size;
    glm::vec3 center;

    glm::mat4 ModelMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    glm::mat4 MVP;
    glm::mat4 objectRotationMatrix;
    glm::mat4 objectTranslationMatrix;
    glm::mat4 objectScalingMatrix;




};

#endif
