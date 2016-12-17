#include "Parts.hpp"
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Shaders.hpp"
#include <shaderlibrary.h>
#include "helpers/Shadows.hpp"
Parts::Parts(string obj,string txt,double x,double y,double z)
{
    string temp="Maze/objects/";
    temp=temp+obj+".obj";
    fileLocation=temp.c_str();
    res= loadOBJ(fileLocation,this->vertices,this->uvs,this->normals);
    temp="Maze/objects/";
    temp=temp+txt+".bmp";
    textureLocation=temp.c_str();
    Texture=loadBMP_custom(textureLocation);
    //generateAndBindBuffers();
    glm::mat4 TranslationMatrixTemp = glm::translate(glm::mat4(), glm::vec3(x,z,y));
    this->TranslationMatrix = TranslationMatrixTemp;
    glm::mat4 ScalingMatrixTemp = glm::scale(glm::mat4(), glm::vec3(1, 1, 1));
    this->ScalingMatrix = ScalingMatrixTemp;
    this->RotationMatrix=eulerAngleYXZ(0.0f, 0.0f, 0.0f);

    //this->RotationMatrix = glm::rotate(glm::mat4(), 0, glm::vec3(1,0,0)); // rotate arround x with x degree
    //this->RotationMatrix = glm::rotate(glm::mat4(), 0, glm::vec3(0,1,0)); // rotate arround x
    //this->RotationMatrix = glm::rotate(glm::mat4(), 0, glm::vec3(0,0,1)); // rotate arround x

    generateAndBindBuffers();

}

void Parts::generateAndBindBuffers()
{


    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}

void Parts::sendDatatoBuffers_Phong()
{
    Shader * PhongShader;
    PhongShader = ShaderLibrary::GetPhongShader();
    PhongShader->Use();

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    PhongShader->SendUniform("MVP", this->MVP);
    // Minv needed for environment lighting calculations
    glm::mat4 Minv = glm::inverse(this->ModelMatrix);
    PhongShader->SendUniform("Minv", Minv);
    PhongShader->SendUniform("M", this->ModelMatrix);
    PhongShader->SendUniform("V", this->ViewMatrix);

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->Texture);
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    PhongShader->SendUniform("myTextureSampler", 0);


    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(PhongShader->Attribute("vertexPosition_modelspace"));
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glVertexAttribPointer(
        PhongShader->Attribute("vertexPosition_modelspace"),  // The attribute we want to configure
        3,                            // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(PhongShader->Attribute("vertexUV"));
    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
    glVertexAttribPointer(
        PhongShader->Attribute("vertexUV"),                   // The attribute we want to configure
        2,                            // size : U+V => 2
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    // 3rd attribute buffer : normals
    glEnableVertexAttribArray(PhongShader->Attribute("vertexNormal_modelspace"));
    glBindBuffer(GL_ARRAY_BUFFER, this->normalbuffer);
    glVertexAttribPointer(
        PhongShader->Attribute("vertexNormal_modelspace"),    // The attribute we want to configure
        3,                            // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );
}
void Parts::Translate(float x, float y, float z)
{
    glm::mat4 TranslationMatrixTemp = glm::translate(glm::mat4(), glm::vec3(x,y,z));
    this->TranslationMatrix = TranslationMatrixTemp;
    //cout << TranslationMatrix[0][0] << " " << TranslationMatrix[1][1] << " " << TranslationMatrix[2][2] << " ";
}

void Parts::sendDatatoBuffers_Depth()
{

    Shader * simpleDepthShader;
    simpleDepthShader = ShaderLibrary::GetsimpleDepthShader();
    simpleDepthShader->LoadShader("ShadowMapping", "simpleDepthShader.vertexshader" , "simpleDepthShader.fragmentshader");
    simpleDepthShader->Use();

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glm::mat4 VP = ProjectionMatrix * ViewMatrix;
    simpleDepthShader->SendUniform("depthVP", VP);
    simpleDepthShader->SendUniform("model", this->ModelMatrix);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(simpleDepthShader->Attribute("vertexPosition_modelspace"));
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glVertexAttribPointer(
        simpleDepthShader->Attribute("vertexPosition_modelspace"),  // The attribute we want to configure
        3,                            // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );
}

void Parts::disableAttribsAfterDraw_Phong()
{
    Shader * PhongShader;
    PhongShader = ShaderLibrary::GetPhongShader();
    glDisableVertexAttribArray(PhongShader->Attribute("vertexPosition_modelspace"));
    glDisableVertexAttribArray(PhongShader->Attribute("vertexUV"));
    glDisableVertexAttribArray(PhongShader->Attribute("vertexNormal_modelspace"));

}

void Parts::disableAttribsAfterDraw_Depth()
{
    Shader * simpleDepthShader;
    simpleDepthShader = ShaderLibrary::GetsimpleDepthShader();
    glDisableVertexAttribArray(simpleDepthShader->Attribute("vertexPosition_modelspace"));

}
void Parts::updateMVP_Phong()
{
    // re computes the projection&view matrices
    computeMatricesFromInputs();
    this->ProjectionMatrix = getProjectionMatrix();
    this->ViewMatrix = getViewMatrix();
    this->MVP = ProjectionMatrix * ViewMatrix * ModelMatrix; // and this too
}

void Parts::updateMVP_Depth()
{
    //this is just for debugging, the real matrix that will be used for mapping is in shadows class constructor
    //shadow mapping debugging
 //   this->ProjectionMatrix = glm::ortho(-10.0f, 10.0f, -7.5f, 7.5f, -10.0f, 100.0f);

    //makan matrix el orthogonal da we tolo we keda , hy3mli mshakel ktir fi 7tat ktir
    ///5ali balak en el gwa el SHADOW OBJECT mo5talef 3n da, !!! we da 3'alat
    /// el mfrod asta5dem fl 7esabat el gowa el shadow object
    /// we 3'aleban b2a keda ab3to mn l main b2a msh gowa , da sabet el mfrod hna , el VP bas y3ni

    ///// lma tsht3'al , ozbot b2a mkan el light wel look at , 3ashan tkamel ba2i l maze gowa el map
    this->ProjectionMatrix = glm::ortho(-40.0f, 40.0f, -25.0f, 25.0f, -10.0f, 50.0f);
    this->ViewMatrix =  glm::lookAt(vec3(05,10,10), glm::vec3(0.0f, 0.0f, 0.0001f), glm::vec3(0.0, 1.0, 0.0));

}

void Parts::drawPhong()
{
    //this updates the model matrix from the new transformations - if exists - and the MVP matrix
    updateModelMatrix();

    updateMVP_Phong();

    sendDatatoBuffers_Phong();

    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());

    disableAttribsAfterDraw_Phong();

}

void Parts::drawDepthMap()
{
    //this updates the model matrix from the new transformations - if exists - and the MVP matrix
    updateModelMatrix();

    updateMVP_Depth();

    sendDatatoBuffers_Depth();

    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());

    disableAttribsAfterDraw_Depth();

}



void Parts::updateModelMatrix()
{

    this->ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
}



