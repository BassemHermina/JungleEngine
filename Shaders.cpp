#include "Shaders.hpp"
#include "fileLoaders/shader.hpp"
#include "fileLoaders/texture.hpp"


Shader::Shader()
{
    loaded = false;
//    this->name = shaderName;
//    this->ProgramID = LoadShaders(vertexSourcePath,fragmentSourcePath);
//    //this->ProgramID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
}

void Shader::LoadShader(string shaderName, const char * vertexSourcePath, const char * fragmentSourcePath)
{
    if (!loaded)
    {
        this->name = shaderName;
        this->ProgramID = LoadShaders(vertexSourcePath,fragmentSourcePath);
        cout << "LoadShader -> Program ID : " << ProgramID << endl;
        loaded = true;
    }
    //this->ProgramID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
}

void Shader::Init()
{

}

string Shader::GetName() const {
    return name;
}

Shader::~Shader(void) {
    glDetachShader(ProgramID, fragment);
    glDeleteShader(fragment);

    glDetachShader(ProgramID, vertex);
    glDeleteShader(vertex);

    glDeleteProgram(ProgramID);
}

GLuint Shader::Program() const {
    return ProgramID;
}

void Shader::Use() const {
    //if (IsInUse()) cout << "was in use" <<endl;  // for debugging purposes
    if(!IsInUse())
    {
        cout << "wasn't in use " << endl;
        glUseProgram(Program());
    }

    //Write here any "tazbitat" for the shader:
    // like: glDrawBuffer(GL_NONE) ,glSmoothShading( .. ba bla) ,,....
    //  7agat global keda

}

void Shader::Release() const {
    glUseProgram(0);
}


bool Shader::IsInUse() const {
    GLint currentProgram = 0; //dummy value
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return (Program() == (GLuint)currentProgram);
}

void Shader::Link() {
    glLinkProgram(ProgramID);
    GLint code;
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &code);

}

GLuint Shader::Uniform(const char * uniformName) const {

    GLuint uniform = glGetUniformLocation(Program(), uniformName);

    if(uniform < 0) {
        cout << "Uniform variable not found (" + name + ") : ";
        cout << uniformName << endl;
    }

    return uniform;
}

GLuint Shader::Attribute(const char * attributeName) const{
    GLuint attrib = glGetAttribLocation(Program(), attributeName);

    if(attrib < 0) {
        cout << "Attribute variable not found in (" + name + ") : ";
        cout << attributeName << endl;
    }
    return attrib;
}

void Shader::SendUniform(const char * name, glm::mat4 mat) {
    if(IsInUse())
    glUniformMatrix4fv(Uniform(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SendUniform(const char * name, glm::mat3 mat) {
    if(IsInUse())
    glUniformMatrix3fv(Uniform(name), 1, GL_FALSE,  &mat[0][0]);
}

void Shader::SendUniform(const char * name, float value) {
    if (IsInUse())
    glUniform1f(Uniform(name), value);
}

void Shader::SendUniform(const char * name, int value) {
    if(IsInUse())
    glUniform1i(Uniform(name), value);
}

//void Shader::SendUniform(string name, Texture* texture) {
//    assert(IsInUse());
//    glUniform1i(Uniform(name), texture->TextureIndex());
//}

void Shader::SendUniform(const char * name, glm::vec2 vec) {
    if(IsInUse())
    glUniform2f(Uniform(name), vec[0], vec[1]);
}

void Shader::SendUniform(const char * name, glm::vec3 vec) {
    if (IsInUse())
    glUniform3f(Uniform(name), vec[0], vec[1], vec[2]);
}

void Shader::SendUniform(const char * name, glm::vec4 vec) {
    if(IsInUse())
    glUniform4f(Uniform(name), vec[0], vec[1], vec[2], vec[3]);
}


