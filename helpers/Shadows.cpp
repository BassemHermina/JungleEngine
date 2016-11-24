// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Shaders.hpp"
#include <shaderlibrary.h>
#include "Shadows.hpp"


Shadow::Shadow()
{
    //not now, we willl figure out when
//    Shader * simpleDepthShader;
//    simpleDepthShader = ShaderLibrary::GetsimpleDepthShader();
//    simpleDepthShader->LoadShader("ShadowMapping", "simpleDepthShader.vertexshader" , "simpleDepthShader.fragmentshader");
//    simpleDepthShader->Use();

    SHADOW_WIDTH = 1024;
    SHADOW_HEIGHT = 1024;

    glGenFramebuffers(1, &fb);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, fb);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
    texture, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);   //da byraga3 el buffer el kan wasel el awel , msh el ana 3amalto , 3'aleban el 0 da el default buffer


    ConfigureShaderAndMatrices_ortho();
}

void Shadow::RenderShadowMap(){

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
   // glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);


    //select shader and load it


}

void Shadow::ConfigureShaderAndMatrices_ortho()
//ortho means that it uses orthogonal matrix transformation
//because i use directional light
//if it was a point light, it should be prespective not orthogonal
{
    near_plane = -10.0f;
    far_plane = 100.0f;

    lightInvDir = glm::vec3(5,40.0f,30.0f);   // LightPosition_worldspace" = vec3(0,40,0)
    lightInvDir = glm::vec3(05,10,10);
    // Compute the MVP matrix from the light's point of view
    depthProjectionMatrix = glm::ortho(-20.0f, 20.0f, -15.0f, 15.0f, -10.0f, 30.0f);
    depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0.0f, 0.0f, 0.0001f), glm::vec3(0.0, 1.0, 0.0));
    depthVP = depthProjectionMatrix * depthViewMatrix;

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    Shader * simpleDepthShader;
    simpleDepthShader = ShaderLibrary::GetsimpleDepthShader();

    ///ana msh 3amel load shadow fi el draw , we mynfa3sh a3ml mrteen fa ya hna ya hnak fl debug
    simpleDepthShader->LoadShader("ShadowMapping", "simpleDepthShader.vertexshader" , "simpleDepthShader.fragmentshader");
    simpleDepthShader->Use();
    simpleDepthShader->SendUniform("depthVP", depthVP);

    //    simpleDepthShader->Use();


}
