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
#include "helpers/Shadows.hpp"

int initializeGL();
void lightControls();
float x = 200;
void initialPlacingObjects();
using namespace std;


int main(void)
{
    initializeGL();
    //ShaderLibrary::initializeShaders();

    Shader * PhongShader;
    PhongShader = ShaderLibrary::GetPhongShader();
    PhongShader->Use();

    Shader * simpleDepthMap;
    simpleDepthMap = ShaderLibrary::GetsimpleDepthShader();

    ///////////////////////////////////////
    /// \brief nrAttributes
    /// Offline LearnOpenGL.pdf tutorials
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    ///////////////////////////////////////

    cout << PhongShader->Program() << endl;
    //BH: the GameObjects_Bucket is the Datastructure that holds all the game objects with inherit from monobehavior
    hierarchy *GameObjects_Bucket= new hierarchy;

    //GameObjects
    SuzanneClass Suzanne;
    SuzanneClass Suzanne2;
    SuzanneClass Suzanne3;
    SuzanneClass Suzanne4;
    SuzanneClass Suzanne5;
    SuzanneClass Suzanne6;
    ShellClass Shell;
    PlaneClass Plane;

    //add the game objects to the list
    GameObjects_Bucket->add(&Suzanne);
    GameObjects_Bucket->add(&Suzanne2);
    GameObjects_Bucket->add(&Suzanne3);
    GameObjects_Bucket->add(&Suzanne4);
    GameObjects_Bucket->add(&Suzanne5);
    GameObjects_Bucket->add(&Suzanne6);
    GameObjects_Bucket->add(&Shell);
    GameObjects_Bucket->add(&Plane);

    //initialize world
    GameObjects_Bucket->init();

    // note: lma b5ali el ambient a2al btb2a eda2a tab3ya shoia aktr , el hwa lma adalemha 5ales el dnia btswad , msh zy di keda , kol
    //ma3ali ambient btb2a flat shading


    //////////////////////////
    //Shadow mapping


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
//    Shadow ShadowObject;  //calls the constructor only till now
    // ana gowa 3amalt load lel shader 5las, we foo2 5ales afashto

    do{
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        PhongShader->Use();
//       simpleDepthMap->Use();

        /////////////////////////////////////
        GameObjects_Bucket->drawPhong();

        lightControls();

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
//    PhongShader.Use();
    GLint currentProgram = 0; //dummy value
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    cout << currentProgram << endl;

    // only effects the shadow direction
    // it don't effect light intensity , check fragment shader edited
    PhongShader->SendUniform("LightPosition_worldspace" , vec3(0,40,0));
    PhongShader->SendUniform("LightPower", x);

}

void lightControls(){

    Shader * PhongShader;
    PhongShader = ShaderLibrary::GetPhongShader();

    if ( glfwGetKey( GLFW_KEY_LSHIFT ) == GLFW_PRESS)
        x = x + 3;
    if ( glfwGetKey( GLFW_KEY_LCTRL ) == GLFW_PRESS)
        x = x -3;
    PhongShader->SendUniform("LightPower", x);

}
