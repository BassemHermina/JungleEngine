#include "SkyBox.hpp"
#include "Shaders.hpp"
#include "shaderlibrary.h"
#include "fileLoaders/controls.hpp"

SkyBox::SkyBox() {

//        faces.push_back("SkyBoxes/cubemap1/plains-of-abraham_rt.bmp");
//        faces.push_back("SkyBoxes/cubemap1/plains-of-abraham_lf.bmp");
//        faces.push_back("SkyBoxes/cubemap1/plains-of-abraham_dn.bmp"); //supposed to be up
//        faces.push_back("SkyBoxes/cubemap1/plains-of-abraham_up.bmp"); //supposed to be down
//        faces.push_back("SkyBoxes/cubemap1/plains-of-abraham_bk.bmp");
//        faces.push_back("SkyBoxes/cubemap1/plains-of-abraham_ft.bmp");

//        faces.push_back("SkyBoxes/cubemap1/Blur/plains-of-abraham_rt.bmp");
//        faces.push_back("SkyBoxes/cubemap1/Blur/plains-of-abraham_lf.bmp");
//        faces.push_back("SkyBoxes/cubemap1/Blur/plains-of-abraham_dn.bmp"); //supposed to be up
//        faces.push_back("SkyBoxes/cubemap1/Blur/plains-of-abraham_up.bmp"); //supposed to be down
//        faces.push_back("SkyBoxes/cubemap1/Blur/plains-of-abraham_bk.bmp");
//        faces.push_back("SkyBoxes/cubemap1/Blur/plains-of-abraham_ft.bmp");

//        faces.push_back("SkyBoxes/cubemap1/darkgloom_rt.bmp");
//        faces.push_back("SkyBoxes/cubemap1/darkgloom_lf.bmp");
//        faces.push_back("SkyBoxes/cubemap1/darkgloom_dn.bmp"); //supposed to be up
//        faces.push_back("SkyBoxes/cubemap1/darkgloom_up.bmp"); //supposed to be down
//        faces.push_back("SkyBoxes/cubemap1/darkgloom_bk.bmp");
//        faces.push_back("SkyBoxes/cubemap1/darkgloom_ft.bmp");

    //        faces.push_back("SkyBoxes/cubemap1/negz.bmp");
    //        faces.push_back("SkyBoxes/cubemap1/posz.bmp");
    //        faces.push_back("SkyBoxes/cubemap1/negy.bmp"); //supposed to be up
    //        faces.push_back("SkyBoxes/cubemap1/posy.bmp"); //supposed to be down
    //        faces.push_back("SkyBoxes/cubemap1/negx.bmp");
    //        faces.push_back("SkyBoxes/cubemap1/posx.bmp");
}




GLuint SkyBox::loadCubemap(std::vector<std::string> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE4);

    int width, height; // hashof 7al lesa 3ashan agib el width wel heigth mn l file mn gwa
    unsigned char* imageData;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for (GLuint i = 0; i < faces.size(); i++)
    {
               // image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        imageData = loadBMPdata_cubeMap(faces[i].c_str(), width, height);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData); // da tani wa7da kant GL_RGB msh BGR
        // 3'aleban tani wa7da di el tal3a mn el file nafso , we 3'aleban kman el bmp bbytala3 BGR
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    return textureID;
}

void SkyBox::InitReal()
{
            faces.push_back("SkyBoxes/cubemap1/negz.bmp");
            faces.push_back("SkyBoxes/cubemap1/posz.bmp");
            faces.push_back("SkyBoxes/cubemap1/negy.bmp"); //supposed to be up
            faces.push_back("SkyBoxes/cubemap1/posy.bmp"); //supposed to be down
            faces.push_back("SkyBoxes/cubemap1/negx.bmp");
            faces.push_back("SkyBoxes/cubemap1/posx.bmp");

    //outside the do loop !!
    skyboxTexture = loadCubemap(faces);
    GLfloat skyboxVertices[] = {
        // Positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    glGenBuffers(1, &cubaMapVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, cubaMapVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_DYNAMIC_DRAW);


}

void SkyBox::InitBlurry()
{


    faces.push_back("SkyBoxes/cubemap1/Blur/negz.bmp");
    faces.push_back("SkyBoxes/cubemap1/Blur/posz.bmp");
    faces.push_back("SkyBoxes/cubemap1/Blur/negy.bmp"); //supposed to be up
    faces.push_back("SkyBoxes/cubemap1/Blur/posy.bmp"); //supposed to be down
    faces.push_back("SkyBoxes/cubemap1/Blur/negx.bmp");
    faces.push_back("SkyBoxes/cubemap1/Blur/posx.bmp");


    //outside the do loop !!
    skyboxTexture = loadCubemap(faces);
    GLfloat skyboxVertices[] = {
        // Positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    glGenBuffers(1, &cubaMapVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, cubaMapVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_DYNAMIC_DRAW);


}


void SkyBox::clearThenDraw(GLuint FB_ID)
{
    //inside the loop
    Shader * cubeMapShader;
    cubeMapShader = ShaderLibrary::GetcubeMapShader();
    ////SkyBox////
    glBindFramebuffer(GL_FRAMEBUFFER, FB_ID);  //return back to default buffer which is rendered to the screen
    cubeMapShader->Use();
    glCullFace(GL_BACK);
    //glDepthMask(GL_FALSE);
    glViewport(0,0,1024,768);
    /////glClearDepth(1.0f); di bt3'aiar 7gat 3'ariba
    glClearColor(0.0f, 0.682352f, 0.933333f, 0.0f); //yaslaam yaro7 5altak :D
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    computeMatricesFromInputs();
    glm::mat4 modelMatrixCubeMap = glm::mat4(1.0f);
    modelMatrixCubeMap = scale(modelMatrixCubeMap, vec3( 50.0f, 50.0f, 50.0f));
    glm::mat4 VM = getViewMatrix() * modelMatrixCubeMap;
    cubeMapShader->SendUniform("VM" , VM);
    cubeMapShader->SendUniform("projection", getProjectionMatrix());
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
    cubeMapShader->SendUniform("skybox", 7);
    glEnableVertexAttribArray(cubeMapShader->Attribute("position"));
    glBindBuffer(GL_ARRAY_BUFFER, cubaMapVertexBuffer);
    glVertexAttribPointer(
        cubeMapShader->Attribute("position"),  // The attribute we want to configure
        3,                            // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDisableVertexAttribArray(cubeMapShader->Attribute("position"));

}
