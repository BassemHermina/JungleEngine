// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Shaders.hpp"
#include <shaderlibrary.h>
#include "Shadows.hpp"


void Shadow::initialize(){
    Shader * simpleDepthShader;
    simpleDepthShader = ShaderLibrary::GetsimpleDepthShader();
    simpleDepthShader->LoadShader("ShadowMapping", "simpleDepthShader.vertexshader" , "simpleDepthShader.fragmentshader");

    simpleDepthShader->Use();

    SHADOW_WIDTH = 10000;
    SHADOW_HEIGHT = 10000;

    ///ma3rafsh kan fi a fl code 3'alat kol da!!!!!!!!!!!!!
    /// 5adto copy paste esht3'al :/ m3rfshl leeh wla ezay
    fb = 7;
    glGenFramebuffers(1, &fb);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);

    // Depth texture. Slower than a depth buffer, but you can sample it later in your shader
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT32, 2048, 2048, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,texture, 0);

    glDrawBuffer(GL_NONE);  //for the currently bound buffer
    glReadBuffer(GL_NONE);

    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
       cout << "FBO is Incomplete" << endl;

    glBindTexture(GL_TEXTURE_2D, 0);        // bnrga3 lel default texture we buffer 3ashan nrga3 le flow el program el tabi3i
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);   //da byraga3 el buffer el kan wasel el awel , msh el ana 3amalto , 3'aleban el 0 da el default buffer

    ConfigureShaderAndMatrices_ortho();
}

Shadow::Shadow()
{
    //generate and maniupulate the needed data to render into the shadow map


//    GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//    switch(status) {
//        case GL_FRAMEBUFFER_COMPLETE:
//            return;
//            break;

//    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
//        throw FramebufferIncompleteException("An attachment could not be bound to frame buffer object!");
//        break;

//    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
//        throw FramebufferIncompleteException("Attachments are missing! At least one image (texture) must be bound to the frame buffer object!");
//        break;

//    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
//        throw FramebufferIncompleteException("The dimensions of the buffers attached to the currently used frame buffer object do not match!");
//        break;

//    case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
//        throw FramebufferIncompleteException("The formats of the currently used frame buffer object are not supported or do not fit together!");
//        break;

//    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
//        throw FramebufferIncompleteException("A Draw buffer is incomplete or undefinied. All draw buffers must specify attachment points that have images attached.");
//        break;

//    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
//        throw FramebufferIncompleteException("A Read buffer is incomplete or undefinied. All read buffers must specify attachment points that have images attached.");
//        break;

//    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
//        throw FramebufferIncompleteException("All images must have the same number of multisample samples.");
//        break;

//    case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS :
//        throw FramebufferIncompleteException("If a layered image is attached to one attachment, then all attachments must be layered attachments. The attached layers do not have to have the same number of layers, nor do the layers have to come from the same kind of texture.");
//        break;

//    case GL_FRAMEBUFFER_UNSUPPORTED:
//        throw FramebufferIncompleteException("Attempt to use an unsupported format combinaton!");
//        break;

//    default:
//        throw FramebufferIncompleteException("Unknown error while attempting to create frame buffer object!");
//        break;
//    }
}

void Shadow::PreRenderShadowMap(){

    if (!Inizialized){

    //required before rendering objects bucket with simple depth shader
    //implement here when it runs in the main loop
    Shader * simpleDepthMap;
    simpleDepthMap = ShaderLibrary::GetsimpleDepthShader();

    ///RenderShadowMap to FB////
    //the framebuffer must be bind before any glFunction!!!!!!!!!!!!!!!
    cout << "fb: " << fb << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, this->fb);
    glClearColor( 0.0f, 1.0f, 1.0f, 1.0f );// da mlosh lazma, hwa keda keda 3aref hya5od a mn el rasma  , el background mlhash lazma
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnableVertexAttribArray(simpleDepthMap->Attribute("vertexPosition_modelspace"));
    glViewport(0,0,2048,2048);  // must be same numbers in shadowmap object Texture Image 2D !!!
    simpleDepthMap->Use();
    glCullFace(GL_FRONT);
Inizialized = true;
}

}

void Shadow::ConfigureShaderAndMatrices_ortho()
//ortho means that it uses orthogonal matrix transformation
//because i use directional light
//if it was a point light, it should be prespective not orthogonal
{
    near_plane = -10.0f;
    far_plane = 100.0f;

    //bl bta3 da ba5tar el mkan el 2al y3ni hyb2a masdar el light fih , 3ashan da l haysabbeb mkan el shadows
    //lightInvDir = glm::vec3(5,40.0f,30.0f);   // LightPosition_worldspace" = vec3(0,40,0)
    lightInvDir = glm::vec3(05,10,10);

    ///lel asaf ana lesa msh bsta5dem dol fl 7sabat , basta5dem 7agat zyhom gowa el UpdateMVP_simpleDepthMap el gwa el MonoBehaviour
    // Compute the MVP matrix from the light's point of view
//    depthProjectionMatrix = glm::ortho(-20.0f, 20.0f, -15.0f, 15.0f, -10.0f, 30.0f);
//    depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0.0f, 0.0f, 0.0001f), glm::vec3(0.0, 1.0, 0.0));
//    depthVP = depthProjectionMatrix * depthViewMatrix;
    depthProjectionMatrix = glm::ortho(-20.0f, 20.0f, -15.0f, 15.0f, -10.0f, 30.0f);
    depthViewMatrix = glm::lookAt(vec3(05,10,10), glm::vec3(0.0f, 0.0f, 0.0001f), glm::vec3(0.0, 1.0, 0.0));
    depthVP = depthProjectionMatrix * depthViewMatrix;

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    Shader * simpleDepthShader;
    simpleDepthShader = ShaderLibrary::GetsimpleDepthShader();

    ///ana msh 3amel load shadow fi el draw , we mynfa3sh a3ml mrteen fa ya hna ya hnak fl debug
    simpleDepthShader->LoadShader("ShadowMapping", "simpleDepthShader.vertexshader" , "simpleDepthShader.fragmentshader");
    simpleDepthShader->Use();  //lazem a3ml use abl mab3at ai 7aga , fa 3adi h3ml use hena
    simpleDepthShader->SendUniform("depthVP", depthVP);

}
