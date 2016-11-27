#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
#include <GL/glew.h> // Include glew to get all the required OpenGL
class Texture;
#include "includes.hpp"// msh 3aref ha3ml include wla hasibo keda
class Shader
{
public:

    Shader();
    ~Shader(void);
    string GetName() const;

    GLuint Program() const;
    void Init();
    bool IsInUse() const;
    void Use() const;
    void Release() const;
    void LoadShader(string shaderName, const char * vertexSourcePath, const char * fragmentSourcePath);

//    //TODO : send a matrix/texture as a uniform to shader
//    void SendUniform(string name, Texture* texture);

    void SendUniform(const char * name, glm::mat4 mat);
    void SendUniform(const char * name, glm::mat3 mat);

    void SendUniform(const char * name, float value);
    void SendUniform(const char * name, int value);
    void SendUniform(const char * name, glm::vec2 vec);
    void SendUniform(const char * name, glm::vec3 vec);
    void SendUniform(const char * name, glm::vec4 vec);
    void Link();
    GLuint Uniform(const char * uniformName) const;
    GLuint Attribute(const char * attributeName) const;
    GLuint ProgramID;

    bool loaded;

private:


    GLuint fragment;
    GLuint vertex;
    string name;
};//static PhongShader ("PhongShader", "StandardShading.vertexshader", "StandardShading.fragmentshader");



// static Shader PhongShader("PhongShader", "StandardShading.vertexshader", "StandardShading.fragmentshader");




/////////////////////////////////////////////////////
// Shaders Hints
// 1- PhongShader
//      - MVP   : MVPMatrix
//      - V     : ViewMatrix
//      - M     : ModelMatrix
//      - LightPower
//      - vertexPosition_modelspace
//      - vertexUV
//      - vertexNormal_modelspace
//      - myTextureSampler
//      - LightPosition_worldspace
/////////////////////////////////////////////////////
#endif
