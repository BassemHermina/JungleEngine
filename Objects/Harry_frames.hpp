#ifndef HARRY_FRAMES_H
#define HARRY_FRAMES_H
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

class Harryframes
{
    // dol bbytkararo 3la tol fi kol object
    GLuint Texture;
    string fileLocation;
    string textureLocation;

    // fi wa7ed zyada 3ashan a3raf a2ol el rakam el realistic bdal matla5bat
    // i will not use [0]
    GLuint vertexBuffer [70];
    GLuint normalBuffer [70];
    GLuint uvBuffer;


    glm::mat4 ProjectionMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ModelMatrix;
    glm::mat4 MVP;


public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;


    glm::mat4 RotationMatrix;
    glm::mat4 TranslationMatrix;
    glm::mat4 ScalingMatrix;

    bool update();
    Harryframes();
    GLuint loadaFrame(string frame);
    void generateaBuffer(int frame);
    void generateUVbuffer();

    void sendData(int frame);
    void disableAttribsAfterDraw();
    void updateMVP();
    void updateModelMatrix();
    void Scale(float x, float y, float z);
    void Rotate(float x, float y, float z);
    void Translate(float x, float y, float z);

    void draw(int frame);
    void loadAnimation();


};

#endif
