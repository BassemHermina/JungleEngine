
#include "Shell.hpp"
#include "includes.hpp"

bool ShellClass::update()
{
    //implement update function
    //to update the buffers MVP and matrices belonging to this .obj
    cout << "Suzanne updated";

    // hena 7asab el zrayer el ana dayes-ha hayod5ol fl function di we y3'aiar fl model matrix
    // be functions translate , euler rotate , we scale we keda


}

ShellClass::ShellClass()
{
    //.obj file and .bmp texture file
    fileLocation = "3dmodels/shell.obj";
    //fileLocation = "cube.obj";
    textureLocation = "3dmodels/shelltexbmp.bmp";
    Texture = loadBMP_custom(textureLocation);

    res = loadOBJ(fileLocation, this->vertices, this->uvs, this->normals);
    //generateAndBindBuffers(); mynfa3sh di tt3ml hna , 3ashan ana wana barsem
    // kol mara haloop 3la kol el objects , a3ml bind warsmhom wad5ol 3l ba3do w keda
    // mynf3sh a bind mn l awel

    //these belongs to contol.cpp bas ana ha3ml wa7da zyha we hyb2a fiha el projection wel view matrices bto3 el world
    // Projection and view are global , laken model fi mnha fi kol wa7ed
    cout << "done" <<endl;
    generateAndBindBuffers();
    sendDatatoBuffers();
}

void ShellClass::generateAndBindBuffers()
{
    glGenBuffers(1, &this->vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);
}

void ShellClass::sendDatatoBuffers()
{
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(getOPENGLTAGS().Shader_MVPMatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(getOPENGLTAGS().Shader_ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniformMatrix4fv(getOPENGLTAGS().Shader_ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
    //!BH Bassem lamma bansa dol byb2a el gesm bylef bs el eda2a ka2enaha sabta bnsbalo
    //! 3ashan el normals el 3leh asln btt7sb mn M vector, wana m5ali el M el awlani lw mb3atesh dol fa bl nesba
    //! lel light wel specular hwa mat7raksh

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

void ShellClass::disableAttribsAfterDraw()
{
    glDisableVertexAttribArray(getOPENGLTAGS().Shader_vertexPosition_modelspaceID);
    glDisableVertexAttribArray(getOPENGLTAGS().Shader_vertexUVID);
    glDisableVertexAttribArray(getOPENGLTAGS().Shader_vertexNormal_modelspaceID);

}

void ShellClass::updateMVPaccordingToPressKeys()
{
    computeMatricesFromInputs();  //el satr da el kan mbawazha !!!!!!
    this->ProjectionMatrix = getProjectionMatrix();
    this->ViewMatrix = getViewMatrix();
    //this->ModelMatrix = glm::mat4(1.0); // this is just initializing , laken hadiha el data ba3d keda fi update();
    this->MVP = ProjectionMatrix * ViewMatrix * ModelMatrix; // and this too
}

void ShellClass::draw()
{
    updateMVPaccordingToPressKeys(); // da mashkok fi mkano lesa
    //generateAndBindBuffers();
    sendDatatoBuffers();

    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());

    disableAttribsAfterDraw();

}



