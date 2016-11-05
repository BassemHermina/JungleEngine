
#include "Suzanne.hpp"
#include "includes.hpp"

bool SuzanneClass::update()
{
    //implement update function
    //to update the buffers MVP and matrices belonging to this .obj
    cout << "Suzanne updated";

    // hena 7asab el zrayer el ana dayes-ha hayod5ol fl function di we y3'aiar fl model matrix
    // be functions translate , euler rotate , we scale we keda


}

SuzanneClass::SuzanneClass()
{
    //.obj file and .bmp texture file
    fileLocation = "3dmodels/suzanne.obj";
    //fileLocation = "cube.obj";
    textureLocation = "3dmodels/suzanneTexBmp.bmp";
    Texture = loadBMP_custom(textureLocation);

    res = loadOBJ(fileLocation, this->vertices, this->uvs, this->normals);
    //generateAndBindBuffers(); mynfa3sh di tt3ml hna , 3ashan ana wana barsem
    // kol mara haloop 3la kol el objects , a3ml bind warsmhom wad5ol 3l ba3do w keda
    // mynf3sh a bind mn l awel

    //these belongs to contol.cpp bas ana ha3ml wa7da zyha we hyb2a fiha el projection wel view matrices bto3 el world
    // Projection and view are global , laken model fi mnha fi kol wa7ed
    cout << "done" <<endl;

}

void SuzanneClass::generateAndBindBuffers()
{
    glGenBuffers(1, &this->vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);
}

void SuzanneClass::sendDatatoBuffers()
{
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(getOPENGLTAGS().MatrixIDHandle, 1, GL_FALSE, &this->MVP[0][0]);

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->Texture);
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(getOPENGLTAGS().TextureIDHandle, 0);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(getOPENGLTAGS().vertexPosition_modelspaceIDHandle);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glVertexAttribPointer(
        getOPENGLTAGS().vertexPosition_modelspaceIDHandle,  // The attribute we want to configure
        3,                            // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(getOPENGLTAGS().vertexUVIDHandle);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
    glVertexAttribPointer(
        getOPENGLTAGS().vertexUVIDHandle,                   // The attribute we want to configure
        2,                            // size : U+V => 2
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );
}

void SuzanneClass::disableAttribsAfterDraw()
{
    glDisableVertexAttribArray(getOPENGLTAGS().vertexPosition_modelspaceIDHandle);
    glDisableVertexAttribArray(getOPENGLTAGS().vertexUVIDHandle);
}

void SuzanneClass::updateMVPaccordingToPressKeys()
{
    computeMatricesFromInputs();  //el satr da el kan mbawazha !!!!!!
    this->ProjectionMatrix = getProjectionMatrix();
    this->ViewMatrix = getViewMatrix();
    //this->ModelMatrix = glm::mat4(1.0); // this is just initializing , laken hadiha el data ba3d keda fi update();
    this->MVP = ProjectionMatrix * ViewMatrix * ModelMatrix; // and this too
}

void SuzanneClass::draw()
{
    updateMVPaccordingToPressKeys(); // da mashkok fi mkano lesa
    generateAndBindBuffers();
    sendDatatoBuffers();

    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());

    disableAttribsAfterDraw();

}



