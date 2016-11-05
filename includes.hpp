// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "fileLoaders/shader.hpp"
#include "fileLoaders/controls.hpp"  // hashil da b3d keda ba3d mafham el gowah , msh 3aiz ana l controls el 3'abeya di
#include "fileLoaders/objloader.hpp"
#include "fileLoaders/texture.hpp"

#include <glm/gtx/euler_angles.hpp>//rotation
#include <glm/gtx/norm.hpp>//rotation

//object headers
#include "Objects/Suzanne.hpp"
#include "Objects/Shell.hpp"

struct Handles {
    GLuint ProgramIDHandle;
    GLuint MatrixIDHandle;
    GLuint vertexPosition_modelspaceIDHandle;
    GLuint vertexUVIDHandle;
    GLuint TextureIDHandle;
};

Handles getOPENGLTAGS (); //get OPENGLTAGS from main to any other class that don't have access to main but can read this header






