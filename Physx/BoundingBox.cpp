
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
        if (theObject->vertices[i].x < min_x) min_x = theObject->vertices[i].x;
        if (theObject->vertices[i].x > max_x) max_x = theObject->vertices[i].x;
        if (theObject->vertices[i].y < min_y) min_y = theObject->vertices[i].y;
        if (theObject->vertices[i].y > max_y) max_y = theObject->vertices[i].y;
        if (theObject->vertices[i].z < min_z) min_z = theObject->vertices[i].z;
        if (theObject->vertices[i].z > max_z) max_z = theObject->vertices[i].z;
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
        if (MazeObject->vertices[i].x < min_x) min_x = MazeObject->vertices[i].x;
        if (MazeObject->vertices[i].x > max_x) max_x = MazeObject->vertices[i].x;
        if (MazeObject->vertices[i].y < min_y) min_y = MazeObject->vertices[i].y;
        if (MazeObject->vertices[i].y > max_y) max_y = MazeObject->vertices[i].y;
        if (MazeObject->vertices[i].z < min_z) min_z = MazeObject->vertices[i].z;
        if (MazeObject->vertices[i].z > max_z) max_z = MazeObject->vertices[i].z;
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

    UpdateLocationWithObject2();
    //that's how i update model matrix now
    //this line translates the center with the same translation of the object
    //transform = tranlation * scale
    this->ModelMatrix =  objectTranslationMatrix* glm::translate(glm::mat4(1), center)*objectRotationMatrix*glm::scale(glm::mat4(1), size) * objectScalingMatrix;

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

