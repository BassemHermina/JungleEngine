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
void lightControls();
Handles OPENGLTAGS;
float x = 200;

using namespace std;

int main(void)
{
    //!! fi moshkla fi etgah el light ba3d el rotate ,y3ni zy el kan 3la learnopengl keda , lama by3ml rotate, source
    //! el noor byfdal zy ma howa, fa klohom ka2en el source bylef m3ahom keda

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
    PlaneClass lightplaceCube;

    //////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    //////////////////////
    ///

    glm::mat4 RotationMatrix7 = eulerAngleYXZ(0.0f, 0.0f, 0.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix7 = translate(mat4(), vec3(3.0f, 2.50f, 1.0f));  //3,4,1
    //! hena el moshkla el 7asla fl render , el alwan wel eda2a darba keda
    //! 3ashan el mfrod en el cube keda ben el objects asln wel noor , f lw 7rakt el object b3id btrga3 el eda2a tabi3ya

    // lma b5ali el ambient a2al btb2a eda2a tab3ya shoia aktr , el hwa lma adalemha 5ales el dnia btswad , msh zy di keda , kol
    //ma3ali ambient btb2a flat shading

    glm::mat4 ScalingMatrix7 = scale(mat4(), vec3(0.2f, 0.2f, 0.2f));
    glm::mat4 Model7 = TranslationMatrix7*RotationMatrix7 * ScalingMatrix7;//order of multiplication is important (try different values above and different order of multiplicationn
    lightplaceCube.ModelMatrix = Model7 ;

    glm::mat4 RotationMatrix0 = eulerAngleYXZ(0.0f, 0.0f, 0.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix0 = translate(mat4(), vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 ScalingMatrix0 = scale(mat4(), vec3(10.0f, 0.4f, 6.0f));
    glm::mat4 Model0 = TranslationMatrix0*RotationMatrix0 * ScalingMatrix0;//order of multiplication is important (try different values above and different order of multiplicationn
    Plane.ModelMatrix = Model0 ;

    // da test le t7rik object suzanne 2
    glm::mat4 RotationMatrix = eulerAngleYXZ(0.0f, 0.0f, 2.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix = translate(mat4(), vec3(6.0f, 0.0f, 0.0f));
    glm::mat4 ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 Model = TranslationMatrix*RotationMatrix; //* ScalingMatrix;//order of multiplication is important (try different values above and different order of multiplicationn
    Suzanne2.ModelMatrix = Model ;
    //
    glm::mat4 RotationMatrix2 = eulerAngleYXZ(0.0f, 0.0f, 1.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix2 = translate(mat4(), vec3(-20.0f, 5.0f, 0.0f));
    glm::mat4 ScalingMatrix2 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 Model2 = TranslationMatrix2*RotationMatrix2;// * ScalingMatrix2;//order of multiplication is important (try different values above and different order of multiplicationn
    Suzanne3.ModelMatrix =  Model2 ;
    //
    glm::mat4 RotationMatrix3 = eulerAngleYXZ(0.0f, 0.0f, 0.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix3 = translate(mat4(), vec3(6.0f, 3.0f, 10.0f));
    glm::mat4 ScalingMatrix3 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 Model3 = TranslationMatrix3*RotationMatrix3;// * ScalingMatrix3;//order of multiplication is important (try different values above and different order of multiplicationn
    Suzanne4.ModelMatrix = Model3 ;
    //
    glm::mat4 RotationMatrix4 = eulerAngleYXZ(0.0f,-1.0f, 0.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix4 = translate(mat4(), vec3(6.0f, -4.0f, 0.0f));
    glm::mat4 ScalingMatrix4 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 Model4 = TranslationMatrix4 *RotationMatrix4;// * ScalingMatrix4;//order of multiplication is important (try different values above and different order of multiplicationn
    Suzanne5.ModelMatrix =  Model4 ;
    //
    glm::mat4 RotationMatrix5 = eulerAngleYXZ(0.0f, -5.0f, 2.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix5 = translate(mat4(), vec3(6.0f, 0.0f, 9.0f));
    glm::mat4 ScalingMatrix5 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 Model5 = TranslationMatrix5 *RotationMatrix5;// * ScalingMatrix5;//order of multiplication is important (try different values above and different order of multiplicationn
    Suzanne6.ModelMatrix =  Model5 ;
    //
    glm::mat4 RotationMatrix6 = eulerAngleYXZ(0.0f, 0.0f, 1.0f);//yaw, pitch and roll. Measured in radians
    glm::mat4 TranslationMatrix6 = translate(mat4(), vec3(-3.0f, 2.0f, 0.0f));
    glm::mat4 ScalingMatrix6 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 Model6 = TranslationMatrix6 *RotationMatrix6;// * ScalingMatrix6;//order of multiplication is important (try different values above and different order of multiplicationn
    Shell.ModelMatrix = Model6;  // here i manipulate the model matrix
    // and in the update function in the draw in each object i used to set it to identity , da el kan m5alih myt7araksh
    //



    //add the game objects to the list
   // GameObjects_Bucket->add(&Suzanne);

    do{
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(OPENGLTAGS.Shader_ProgramID);

        Suzanne.draw();
        Suzanne2.draw();
        Suzanne3.draw();
        Suzanne4.draw();
        Suzanne5.draw();
        Suzanne6.draw();
        Plane.draw();
        Shell.draw();
        //lightplaceCube.draw();


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

void drawPlane(){

}
