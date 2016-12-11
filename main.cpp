#include <iostream>

#include <GL/glew.h>
#include<hierarchy/hierarchy.hpp>
// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <includes.hpp>

#include <shaderlibrary.h>
#include "Shaders.hpp"
#include <shaderlibrary.h>
#include "SkyBoxes/SkyBox.hpp"
#include "helpers/Shadows.hpp"
#include "Maze/Maze.hpp"

#include <ctime>
float rotation  = 0;
int initializeGL();
void lightControls_Phong();
float x = 1800;
using namespace std;
void renderfromTexture(GLuint TextureIDtobesampled);
void renderfromTextureandDepth(GLuint TextureIDtobesampled, GLuint DepthtextureID);

glm::mat4 biasMatrix(
0.5, 0.0, 0.0, 0.0,
0.0, 0.5, 0.0, 0.0,
0.0, 0.0, 0.5, 0.0,
0.5, 0.5, 0.5, 1.0
);

glm::vec3 Hposition = glm::vec3(18.6875f,0.48537f ,-15 );
float Hwalkspeed = 1.0f;


void MoveHarry();
void AnimateHarry(int, Harryframes HarryAnim);

int main(void)
{
    initializeGL();

    Shader * PhongShader;
    PhongShader = ShaderLibrary::GetPhongShader();
    PhongShader->Use();

    Shader * simpleDepthMap;
    simpleDepthMap = ShaderLibrary::GetsimpleDepthShader();

    Shader * TextToScreen;
    TextToScreen = ShaderLibrary::GetTexToScreen();

    Shader * cubeMapShader;
    cubeMapShader = ShaderLibrary::GetcubeMapShader();
    cubeMapShader->LoadShader("cubeMapShader" , "skybox.vs" , "skybox.frag");

    //==============================================================

    //BH: the GameObjects_Bucket is the Datastructure that holds
    //all the game objects with inherit from monobehavior
    //hierarchy *GameObjects_Bucket= new hierarchy;

    //GameObjects
    SuzanneClass Suzanne;

    //add the game objects to the list
    //GameObjects_Bucket->add(&Suzanne);

    // light blue background
    glClearColor(0.0f, 0.682352f, 0.933333f, 0.0f);
    // msh bya5od fraction "238/255" bs bya5od el float bta3ha "0.93333f" bs

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    //==============================================================

    // must be created before shadowmapping
    Shadow ShadowObject;
    ShadowObject.initialize();  //calls the constructor only till now

    SkyBox WORLDreal;
    WORLDreal.InitReal();

    SkyBox WorldBlurry;
    WorldBlurry.InitBlurry();

    Maze m;
    SuzanneClass harry;
    harry.Translate(17.9875f,0.48537f,-15);
    harry.Rotate(0,180,0);
    harry.Scale(0.25,0.25,0.25);

    //================================================================

    ///////////////////////////////////////////////////////////////
    ///post processing's tazbit
    GLuint PPFB;
    glGenFramebuffers(1,&PPFB);
    glBindFramebuffer(GL_FRAMEBUFFER, PPFB);

    // Generate texture
    GLuint texColorBuffer;
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 1024, 768, 0, GL_BGR, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // Attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    // Generate texture
    // must be depth and stencil to work!
    GLuint texDepthBuffer;
    glGenTextures(1, &texDepthBuffer);
    glBindTexture(GL_TEXTURE_2D, texDepthBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 1024, 768, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // Attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,GL_TEXTURE_2D,texDepthBuffer, 0);

    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
       cout << "PP_FBO is Incomplete" << endl;
    else cout << "pp_FBO is complete" << endl;

    //bnrga3 lel default b3d ma n5las
    glBindTexture(GL_TEXTURE_2D, 0);
    ///////////////////////////////////////////////////////////////

    //================================================================

    ///////////////////////////////////////////////////////////////
    /// Animation's tazbit
    Harryframes HarryAnim;

    HarryAnim.loadAnimation();
    HarryAnim.Scale(0.23,0.23,0.23);
    HarryAnim.Translate(Hposition.x+0.4, Hposition.y, Hposition.z);
    int dumdum = 0;
 // HarryAnim.Rotate(80,80,0); el objects nfsaha fi 7aga 3'ala fl origin bta3ha , akid msh byrotat-o
    // 3ala blender , eb2a garab
    ///////////////////////////////////////////////////////////////

    //================================================================

    do{
        MoveHarry();
        //harry.Translate(Hposition.x, Hposition.y, Hposition.z);
        HarryAnim.Translate(Hposition.x, Hposition.y, Hposition.z);


        WORLDreal.clearThenDraw(PPFB);

        ///RenderShadowMap to FB////
        ShadowObject.PreRenderShadowMap();
        //GameObjects_Bucket->drawDepthMap();
        // Enable Those to Draw shadows
        m.drawDepthMap();
        harry.drawDepthMap();

        //================================================================

        ///RenderScene to screen////
        /// to render to screen , disable the RenderfromTexture function, and enable framebuffer0 here
        ///glBindFramebuffer(GL_FRAMEBUFFER, 0);  //return back to default buffer which is rendered to the screen

        /// render to PP-FRAMEBUFFER
        // hna lazm a2olo el clear color we clear we est5dem depth test
        // 3ashan ana lma oltohom abl keda kano 3la buffer tani (0)
        glBindFramebuffer(GL_FRAMEBUFFER,PPFB );
        //dol by7salo gowa el ClearThenDraw ( frambuffer ID )
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer now
        glEnable(GL_DEPTH_TEST);
        ///////////////////////

        PhongShader->Use();
        glCullFace(GL_BACK); //de momken t3ml moshkla
        glViewport(0,0,1024,768);
        //removed the clear 3ashan ba-clear abl marsem el cubemap, 3ashan mamsa7haash
        ///law 3'aiart tartib eni arsem el cubemap el awel lazem a7ot dol
        //glClearColor(0.0f, 0.682352f, 0.933333f, 0.0f); //yaslaam yaro7 5altak :D
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //send texture to framebuffer
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, ShadowObject.texture);
        PhongShader->SendUniform("shadowMap", 1);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_CUBE_MAP, WorldBlurry.skyboxTexture);
        PhongShader->SendUniform("skybox", 2);
        //PhongShader->SEND ( Model matrix inverse ) is done inside drawPhong for every object
        // as i can't find a function to calculate Model matrix in GLSL
        PhongShader->SendUniform("DepthVP", ShadowObject.depthVP); // el view projection da sabet , 3ashan ana msh b3'aiar mkan el light
        PhongShader->SendUniform("BiasMatrix", biasMatrix);
        PhongShader->SendUniform("cameraPos", getCameraPosition());
       // GameObjects_Bucket->drawPhong();
        m.drawPhong();
        harry.drawPhong();
        //================================================================

        if (glfwGetKey( GLFW_KEY_w ) == GLFW_PRESS){
            dumdum ++;

            AnimateHarry(dumdum, HarryAnim);
        }
        else {
            dumdum = 1;
            AnimateHarry(dumdum, HarryAnim);
        }

//        dumdum = dumdum % 69;
//        if (dumdum != 0 && dumdum != 70)
//            HarryAnim.draw(dumdum);
//        if (dumdum == 0)
//            HarryAnim.draw(1);


        //renderfromTexture(depthTexture);


        /////////////////////////////////////////////////
        // Post Processing
        //renderfromTexture(Suzanne.texture);
        //renderfromTexture(ShadowObject.texture);
        //renderfromTexture(texColorBuffer);
        renderfromTextureandDepth( texColorBuffer, texDepthBuffer );



////    GameObjects_Bucket->drawDepthMap();

        lightControls_Phong();

        //renderfromTexture(Suzanne2.getTextureSamplerIDtoBind());

        // Swap buffers
        glfwSwapBuffers();

    }

  while(
        glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
        glfwGetWindowParam( GLFW_OPENED )
        );

  // Close OpenGL window and terminate GLFW
  glfwTerminate();
    return 0;
}






//////////////////////////////////////////
//--------------------------------------
int initializeGL()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        return -1;
    }

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glfwSetWindowTitle( "Game" );

    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );
    glfwEnable(GLFW_STICKY_MOUSE_BUTTONS);
    glfwSetMousePos(1024/2, 768/2);


    // Create and compile our GLSL program from the shaders
    Shader * PhongShader;
    PhongShader = ShaderLibrary::GetPhongShader();
    PhongShader->LoadShader("Phong", "StandardShading.vertexshader", "StandardShading.fragmentshader" );
    PhongShader->Use();

    // switching the order caused some color distortions!
    /// 3ashan lazem a3ml use lel shader el awel akid abl mab3at ai 7aga , ya 7mar !
    GLint currentProgram = 0; //dummy value
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    cout << currentProgram << endl;

    // only effects the shadow direction
    // it don't effect light intensity , check fragment shader edited
    PhongShader->SendUniform("LightPosition_worldspace" , vec3(0,40,0));
    PhongShader->SendUniform("LightPower", x);

}

void lightControls_Phong(){

    Shader * PhongShader;
    PhongShader = ShaderLibrary::GetPhongShader();
    PhongShader->Use();

    if ( glfwGetKey( GLFW_KEY_LSHIFT ) == GLFW_PRESS)
        x = x + 3;
    if ( glfwGetKey( GLFW_KEY_LCTRL ) == GLFW_PRESS)
        x = x -3;
    PhongShader->SendUniform("LightPower", x);
    // 1780 for the darkening PP shader effect
    // normal shading is 480

}


void renderfromTexture(GLuint TextureIDtobesampled)
{

    glBindFramebuffer(GL_FRAMEBUFFER, 0);  //return back to default buffer which is rendered to the screen
    glViewport(0,0,1024,768);
    glClearColor(1,1,1,1); //yaslaam yaro7 5altak :D
    glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);

    static const GLfloat g_quad_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
    };

    static const GLfloat g_quad_uv_buffer_data[] = {
//        0.0f, 1.0f,
//        1.0f, 1.0f,
//        0.0f, 0.0f,
//        0.0f, 0.0f,
//        1.0f, 1.0f,
//        1.0f, 0.0f

//        //rotated
//        1.0f, 0.0f,
//        0.0f, 0.0f,
//        1.0f, 1.0f,
//        1.0f, 1.0f,
//        0.0f, 0.0f,
//        0.0f, 1.0f

        //fliped
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f



    };

    Shader * TextToScreen;
    TextToScreen = ShaderLibrary::GetTexToScreen();
    TextToScreen->LoadShader("textureShader", "TexturetoScreen.vertexshader", "TexturetoScreen.fragmentshader");

    TextToScreen->Use();
    glDisable(GL_DEPTH_TEST);

    //it uses gltexture 2
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, TextureIDtobesampled);
    TextToScreen->SendUniform("myTextureSampler", 2);
    //glActiveTexture(GL_TEXTURE0);

    GLuint quad_vertexbuffer;
    glGenBuffers(1, &quad_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint quad_uvbuffer;
    glGenBuffers(1, &quad_uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad_uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_uv_buffer_data), g_quad_uv_buffer_data, GL_STATIC_DRAW);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(TextToScreen->Attribute("vertex_screenspace"));
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glVertexAttribPointer(
        TextToScreen->Attribute("vertex_screenspace"),  // The attribute we want to configure
        3,                            // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(TextToScreen->Attribute("vertexUV"));
    glBindBuffer(GL_ARRAY_BUFFER, quad_uvbuffer);
    glVertexAttribPointer(
        TextToScreen->Attribute("vertexUV"),                   // The attribute we want to configure
        2,                            // size : U+V => 2
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, 6); // 12*3 indices starting at 0 -> 12 triangles
    glDisableVertexAttribArray(TextToScreen->Attribute("vertex_screenspace"));
    glDisableVertexAttribArray(TextToScreen->Attribute("vertexUV"));

}

void renderfromTextureandDepth(GLuint TextureIDtobesampled, GLuint DepthtextureID)
{

    glBindFramebuffer(GL_FRAMEBUFFER, 0);  //return back to default buffer which is rendered to the screen
    glViewport(0,0,1024,768);
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);

    static const GLfloat g_quad_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
    };

    static const GLfloat g_quad_uv_buffer_data[] = {


        //fliped
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f



    };

    Shader * TextToScreen;
    TextToScreen = ShaderLibrary::GetTexToScreen();
    TextToScreen->LoadShader("textureShader", "TexturetoScreen.vertexshader", "TexturetoScreen.fragmentshader");

    TextToScreen->Use();
    glDisable(GL_DEPTH_TEST);

    //it uses gltexture 2
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, TextureIDtobesampled);
    TextToScreen->SendUniform("myTextureSampler", 2);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, DepthtextureID);
    TextToScreen->SendUniform("DepthTex", 3);
    //glActiveTexture(GL_TEXTURE0);


    float r = ((double) rand() / (RAND_MAX));
    TextToScreen->SendUniform("random",r);
    //cout << r << endl;
            ///
//
    GLuint quad_vertexbuffer;
    glGenBuffers(1, &quad_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint quad_uvbuffer;
    glGenBuffers(1, &quad_uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad_uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_uv_buffer_data), g_quad_uv_buffer_data, GL_STATIC_DRAW);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(TextToScreen->Attribute("vertex_screenspace"));
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glVertexAttribPointer(
        TextToScreen->Attribute("vertex_screenspace"),  // The attribute we want to configure
        3,                            // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(TextToScreen->Attribute("vertexUV"));
    glBindBuffer(GL_ARRAY_BUFFER, quad_uvbuffer);
    glVertexAttribPointer(
        TextToScreen->Attribute("vertexUV"),                   // The attribute we want to configure
        2,                            // size : U+V => 2
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, 6); // 12*3 indices starting at 0 -> 12 triangles
    glDisableVertexAttribArray(TextToScreen->Attribute("vertex_screenspace"));
    glDisableVertexAttribArray(TextToScreen->Attribute("vertexUV"));

}

void MoveHarry()
{
    // thats how delta time is used

    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    //cout << "Last: " << lastTime << " Current: " << currentTime << " delta: " << deltaTime << endl;
    //if (deltaTime > 0.02) cout << "!!!" << endl;

    /// camera's delta time is different from the character's so they lag
    /// they move with different steps
    //I will have to parent one of them to the other ( give the other the exact
    // same steps, not re-calculate it)

    /// for now i will not use deltaTime

    if (glfwGetKey( GLFW_KEY_SPACE ) == GLFW_PRESS){
        Hwalkspeed = 5.0;
    }

    if (glfwGetKey( GLFW_KEY_SPACE ) == GLFW_RELEASE){
        Hwalkspeed = 1.0;
    }
    // glfwGetTime is called only once, the first time this function is called

    // Move forward
    if (glfwGetKey( GLFW_KEY_w ) == GLFW_PRESS){
        //Hposition =  Hposition +  vec3(0.0,0.0,1.0) * deltaTime * Hwalkspeed;
        Hposition =  Hposition +  vec3(0.0,0.0,0.0167) * Hwalkspeed;
    }
    // Move backward
    if ( glfwGetKey( GLFW_KEY_s ) == GLFW_PRESS){
        //position =  Hposition +  vec3(0.0,0.0,-1.0) * deltaTime * Hwalkspeed;
        Hposition =  Hposition +  vec3(0.0,0.0,-0.0167) * Hwalkspeed;
    }
    // Strafe right
    if (glfwGetKey( GLFW_KEY_d ) == GLFW_PRESS){
        rotation = rotation + 1;
    }
    // Strafe left
    if (glfwGetKey( GLFW_KEY_a ) == GLFW_PRESS){
        Hposition =  Hposition +  vec3(0.0167,0.0,0.0)  * Hwalkspeed;
    }
    lastTime = currentTime;
}

void AnimateHarry(int dumdum, Harryframes HarryAnim)
{
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    dumdum = deltaTime*1000/60 + dumdum* 1.7;  // .... + dumdum * speed;

    dumdum = dumdum % 69;
    if (dumdum != 0 && dumdum != 70)
        HarryAnim.draw(dumdum);
    if (dumdum == 0)
        HarryAnim.draw(1);

    lastTime = currentTime;
}
