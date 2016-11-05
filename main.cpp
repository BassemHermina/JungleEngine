#include <iostream>

#include <GL/glew.h>
#include<hierarchy/hierarchy.hpp>
// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "includes.hpp"


int initializeGL();

Handles OPENGLTAGS;

using namespace std;

int main(void)
{
    //BH: this should be a class that inherits from the monoBehaviorClass, so we will be able to add it to the system
    //monobehaviorClass mon;

    //initialize GL window
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
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
    //////////////////////
    // da test le t7rik object suzanne 2
    glm::mat4 RotationMatrix = eulerAngleYXZ(0.0f, 0.0f, 2.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix = translate(mat4(), vec3(6.0f, 0.0f, 0.0f));
    glm::mat4 ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 Model = TranslationMatrix*RotationMatrix * ScalingMatrix;//order of multiplication is important (try different values above and different order of multiplicationn
    Suzanne2.ModelMatrix = Suzanne2.ProjectionMatrix * Suzanne2.ViewMatrix * (Suzanne2.ModelMatrix + Model) ;
    //
    glm::mat4 RotationMatrix2 = eulerAngleYXZ(0.0f, 0.0f, 1.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix2 = translate(mat4(), vec3(-20.0f, 5.0f, 0.0f));
    glm::mat4 ScalingMatrix2 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 Model2 = TranslationMatrix2*RotationMatrix2 * ScalingMatrix2;//order of multiplication is important (try different values above and different order of multiplicationn
    Suzanne3.ModelMatrix = Suzanne2.ProjectionMatrix * Suzanne2.ViewMatrix * (Suzanne2.ModelMatrix + Model2) ;
    //
    glm::mat4 RotationMatrix3 = eulerAngleYXZ(0.0f, 0.0f, 0.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix3 = translate(mat4(), vec3(6.0f, 3.0f, 10.0f));
    glm::mat4 ScalingMatrix3 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 Model3 = TranslationMatrix3*RotationMatrix3 * ScalingMatrix3;//order of multiplication is important (try different values above and different order of multiplicationn
    Suzanne4.ModelMatrix = Suzanne2.ProjectionMatrix * Suzanne2.ViewMatrix * (Suzanne2.ModelMatrix + Model3) ;
    //
    glm::mat4 RotationMatrix4 = eulerAngleYXZ(0.0f,-1.0f, 0.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix4 = translate(mat4(), vec3(6.0f, -4.0f, 0.0f));
    glm::mat4 ScalingMatrix4 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 Model4 = TranslationMatrix4 *RotationMatrix4 * ScalingMatrix4;//order of multiplication is important (try different values above and different order of multiplicationn
    Suzanne5.ModelMatrix = Suzanne2.ProjectionMatrix * Suzanne2.ViewMatrix * (Suzanne2.ModelMatrix + Model4) ;
    //
    glm::mat4 RotationMatrix5 = eulerAngleYXZ(0.0f, -5.0f, 2.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix5 = translate(mat4(), vec3(6.0f, 0.0f, 9.0f));
    glm::mat4 ScalingMatrix5 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 Model5 = TranslationMatrix5 *RotationMatrix5 * ScalingMatrix5;//order of multiplication is important (try different values above and different order of multiplicationn
    Suzanne6.ModelMatrix = Suzanne2.ProjectionMatrix * Suzanne2.ViewMatrix * (Suzanne2.ModelMatrix + Model5) ;
    //
    glm::mat4 RotationMatrix6 = eulerAngleYXZ(0.0f, 0.0f, 1.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix6 = translate(mat4(), vec3(-3.0f, 2.0f, 0.0f));
    glm::mat4 ScalingMatrix6 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 Model6 = TranslationMatrix6 *RotationMatrix6 * ScalingMatrix6;//order of multiplication is important (try different values above and different order of multiplicationn
    Shell.ModelMatrix = Shell.ProjectionMatrix * Shell.ViewMatrix * (  Model6) ;
    //






    //add the game objects to the list
    GameObjects_Bucket->add(&Suzanne);


  do{
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(OPENGLTAGS.ProgramIDHandle);

        Suzanne.draw();  // l controls bta3t l camera msh sh3'ala
        Suzanne2.draw();
        Suzanne3.draw();
        Suzanne4.draw();
        Suzanne5.draw();
        Suzanne6.draw();

        Shell.draw();
     // Swap buffers
     glfwSwapBuffers();


    }

  while(
        glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
        glfwGetWindowParam( GLFW_OPENED )
        );

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
    OPENGLTAGS.ProgramIDHandle = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );

    // Get a handle for our "MVP" uniform
    OPENGLTAGS.MatrixIDHandle = glGetUniformLocation(OPENGLTAGS.ProgramIDHandle, "MVP");

    // Get a handle for our buffers
    OPENGLTAGS.vertexPosition_modelspaceIDHandle = glGetAttribLocation(OPENGLTAGS.ProgramIDHandle, "vertexPosition_modelspace");
    OPENGLTAGS.vertexUVIDHandle = glGetAttribLocation(OPENGLTAGS.ProgramIDHandle, "vertexUV");

    // Get a handle for our "myTextureSampler" uniform
    OPENGLTAGS.TextureIDHandle  = glGetUniformLocation(OPENGLTAGS.ProgramIDHandle, "myTextureSampler");


}


Handles getOPENGLTAGS ()
{
    return OPENGLTAGS;
}
