
#include "Harry_frames.hpp"
#include "Shaders.hpp"
#include <shaderlibrary.h>

bool Harryframes::update()
{
    //implement update function
    //to update the buffers MVP and matrices belonging to this .obj
    cout << "Suzanne updated";

    // hena 7asab el zrayer el ana dayes-ha hayod5ol fl function di we y3'aiar fl model matrix
    // be functions translate , euler rotate , we scale we keda


}

Harryframes::Harryframes()
{
    fileLocation = "Harry_frames/Harrypotter_obj_0000";
    textureLocation = "Harry Potter/Harry_all.bmp";
    //res = loadOBJ(fileLocation, this->vertices, this->uvs, this->normals);
    Texture = loadBMP_custom(textureLocation.c_str());

    //generateAndBindBuffers(); will create another one


}

//must load every frame (once per frame/object)
GLuint Harryframes::loadaFrame(string frame){
    // frame ex. : 01 , 02 , 11 , ... 69
    string file = fileLocation + frame + ".obj";

    //lazem clear 3ashan ana ba7ot fi nafs el vector kaza mra
    this->vertices.clear();
    this->uvs.clear();
    this->normals.clear();
    return loadOBJ(file.c_str(), this->vertices, this->uvs, this->normals);
}

//must generate a buffer for everyframe (once per frame/object)
void Harryframes::generateaBuffer(int frame){
    // frame ex. : 1 , 2 , ... 69 , will not use 0

    glGenBuffers(1, &vertexBuffer[frame]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[frame]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalBuffer[frame]);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer[frame]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}

// only once (same UV map for all frames)
void Harryframes::generateUVbuffer(){
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

}

// required to draw (inside draw loop)
void Harryframes::sendData(int frame)
{
    Shader * PhongShader;
    PhongShader = ShaderLibrary::GetPhongShader();
    PhongShader->Use();

    PhongShader->SendUniform("MVP", this->MVP);
    glm::mat4 Minv = glm::inverse(this->ModelMatrix);
    PhongShader->SendUniform("Minv", Minv);
    PhongShader->SendUniform("M", this->ModelMatrix);
    PhongShader->SendUniform("V", this->ViewMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->Texture);
    PhongShader->SendUniform("myTextureSampler", 0);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(PhongShader->Attribute("vertexPosition_modelspace"));
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer[frame]);
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
    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
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
    glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer[frame]);
    glVertexAttribPointer(
        PhongShader->Attribute("vertexNormal_modelspace"),    // The attribute we want to configure
        3,                            // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );
}


void Harryframes::disableAttribsAfterDraw()
{
    Shader * PhongShader;
    PhongShader = ShaderLibrary::GetPhongShader();
    glDisableVertexAttribArray(PhongShader->Attribute("vertexPosition_modelspace"));
    glDisableVertexAttribArray(PhongShader->Attribute("vertexUV"));
    glDisableVertexAttribArray(PhongShader->Attribute("vertexNormal_modelspace"));

}

void Harryframes::updateMVP()
{
    // re computes the projection&view matrices
    computeMatricesFromInputs();
    this->ProjectionMatrix = getProjectionMatrix();
    this->ViewMatrix = getViewMatrix();
    this->MVP = ProjectionMatrix * ViewMatrix * ModelMatrix; // and this too
}


void Harryframes::draw(int frame)
{
    //this updates the model matrix from the new transformations - if exists - and the MVP matrix
    updateModelMatrix();

    updateMVP();

    sendData(frame);

    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());

    disableAttribsAfterDraw();

}


void Harryframes::Translate(float x, float y, float z)
{
    glm::mat4 TranslationMatrixTemp = glm::translate(glm::mat4(), glm::vec3(x,y,z));
    this->TranslationMatrix = TranslationMatrixTemp;
}

void Harryframes::Rotate(float x, float y, float z)
{
    //Model = glm::rotate(Model, angle_in_degrees, glm::vec3(x, y, z)); // where x, y, z is axis of rotation (e.g. 0 1 0)
    this->RotationMatrix = glm::rotate(glm::mat4(), x, glm::vec3(1,0,0)); // rotate arround x with x degree
    this->RotationMatrix = glm::rotate(glm::mat4(), y, glm::vec3(0,1,0)); // rotate arround x
    this->RotationMatrix = glm::rotate(glm::mat4(), z, glm::vec3(0,0,1)); // rotate arround x


}

void Harryframes::Scale(float x, float y, float z)
{
    glm::mat4 ScalingMatrixTemp = glm::scale(glm::mat4(), glm::vec3(x, y, z));
    this->ScalingMatrix = ScalingMatrixTemp;
}

void Harryframes::updateModelMatrix()
{
    this->ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
}


void Harryframes::loadAnimation()
{
//    loadaFrame("15");
//    generateUVbuffer(); // da lazm ba3d ma3ml load le ai frame ( 3ashan yb2a m3aia el data )
//    generateaBuffer(15);

//    loadaFrame("35");
//    generateaBuffer(35);

    int framenumber;

    string result;
    string frame;

    // i = number of frames
    // i : 1 -> 69
    // loadaframe(string frameNo)
    // generateaBuffer ( int frameNo )

    for (int i = 1; i <= 69 ; i++)
    {
        stringstream convert; // stringstream used for the conversion

        framenumber = i;
        convert << framenumber;//add the value of Number to the characters in the stream
        result = convert.str();//set Result to the content of the stream

        if (framenumber < 10)
            frame = "0" + result;
        else
            frame = result;

        cout << frame << endl;
        loadaFrame(frame);
        generateUVbuffer();
        generateaBuffer(i);

    }

}
