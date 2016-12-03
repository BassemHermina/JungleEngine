#ifndef PARTS_H
#define PARTS_H
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


using namespace std;

class Parts
{
public:
    GLuint Texture;
    GLuint getTextureIDtoBind();

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
    const char* fileLocation;
    const char* textureLocation;
    // dol bbytkararo 3la tol fi kol object
public:
    bool update();
    Parts(string obj,string txt,double x,double y,double z);
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

#endif
