#include "monobehavior.hpp"
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


monobehaviorClass::monobehaviorClass()
{}

bool monobehaviorClass::update(){

    cout<<"This is not supposed to be seen, error in inheretence \n";
}


void monobehaviorClass::generateAndBindBuffers()
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

void monobehaviorClass::sendDatatoBuffers()
{
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform

    glUniformMatrix4fv(getOPENGLTAGS().Shader_MVPMatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(getOPENGLTAGS().Shader_ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniformMatrix4fv(getOPENGLTAGS().Shader_ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->Texture);
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(getOPENGLTAGS().Shader_TextureID, 0);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(getOPENGLTAGS().Shader_vertexPosition_modelspaceID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glVertexAttribPointer(
        getOPENGLTAGS().Shader_vertexPosition_modelspaceID,  // The attribute we want to configure
        3,                            // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(getOPENGLTAGS().Shader_vertexUVID);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
    glVertexAttribPointer(
        getOPENGLTAGS().Shader_vertexUVID,                   // The attribute we want to configure
        2,                            // size : U+V => 2
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    // 3rd attribute buffer : normals
    glEnableVertexAttribArray(getOPENGLTAGS().Shader_vertexNormal_modelspaceID);
    glBindBuffer(GL_ARRAY_BUFFER, this->normalbuffer);
    glVertexAttribPointer(
        getOPENGLTAGS().Shader_vertexNormal_modelspaceID,    // The attribute we want to configure
        3,                            // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );
}

void monobehaviorClass::disableAttribsAfterDraw()
{
    glDisableVertexAttribArray(getOPENGLTAGS().Shader_vertexPosition_modelspaceID);
    glDisableVertexAttribArray(getOPENGLTAGS().Shader_vertexUVID);
    glDisableVertexAttribArray(getOPENGLTAGS().Shader_vertexNormal_modelspaceID);

}

void monobehaviorClass::updateMVP()
{
    // re computes the projection&view matrices
    computeMatricesFromInputs();
    this->ProjectionMatrix = getProjectionMatrix();
    this->ViewMatrix = getViewMatrix();

    this->MVP = ProjectionMatrix * ViewMatrix * ModelMatrix; // and this too
}

void monobehaviorClass::draw()
{
    //this updates the model matrix from the new transformations - if exists - and the MVP matrix
    updateModelMatrix();

    updateMVP();

    sendDatatoBuffers();

    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());

    disableAttribsAfterDraw();

}

void monobehaviorClass::Translate(float x, float y, float z)
{
    glm::mat4 TranslationMatrixTemp = glm::translate(glm::mat4(), glm::vec3(x,y,z));
    this->TranslationMatrix = TranslationMatrixTemp;
}

void monobehaviorClass::Rotate(float x, float y, float z)
{
    //Model = glm::rotate(Model, angle_in_degrees, glm::vec3(x, y, z)); // where x, y, z is axis of rotation (e.g. 0 1 0)
    this->RotationMatrix = glm::rotate(glm::mat4(), x, glm::vec3(1,0,0)); // rotate arround x with x degree
    this->RotationMatrix = glm::rotate(glm::mat4(), y, glm::vec3(0,1,0)); // rotate arround x
    this->RotationMatrix = glm::rotate(glm::mat4(), z, glm::vec3(0,0,1)); // rotate arround x


}

void monobehaviorClass::Scale(float x, float y, float z)
{
    glm::mat4 ScalingMatrixTemp = glm::scale(glm::mat4(), glm::vec3(x, y, z));
    this->ScalingMatrix = ScalingMatrixTemp;
}

void monobehaviorClass::updateModelMatrix()
{
    this->ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
}


