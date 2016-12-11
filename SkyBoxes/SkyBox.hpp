#ifndef SKYBOX_H
#define SKYBOX_H

#include <map>
#include <string>
#include <stdexcept>
#include <iostream>

#include <GL/glew.h>
// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "fileLoaders/texture.hpp"

#include <includes.hpp>
using namespace std;

class SkyBox {

    public:
        SkyBox();
        std::vector<std::string> faces;
        GLuint skyboxTexture;
        GLuint cubaMapVertexBuffer;
        GLuint loadCubemap(std::vector<std::string> faces);


        void clearThenDraw(GLuint FB_ID);
        void InitReal();
        void InitBlurry();

};

#endif
