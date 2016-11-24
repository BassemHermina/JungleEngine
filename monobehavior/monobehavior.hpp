#ifndef MONOBEHAVIOR_H
#define MONOBEHAVIOR_H
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

#include "fileLoaders/objloader.hpp"
#include "fileLoaders/texture.hpp"



using namespace std;

class monobehaviorClass
{

public:
    virtual bool update();  //B:function to be overriden in child classes
    //B:function update di el
    //mthya2li el mfrod di tb2a private
    //TransformationClass *Transform = new TransformationClass;
    monobehaviorClass(); //B:function to be overriden in child classes


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

    //to keep the translation, rotation, scaling and update the Model matrix
    glm::mat4 RotationMatrix;
    glm::mat4 TranslationMatrix;
    glm::mat4 ScalingMatrix;

    ///required functions to view the object
    ///
    void generateAndBindBuffers();
    void updateMVP_Phong();
    void updateMVP_Depth();
    void updateModelMatrix();

    //using phong shader
    void sendDatatoBuffers_Phong();
    void disableAttribsAfterDraw_Phong();

    //using simpleDepthShader
    void sendDatatoBuffers_Depth();
    void disableAttribsAfterDraw_Depth();

    //after viewing the object ( after calling glDrawArrays )


    //draw the object
    virtual void drawPhong();
    virtual void drawDepthMap();


    void Translate(float x, float y, float z);
    void Rotate(float x, float y, float z);
    void Scale(float x, float y, float z);

};

#endif // MONOBEHAVIOR_H
