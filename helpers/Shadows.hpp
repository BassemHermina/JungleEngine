#ifndef SHADOWS_H
#define SHADOWS_H
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
#include "fileLoaders/controls.hpp"

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "fileLoaders/texture.hpp"

using namespace std;

class Shadow
{
public:
    GLuint fb;
    GLuint rb;
    GLuint SHADOW_WIDTH ;//= 768
    GLuint SHADOW_HEIGHT ; //= 1024;
    GLuint texture;

    GLfloat near_plane;
    GLfloat far_plane;

    glm::mat4 depthProjectionMatrix;
    glm::mat4 depthViewMatrix;
    glm::mat4 depthModelMatrix;
    glm::mat4 depthVP;

    glm::vec3 lightInvDir;

    Shadow();
    void PreRenderShadowMap();
    void ConfigureShaderAndMatrices_ortho();
    void RenderScene();
    void initialize();


};







#endif
