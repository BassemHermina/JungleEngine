#include <iostream>

#include <GL/glew.h>
#include<hierarchy/hierarchy.hpp>
// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "includes.hpp"
//#include "Handles.hpp" ma3mollo include Hierarchy.hpp->monobehaviour.hpp->handles


int initializeGL();
void lightControls();
Handles OPENGLTAGS;
float x = 200;
void initialPlacingObjects();
using namespace std;

int main(void)
{
    initializeGL();

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


    do{
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(OPENGLTAGS.Shader_ProgramID);

        //dlwa2ty ana bandah kol draw function bta3et
        //el objects el gowa el Bucket, wel draw di nafsaha m3mola function fl
        //MonobehaviourClass , we da mmkn y3ml moshkla en yb2a fi object lih draw btri2a mo5tlfa
        //sa3etha hab2a a7lha b eni a3ml wa7da virtual , aw btri2aten ma hasib draw el mono
        //we ha3ml draw bta3et el object nafso
        //edit:
        //hya asln virtual dlwa2ty , fa lw ha3mlha coverup ha3ml implmentation lel draw el gdida gowa l object b2a
        GameObjects_Bucket->draw();

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
    glfwSetMousePos(1024/2, 768/2);

    // light blue background
    glClearColor(0.0f, 0.682352f, 0.933333f, 0.0f); //yaslaam yaro7 5altak :D
    // msh bya5od fraction "238/255" bs bya5od el float bta3ha "0.93333f" bs

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    // Create and compile our GLSL program from the shaders
    OPENGLTAGS.Shader_ProgramID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );

    // Get a handle for our "MVP" uniform
    OPENGLTAGS.Shader_MVPMatrixID = glGetUniformLocation(OPENGLTAGS.Shader_ProgramID, "MVP");
    OPENGLTAGS.Shader_ViewMatrixID = glGetUniformLocation(OPENGLTAGS.Shader_ProgramID, "V");
    OPENGLTAGS.Shader_ModelMatrixID = glGetUniformLocation(OPENGLTAGS.Shader_ProgramID, "M");

    //Needed for requirement 1
    OPENGLTAGS.Shader_p = glGetUniformLocation(OPENGLTAGS.Shader_ProgramID, "LightPower");

    //Needed for requirement 2
    OPENGLTAGS.Shader_rr = glGetUniformLocation(OPENGLTAGS.Shader_ProgramID, "r");
    OPENGLTAGS.Shader_gg = glGetUniformLocation(OPENGLTAGS.Shader_ProgramID, "g");

    // Get a handle for our buffers
    OPENGLTAGS.Shader_vertexPosition_modelspaceID = glGetAttribLocation(OPENGLTAGS.Shader_ProgramID, "vertexPosition_modelspace");
    OPENGLTAGS.Shader_vertexUVID = glGetAttribLocation(OPENGLTAGS.Shader_ProgramID, "vertexUV");
    OPENGLTAGS.Shader_vertexNormal_modelspaceID = glGetAttribLocation(OPENGLTAGS.Shader_ProgramID, "vertexNormal_modelspace");

    // Get a handle for our "myTextureSampler" uniform
    OPENGLTAGS.Shader_TextureID = glGetUniformLocation(OPENGLTAGS.Shader_ProgramID, "myTextureSampler");


    glUseProgram(OPENGLTAGS.Shader_ProgramID);  //use programm must come before the next lines
    // switching the order caused some color distortions!



    glm::vec3 lightPos = glm::vec3(0,40,0);  // only effects the shadow direction
                                               // it don't effect light intensity , check fragment shader edited
    OPENGLTAGS.Shader_LightID = glGetUniformLocation(OPENGLTAGS.Shader_ProgramID, "LightPosition_worldspace");
    glUniform3f(OPENGLTAGS.Shader_LightID, lightPos.x, lightPos.y, lightPos.z);



    glUniform1f(OPENGLTAGS.Shader_p,x);

    glShadeModel(GL_SMOOTH); //bassem edit
}


Handles getOPENGLTAGS ()
{
    return OPENGLTAGS;
}


void lightControls(){

    if ( glfwGetKey( GLFW_KEY_LSHIFT ) == GLFW_PRESS)
        x = x + 3;
    if ( glfwGetKey( GLFW_KEY_LCTRL ) == GLFW_PRESS)
        x = x -3;
    glUniform1f(OPENGLTAGS.Shader_p,x);

}

void initialPlacingObjects()
{

}
