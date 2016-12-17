
#include "BoundingBox.hpp"
#include "Shaders.hpp"
#include <shaderlibrary.h>
Bounding_box::Bounding_box(monobehaviorClass* theObjectP)
{
    Shader * BoundingboxShader;
    BoundingboxShader = ShaderLibrary::GetBoundingboxShader();
    BoundingboxShader->LoadShader("BoundingBoxShader", "BoundingBox.vert", "BoundingBox.frag");

    theObject = theObjectP;
    if (theObject->vertices.size() == 0)
        return;

    glGenBuffers(1, &verticesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    min_x = max_x = theObject->vertices[0].x;
    min_y = max_y = theObject->vertices[0].y;
    min_z = max_z = theObject->vertices[0].z;

    for (int i = 0; i < theObject->vertices.size(); i++) {
        if (theObject->vertices[i].x < min_x) {min_x = theObject->vertices[i].x; MinXvec = theObject->vertices[i];}
        if (theObject->vertices[i].x > max_x) {max_x = theObject->vertices[i].x; MaxXvec = theObject->vertices[i];}
        if (theObject->vertices[i].y < min_y) {min_y = theObject->vertices[i].y; MinYvec = theObject->vertices[i];}
        if (theObject->vertices[i].y > max_y) {max_y = theObject->vertices[i].y; MaxYvec = theObject->vertices[i];}
        if (theObject->vertices[i].z < min_z) {min_z = theObject->vertices[i].z; MinZvec = theObject->vertices[i];}
        if (theObject->vertices[i].z > max_z) {max_z = theObject->vertices[i].z; MaxZvec = theObject->vertices[i];}
      }

    this->size = glm::vec3(max_x-min_x, max_y-min_y, max_z-min_z);
    //cout << "BBsize = " << size.x << ", " << size.y << ", " << size.z << "." << endl;
    this->center = glm::vec3((min_x+max_x)/2, (min_y+max_y)/2, (min_z+max_z)/2);
    //cout << "BBcenter = " << center.x << ", " << center.y << ", " << center.z << "." << endl;


}

void Bounding_box::draw()
{//Used for debugging

    UpdateLocationWithObject();
    //that's how i update model matrix now
    //this line translates the center with the same translation of the object
    //transform = tranlation * scale
    this->ModelMatrix =  objectTranslationMatrix* glm::translate(glm::mat4(1), center)*objectRotationMatrix*glm::scale(glm::mat4(1), size) * objectScalingMatrix;

    //Bounding box equation helpers, these are to calculate the important max and min points of the cube after transforming
    //the bounding box standard 1x1x1 cube to it's position of the object, and after animating te object too, i update the
    // model matrix then multiply these points (every one of them carry the important point in xyz format, the only important part
    // is in the name) to get the new in world real position
    glm::mat4 ScaleTmp = glm::scale(glm::mat4(1), vec3(0.2,0.2,0.15));
    // ALLIGNING
    //here i don't multipy with model matrix totally as i don't want the rotation here
    // the viewed box is not logically right, this is different from it
    upMaxXvec = objectTranslationMatrix* glm::translate(glm::mat4(1), center)*glm::scale(glm::mat4(1), size) * ScaleTmp * objectScalingMatrix * glm::vec4(MaxXvec,1.0f);
    upMinXvec = objectTranslationMatrix* glm::translate(glm::mat4(1), center)*glm::scale(glm::mat4(1), size) * ScaleTmp  * objectScalingMatrix * glm::vec4(MinXvec,1.0f);
    upMaxYvec = objectTranslationMatrix* glm::translate(glm::mat4(1), center)*glm::scale(glm::mat4(1), size)  * ScaleTmp * objectScalingMatrix * glm::vec4(MaxYvec,1.0f);
    upMinYvec = objectTranslationMatrix* glm::translate(glm::mat4(1), center)*glm::scale(glm::mat4(1), size) * ScaleTmp  * objectScalingMatrix * glm::vec4(MinYvec,1.0f);
    upMaxZvec = objectTranslationMatrix* glm::translate(glm::mat4(1), center)*glm::scale(glm::mat4(1), size) * ScaleTmp  * objectScalingMatrix * glm::vec4(MaxZvec,1.0f);
    upMinZvec = objectTranslationMatrix* glm::translate(glm::mat4(1), center)*glm::scale(glm::mat4(1), size) * ScaleTmp  * objectScalingMatrix * glm::vec4(MinZvec,1.0f);

    //re-compute the projection and view matrix
    computeMatricesFromInputs();
    this->ProjectionMatrix = getProjectionMatrix();
    this->ViewMatrix = getViewMatrix();

    this->MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    Shader * BoundingboxShader;
    BoundingboxShader = ShaderLibrary::GetBoundingboxShader();
    BoundingboxShader->Use();

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    BoundingboxShader->SendUniform("MVP", this->MVP); //sending the "m"

    /////////
    glBindBuffer(GL_ARRAY_BUFFER, this->verticesBuffer);
    glEnableVertexAttribArray(BoundingboxShader->Attribute("vertexPosition_modelspace"));
    glVertexAttribPointer(
        BoundingboxShader->Attribute("vertexPosition_modelspace"),  // attribute
        3,                  // number of elements per vertex, here (x,y,z,w)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        (void*)0                    // offset of first element
    );

    glDrawArrays(GL_LINE_LOOP, 0,108);

    glDisableVertexAttribArray(BoundingboxShader->Attribute("vertexPosition_modelspace"));
    glBindBuffer(GL_ARRAY_BUFFER, 0);


}


Bounding_box::~Bounding_box()
{

    glDeleteBuffers(1, &verticesBuffer);
}

void Bounding_box::UpdateLocationWithObject()
{
    this->objectRotationMatrix = theObject->RotationMatrix;
    this->objectScalingMatrix = theObject->ScalingMatrix;
    this->objectTranslationMatrix = theObject->TranslationMatrix;
}
/////////////////////////////////////////////////////////////////////
////////
///--------------
// Handlers for other parent classes , Harryframes , Maze parts , ....
Bounding_box::Bounding_box(Parts* theObjectP)
{
    Shader * BoundingboxShader;
    BoundingboxShader = ShaderLibrary::GetBoundingboxShader();
    BoundingboxShader->LoadShader("BoundingBoxShader", "BoundingBox.vert", "BoundingBox.frag");

    MazeObject = theObjectP;
    if (MazeObject->vertices.size() == 0)
        return;

    glGenBuffers(1, &verticesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    min_x = max_x = MazeObject->vertices[0].x;
    min_y = max_y = MazeObject->vertices[0].y;
    min_z = max_z = MazeObject->vertices[0].z;

    for (int i = 0; i < MazeObject->vertices.size(); i++) {
        if (MazeObject->vertices[i].x < min_x) {min_x = MazeObject->vertices[i].x; MinXvec = MazeObject->vertices[i];}
        if (MazeObject->vertices[i].x > max_x) {max_x = MazeObject->vertices[i].x; MaxXvec = MazeObject->vertices[i];}
        if (MazeObject->vertices[i].y < min_y) {min_y = MazeObject->vertices[i].y; MinYvec = MazeObject->vertices[i];}
        if (MazeObject->vertices[i].y > max_y) {max_y = MazeObject->vertices[i].y; MaxYvec = MazeObject->vertices[i];}
        if (MazeObject->vertices[i].z < min_z) {min_z = MazeObject->vertices[i].z; MinZvec = MazeObject->vertices[i];}
        if (MazeObject->vertices[i].z > max_z) {max_z = MazeObject->vertices[i].z; MaxZvec = MazeObject->vertices[i];}
      }

    this->size = glm::vec3(max_x-min_x, max_y-min_y, max_z-min_z);
    //cout << "BBsize = " << size.x << ", " << size.y << ", " << size.z << "." << endl;
    this->center = glm::vec3((min_x+max_x)/2, (min_y+max_y)/2, (min_z+max_z)/2);
    //cout << "BBcenter = " << center.x << ", " << center.y << ", " << center.z << "." << endl;

}

void Bounding_box::UpdateLocationWithObject2()
{
    this->objectRotationMatrix = MazeObject->RotationMatrix;
    this->objectScalingMatrix = MazeObject->ScalingMatrix;
    this->objectTranslationMatrix = MazeObject->TranslationMatrix;
}
void Bounding_box::draw2()
{//Used for debugging

    // ma nsta5dem el vertices bto3 el cube ka max we min tyb ? dol byt3mlhom upload b3d kol draw..
    UpdateLocationWithObject2();
    //that's how i update model matrix now
    //this line translates the center with the same translation of the object
    //transform = tranlation * scale
    this->ModelMatrix =  objectTranslationMatrix* glm::translate(glm::mat4(1), center)* objectScalingMatrix *glm::scale(glm::mat4(1), size);

    upMaxXvec = objectTranslationMatrix* glm::translate(glm::mat4(1), center)* objectScalingMatrix  * glm::vec4(MaxXvec,1.0f);
    upMinXvec = objectTranslationMatrix* glm::translate(glm::mat4(1), center)* objectScalingMatrix  * glm::vec4(MinXvec,1.0f);
    upMaxYvec = objectTranslationMatrix* glm::translate(glm::mat4(1), center)* objectScalingMatrix  * glm::vec4(MaxYvec,1.0f);
    upMinYvec = objectTranslationMatrix* glm::translate(glm::mat4(1), center)* objectScalingMatrix  * glm::vec4(MinYvec,1.0f);
    upMaxZvec = objectTranslationMatrix* glm::translate(glm::mat4(1), center)* objectScalingMatrix  * glm::vec4(MaxZvec,1.0f);
    upMinZvec = objectTranslationMatrix* glm::translate(glm::mat4(1), center)* objectScalingMatrix  * glm::vec4(MinZvec,1.0f);

    //cout << "draw2? : " << upMaxZvec.z << endl;
    //re-compute the projection and view matrix
    computeMatricesFromInputs();
    this->ProjectionMatrix = getProjectionMatrix();
    this->ViewMatrix = getViewMatrix();

    this->MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    Shader * BoundingboxShader;
    BoundingboxShader = ShaderLibrary::GetBoundingboxShader();
    BoundingboxShader->Use();

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    BoundingboxShader->SendUniform("MVP", this->MVP); //sending the "m"

    /////////
    glBindBuffer(GL_ARRAY_BUFFER, this->verticesBuffer);
    glEnableVertexAttribArray(BoundingboxShader->Attribute("vertexPosition_modelspace"));
    glVertexAttribPointer(
        BoundingboxShader->Attribute("vertexPosition_modelspace"),  // attribute
        3,                  // number of elements per vertex, here (x,y,z,w)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        (void*)0                    // offset of first element
    );

    glDrawArrays(GL_LINE_LOOP, 0,108);

    glDisableVertexAttribArray(BoundingboxShader->Attribute("vertexPosition_modelspace"));
    glBindBuffer(GL_ARRAY_BUFFER, 0);


}

