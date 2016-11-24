#include "shaderlibrary.h"

ShaderLibrary::ShaderLibrary() {}

ShaderLibrary::~ShaderLibrary() {
    map<string, Shader*>::iterator it;

    for(it = shaders.begin(); it != shaders.end(); ++it) {
        delete it->second;
    }

    shaders.clear();

}

void ShaderLibrary::AddShader(string shaderName, Shader * shader) {
    shaders.insert(pair<string, Shader*>(shaderName, shader));
}

Shader* ShaderLibrary::GetShader(string shaderName) const {
    Shader* shader = shaders.find(shaderName)->second;

    if(shader == NULL) {
        throw new runtime_error("Didn't found shader " + shaderName + " in the shader library");
    }

    return shader;
}


void ShaderLibrary::initializeShaders()
{
   ShaderLibrary::PhongShader.LoadShader("PhongShader", "StandardShading.vertexshader", "StandardShading.fragmentshader");

}

Shader ShaderLibrary::PhongShader;

Shader * ShaderLibrary::GetPhongShader()
{
    return  &ShaderLibrary::PhongShader;
}

Shader ShaderLibrary::simpleDepthShader;

Shader * ShaderLibrary::GetsimpleDepthShader()
{
    return  &ShaderLibrary::simpleDepthShader;
}


Shader ShaderLibrary::TexToScreen;

Shader * ShaderLibrary::GetTexToScreen()
{
    return  &ShaderLibrary::TexToScreen;
}



//TexToScreen


