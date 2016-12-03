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

int initializeGL();
void lightControls_Phong();
float x = 200;
using namespace std;
void renderfromTexture(GLuint TextureIDtobesampled);

glm::mat4 biasMatrix(
0.5, 0.0, 0.0, 0.0,
0.0, 0.5, 0.0, 0.0,
0.0, 0.0, 0.5, 0.0,
0.5, 0.5, 0.5, 1.0
);



int main(void)
{
    initializeGL();
    //ShaderLibrary::initializeShaders();

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

    //BH: the GameObjects_Bucket is the Datastructure that holds all the game objects with inherit from monobehavior
    //hierarchy *GameObjects_Bucket= new hierarchy;

    //GameObjects
    //SuzanneClass Suzanne;
    //SuzanneClass Suzanne2;
    /*SuzanneClass Suzanne3;
    SuzanneClass Suzanne4;
    SuzanneClass Suzanne5;
    SuzanneClass Suzanne6;*/
    //ShellClass Shell;
   // PlaneClass Plane;

    //add the game objects to the list
    //GameObjects_Bucket->add(&Suzanne);
    //GameObjects_Bucket->add(&Suzanne2);
    /*GameObjects_Bucket->add(&Suzanne3);
    GameObjects_Bucket->add(&Suzanne4);
    GameObjects_Bucket->add(&Suzanne5);
    GameObjects_Bucket->add(&Suzanne6);*/
    //GameObjects_Bucket->add(&Shell);
    //GameObjects_Bucket->add(&Plane);


    //initialize world
    //GameObjects_Bucket->init();

    // note: lma b5ali el ambient a2al btb2a eda2a tab3ya shoia aktr , el hwa lma adalemha 5ales el dnia btswad , msh zy di keda , kol
    //ma3ali ambient btb2a flat shading

    // light blue background
    glClearColor(0.0f, 0.682352f, 0.933333f, 0.0f); //yaslaam yaro7 5altak :D
    // msh bya5od fraction "238/255" bs bya5od el float bta3ha "0.93333f" bs

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    // must be created before shadowmapping
    Shadow ShadowObject;
    ShadowObject.initialize();  //calls the constructor only till now

    SkyBox WORLDreal;
    WORLDreal.InitReal();

    SkyBox WorldBlurry;
    WorldBlurry.InitBlurry();

    Maze m;
    SuzanneClass harry;
    harry.Translate(17.9875f,0.48537f,-19.98861f);
    harry.Rotate(0,180,0);





    do{

        WORLDreal.clearThenDraw();

        ///RenderShadowMap to FB////
        ShadowObject.PreRenderShadowMap();
        //GameObjects_Bucket->drawDepthMap();
        m.drawDepthMap();
        harry.drawDepthMap();

        ///RenderScene to screen////
        glBindFramebuffer(GL_FRAMEBUFFER, 0);  //return back to default buffer which is rendered to the screen
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
        //renderfromTexture(depthTexture);

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

}


void renderfromTexture(GLuint TextureIDtobesampled)
{

    glBindFramebuffer(GL_FRAMEBUFFER, 0);  //return back to default buffer which is rendered to the screen
    glViewport(0,0,1024,768);
    glClearColor(0.0f, 0.682352f, 0.933333f, 0.0f); //yaslaam yaro7 5altak :D
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static const GLfloat g_quad_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
    };

    static const GLfloat g_quad_uv_buffer_data[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };

    Shader * TextToScreen;
    TextToScreen = ShaderLibrary::GetTexToScreen();
    TextToScreen->LoadShader("textureShader", "TexturetoScreen.vertexshader", "TexturetoScreen.fragmentshader");

    TextToScreen->Use();

    //it uses gltexture 2
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, TextureIDtobesampled);
    TextToScreen->SendUniform("myTextureSampler", 2);
    glActiveTexture(GL_TEXTURE0);

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
