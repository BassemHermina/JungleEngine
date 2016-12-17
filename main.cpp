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
#include "Physx/BoundingBox.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

#include <ctime>
float rotation  = 0;
int initializeGL();
void lightControls_Phong();
float x = 1800;
using namespace std;
void renderfromTexture(GLuint TextureIDtobesampled);
void RenderMessage(GLuint TextureIDtobesampled);
void renderfromTextureandDepth(GLuint TextureIDtobesampled, GLuint DepthtextureID);
bool noEnter = false;
bool win = false;
glm::mat4 biasMatrix(
0.5, 0.0, 0.0, 0.0,
0.0, 0.5, 0.0, 0.0,
0.0, 0.0, 0.5, 0.0,
0.5, 0.5, 0.5, 1.0
);

glm::vec3 Hposition = glm::vec3(18.6875f,0.82537f ,-15 );
float Hwalkspeed = 1.0f;


void MoveHarry(Bounding_box* h, Maze* m);
void AnimateHarry(int, Harryframes HarryAnim );
int collisionDetect(Bounding_box* h, Maze* m,glm::vec3 offset);
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
    //SuzanneClass Suzanne;


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
    //createMazeBboxes(); //hardcoded number of objects
    Bounding_box MazePart47(m.maze[47]);

    /// Bbox params , arround one object of harry animation objects
    SuzanneClass harry;

    SuzanneClass suzanne;
    suzanne.Scale(10,10,10);
    Bounding_box Harry_Bbox (&harry);
    harry.Translate(18.6875f,0.48537f ,-15);
    //harry.Rotate(,90,0);
    harry.Scale(0.25,0.25,0.25);

    //================================================================

    ///////////////////////////////////////////////////////////////
    ///post processing's tazbit
    GLuint PPFB;
    glGenFramebuffers(1,&PPFB);
    glBindFramebuffer(GL_FRAMEBUFFER, PPFB);
    cout << PPFB << endl;
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

     GLuint Loading1Tex;
     Loading1Tex = loadBMP_custom("Splash/Loading1.bmp");
     renderfromTexture(Loading1Tex);
     glfwSwapBuffers();

     GLuint SPlashTex;
     SPlashTex = loadBMP_custom("Splash/splash_shfaf.bmp");
     /////////////////////music///////////////
     sf::Music intro;
     if(!intro.openFromFile("final/intro.ogg"))
         cout<<"music error"<<endl;
     intro.setVolume(100);
     intro.setLoop(true);
     intro.play();
     intro.setPlayingOffset(sf::seconds(3));

     sf::Music game;
     if(!game.openFromFile("final/final.ogg"))
         cout<<"music error"<<endl;
     game.setVolume(100);
     game.setLoop(true);






//     renderfromTexture(SPlashTex);
    ///////////////////////////////////////////////////////////////
    /// Animation's tazbit
    Harryframes HarryAnim;
    //Harryframes HarryStanding;

    HarryAnim.loadAnimation();

    //Bounding_box HarryPotterAnim_Bbox(&HarryAnim);

    HarryAnim.Scale(0.23,0.23,0.23);
    HarryAnim.Translate(Hposition.x+0.4, Hposition.y, Hposition.z);
    int dumdum = 0;
    //HarryAnim.Rotate(80,80,0); //el objects nfsaha fi 7aga 3'ala fl origin bta3ha , akid msh byrotat-o
    // 3ala blender , eb2a garab
    ///////////////////////////////////////////////////////////////


    //================================================================

 do{
        HarryAnim.updateModelMatrix();
        harry.updateModelMatrix();
        MoveHarry(&Harry_Bbox , &m);

        //cout << Hposition.z << endl;

        harry.Translate(Hposition.x, Hposition.y, Hposition.z); ///NEW!!: this one has the Bbox arrounnd it
        harry.Rotate(0,rotation,0);
        HarryAnim.Translate(Hposition.x, Hposition.y, Hposition.z);
      //  HarryAnim.Rotate(0,rotation,0);

        WORLDreal.clearThenDraw(0 );


        ///RenderShadowMap to FB////
        suzanne.Scale(0.25,0.25,0.25);
        suzanne.Translate(Hposition.x/1.48, 10, Hposition.z/10);
        ShadowObject.PreRenderShadowMap();
        //GameObjects_Bucket->drawDepthMap();
        // Enable Those to Draw shadows
        // byt3mlo clear mara we yfdal msh mwgood , msh bytrsem tani leeh ?!!!
        glBindFramebuffer(GL_FRAMEBUFFER, ShadowObject.fb);
        //glClearColor( 0.5f, 0.5f, 0.5f, 0.0f );// da mlosh lazma, hwa keda keda 3aref hya5od a mn el rasma  , el background mlhash lazma
        //glClearDepth(0.5f); //debugging
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glCullFace(GL_FRONT);
        //m.drawDepthMap();
        suzanne.drawDepthMap();

        harry.drawDepthMap();


        //================================================================

        ///RenderScene to screen////
        /// to render to screen , disable the RenderfromTexture function, and enable framebuffer0 here, put 0 in WorldREAL.clearthendraw
        ///glBindFramebuffer(GL_FRAMEBUFFER, 0);  //return back to default buffer which is rendered to the screen

        /// render to PP-FRAMEBUFFER
        // hna lazm a2olo el clear color we clear we est5dem depth test
        // 3ashan ana lma oltohom abl keda kano 3la buffer tani (0)
        glBindFramebuffer(GL_FRAMEBUFFER,0 );
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

        /// for proper Bbox , comment this draw function and put asd_0001 in suzanne class object file
        //harry.drawPhong();  /// da el bst5dmo 3ashan a7ot el bounding box 7waleh
        /// 3ashan da by-inherit mn Monobehaviour, badal ma - a handle eni ast5dem
        /// el bounding box m3 class harry frames we ydrab fi weshi
        Harry_Bbox.draw();
        //MazePart47.draw2();

        // Bassem NEW : ana zawedt gowa class el maze , array fiha el bounding boxes, we 3amaltlha new m3
        // load el objects nfsaha , geet arsmha gowa 3amal crash , grabt arsmha hena esht3'let ,msh 3aref leeh we mkasel afkar
        //3'aleban el 3adad kan zyada
        // la2 tle3 3ashan lw 7atet zero byedrab msh 3aref leeh b2a
        // fi 7aga fi element 0 fl array , fl data bta3to
        ///d5altha gowa 5las fl maze weesht3'alet , el error kan fi 0 bas!

        //HarryPotterAnim_Bbox.draw();
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
        glm::mat4 ProjectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 200.0f); //was only 100
                // Camera matrixs
                glm::mat4 ViewMatrix       = glm::lookAt(
                                           glm::vec3(Hposition.x - 3.5476 * sin(rotation) , 2.84254 ,Hposition.z - 3.5476 * cos(rotation)) ,           // Camera is here
                                           glm::vec3(Hposition.x,(Hposition.y)+0.6 ,Hposition.z), // and looks here : at the same position, plus "direction"
                                           glm::vec3(0,1,0)                  // Head is up (set to 0,-1,0 to look upside-down)
                                       );
                //glm::vec3 Hposition = glm::vec3(18.6875f,0.82537f ,-15 );
        //cout<<" rotat: "<< rotation*56<<endl;
                HarryAnim.Rotate(0,rotation*56,0);
            //cout << Hposition.z <<endl;
            setProjectionMatrix(ProjectionMatrix);
            setViewMatrix(ViewMatrix);

        /////////////////////////////////////////////////
        // Post Processing
        //renderfromTexture(Suzanne.texture);
        //renderfromTexture(ShadowObject.texture);
        //renderfromTexture(texColorBuffer);
        //renderfromTextureandDepth( texColorBuffer, texDepthBuffer );

        ///////////////////render messages here
        ////////////////////////////////////
        // Enable blending
       // glEnable (GL_BLEND);
        GLuint Hog;
        Hog = loadBMP_custom("Splash/Hog.bmp");

        RenderMessage(Hog);

        if (glfwGetKey( GLFW_KEY_ENTER ) == GLFW_PRESS){
            noEnter = true;
            intro.stop();
            game.play();
        }

        if (glfwGetKey( GLFW_KEY_F5 ) == GLFW_PRESS){
            Hposition.x = -18.6057;
            Hposition.z = 9.81772;

        }
        if (!noEnter) renderfromTexture(SPlashTex);


////    GameObjects_Bucket->drawDepthMap();

        lightControls_Phong();

        //renderfromTexture(Suzanne2.getTextureSamplerIDtoBind());
        if (Hposition.x <= -19.6057)
        {
           win = true;
        }


        // Swap buffers
        glfwSwapBuffers();

    }

  while(
        glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
        glfwGetWindowParam( GLFW_OPENED ) && !win
        );
  while (glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
          glfwGetWindowParam( GLFW_OPENED ) && win)
  {
    GLuint Hogwarts;
    Hogwarts = loadBMP_custom("Splash/Hog.bmp");
    renderfromTexture(Hogwarts);
    glfwSwapBuffers();
    game.stop();

  }

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
    glClearColor(0,0,0,0); //yaslaam yaro7 5altak :D
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


void RenderMessage(GLuint TextureIDtobesampled)
{

    glBindFramebuffer(GL_FRAMEBUFFER, 0);  //return back to default buffer which is rendered to the screen
    glViewport(0,0,1024,768);
    //glClearColor(0,0,0,0); //yaslaam yaro7 5altak :D
    glClear(GL_DEPTH_BUFFER_BIT);

    static const GLfloat g_quad_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.f,
        -1.0f,  1.0f, 0.f,
        -1.0f,  1.0f,0.f,
        1.0f, -1.0f,0.f,
        1.0f,  1.0f, 0.f,
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

    Shader * MessageShader;
    MessageShader = ShaderLibrary::GetMessagesShader();
    MessageShader->LoadShader("MessagesShader", "MessagesShader.vert", "MessagesShader.frag");

    MessageShader->Use();
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_ONE, GL_ONE); // additive blending

    // mmkn azawed el depth msln wafta7 el depth test , a5ali el Z bta3to b rkam msln waagarab



    //it uses gltexture 2
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, TextureIDtobesampled);

    // some fixes for transperency , btshil el alwan mn el 7edood
    //https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/discard.php
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    MessageShader->SendUniform("myTextureSampler", 2);
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
    glEnableVertexAttribArray(MessageShader->Attribute("vertex_screenspace"));
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glVertexAttribPointer(
        MessageShader->Attribute("vertex_screenspace"),  // The attribute we want to configure
        3,                            // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(MessageShader->Attribute("vertexUV"));
    glBindBuffer(GL_ARRAY_BUFFER, quad_uvbuffer);
    glVertexAttribPointer(
        MessageShader->Attribute("vertexUV"),                   // The attribute we want to configure
        2,                            // size : U+V => 2
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, 6); // 12*3 indices starting at 0 -> 12 triangles
    glDisableVertexAttribArray(MessageShader->Attribute("vertex_screenspace"));
    glDisableVertexAttribArray(MessageShader->Attribute("vertexUV"));
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

void MoveHarry( Bounding_box* h , Maze *m)
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

        glm::vec3 offset =vec3(0.0167*sin(rotation),0.0,0.0167*cos(rotation)) * Hwalkspeed;
        int index=collisionDetect(h ,m,offset );


     if (index)
     {
         //Hposition =  Hposition +  vec3(0.0,0.0,1.0) * deltaTime * Hwalkspeed;
         Hposition =  Hposition +  vec3(0.0167*sin(rotation),0.0,0.0167*cos(rotation)) * Hwalkspeed;
     }
     if(index==53||index==54)
     {m->maze[53]->Translate(200.0f,200.0f,200.0f);
     m->maze[54]->Translate(200,200,200);//hanawar makano
     }
     if(index==55||index==56)
     {m->maze[55]->Translate(200,200,200);
     m->maze[56]->Translate(200,200,200);//hanawar makano
     }
     if(index==59||index==60)
     {m->maze[59]->Translate(200,200,200);
     m->maze[60]->Translate(200,200,200);//hanawar makano
     }
     if(index==57)
     {
     m->maze[57]->Translate(200,200,200);//hanawar makano
     }
     if(index==58)
     {
     m->maze[58]->Translate(200,200,200);//hanawar makano
     }






    }
    // Move backward
    if ( glfwGetKey( GLFW_KEY_s ) == GLFW_PRESS){
       glm::vec3 offset =vec3(-0.0167*sin(rotation),0.0,-0.0167*cos(rotation)) * Hwalkspeed;

        int index=collisionDetect(h ,m,offset );

        //Hposition =  Hposition +  vec3(0.0,0.0,-1.0) * deltaTime * Hwalkspeed;
        if (index){

        Hposition =  Hposition- vec3(0.0167*sin(rotation),0.0,0.0167*cos(rotation)) * Hwalkspeed;
        }
        if(index==53||index==54)
        {m->maze[53]->Translate(200,200,200);
        m->maze[54]->Translate(200,200,200);//hanawar makano
        }
        if(index==55||index==56)
        {m->maze[55]->Translate(200,200,200);
        m->maze[56]->Translate(200,200,200);//hanawar makano
        }
        if(index==59||index==60)
        {m->maze[59]->Translate(200,200,200);
        m->maze[60]->Translate(200,200,200);//hanawar makano
        }
        if(index==57)
        {
        m->maze[57]->Translate(200,200,200);//hanawar makano
        }
        if(index==58)
        {
        m->maze[58]->Translate(200,200,200);//hanawar makano
        }
    }
    // Strafe right
    if (glfwGetKey( GLFW_KEY_d ) == GLFW_PRESS){
        //glm::vec3 offset=vec3(-0.0167,0.0,0.0)  * Hwalkspeed;
        rotation= rotation -0.08;
       /* int index=collisionDetect(h ,m,offset );

        //rotation = rotation - 3;
        if (index)
        {
          //Hposition =  Hposition -  vec3(0.0167,0.0,0.0)  * Hwalkspeed;
        }
        if(index==53||index==54)
        {m->maze[53]->Translate(200,200,200);
        m->maze[54]->Translate(200,200,200);//hanawar makano
        }
        if(index==55||index==56)
        {m->maze[55]->Translate(200,200,200);
        m->maze[56]->Translate(200,200,200);//hanawar makano
        }
        if(index==59||index==60)
        {m->maze[59]->Translate(200,200,200);
        m->maze[60]->Translate(200,200,200);//hanawar makano
        }
        if(index==57)
        {
        m->maze[57]->Translate(200,200,200);//hanawar makano
        }
        if(index==58)
        {
        m->maze[58]->Translate(200,200,200);//hanawar makano
        }*/
    }
    // Strafe left
    if (glfwGetKey( GLFW_KEY_a ) == GLFW_PRESS){
        glm::vec3 offset=vec3(0.0167,0.0,0.0)  * Hwalkspeed;
        //int index=collisionDetect(h ,m,offset );

        rotation = rotation + 0.08;
        /*
        if (index)
        {
          Hposition =  Hposition +  vec3(0.0167,0.0,0.0)  * Hwalkspeed;
        }
        if(index==53||index==54)
        {m->maze[53]->Translate(200,200,200);
        m->maze[54]->Translate(200,200,200);//hanawar makano
        }
        if(index==55||index==56)
        {m->maze[55]->Translate(200,200,200);
        m->maze[56]->Translate(200,200,200);//hanawar makano
        }
        if(index==59||index==60)
        {m->maze[59]->Translate(200,200,200);
        m->maze[60]->Translate(200,200,200);//hanawar makano
        }
        if(index==57)
        {
        m->maze[57]->Translate(200,200,200);//hanawar makano
        }
        if(index==58)
        {
        m->maze[58]->Translate(200,200,200);//hanawar makano
        }*/
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

int collisionDetect(Bounding_box* h, Maze* m,glm::vec3 offset){

//h->UpdateLocationWithObject();

//cout << "Harry_z_min&max: " <<  h->upMinZvec.z <<" " << h->upMaxZvec.z << endl;
//cout << "Harry_x_min&max: " <<  h->upMinXvec.x <<" " << h->upMaxXvec.x << endl;
//cout << "Maze_z min&max: " << m->mazeBboxes[6]->upMinZvec.z << " " << m->mazeBboxes[6]->upMaxZvec.z << endl;
//cout << "Maze_x min&max: " << m->mazeBboxes[6]->upMinXvec.x << " " << m->mazeBboxes[6]->upMaxXvec.x << endl;

    for (int i =1; i<61 ; i++)
    {

        bool n = (h->upMinXvec.x+offset.x<=m->mazeBboxes[i]->upMaxXvec.x && h->upMaxXvec.x +offset.x>= m->mazeBboxes[i]->upMinXvec.x)&& (h->upMinZvec.z+offset.z<=m->mazeBboxes[i]->upMaxZvec.z && h->upMaxZvec.z+offset.z >= m->mazeBboxes[i]->upMinZvec.z); //(h->upmin.x<=m->mazeBboxes[i]->upmax.x && h->upmax.x >= m->mazeBboxes[i]->upmin.x  )

        if (n)
        {   //cout << i << endl;
            //if it was a horecrux, return it's number , else, return 0
             if (i>=53&&i<=60) return i;
            return 0 ; // m3naha eno hassal collision

        }
   }
return 1 ;


}
