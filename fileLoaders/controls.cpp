// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <iostream>
using namespace std;
#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}




// Initial position : on +Z
glm::vec3 position = glm::vec3(18.3236, 2.05326 ,-16.4623 );
// Initial horizontal angle : toward -Z
float horizontalAngle = 0.053;
// Initial vertical angle : none
float verticalAngle =  -0.399;
// Initial Field of View
float initialFoV = 45.0f;

glm::vec3 getCameraPosition(){
    return position;
}

float speed = 14.0f; // 3 units / second
float mouseSpeed = 0.003f;
int xvirtual =  1042/2;
int yvirtual =  768/2;
int xpos= 1042/2;
int ypos=768/2;

int counterX = 0;
int counterY = 0;

float walkspeed = 1.0f;

void computeMatricesFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position

//    int state = glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT);
//    if (state == GLFW_PRESS)
    glfwGetMousePos(&xpos, &ypos);

/////////////////////////////
    ///  code to allow 3d rotation of mouse

    if (xpos > 1018)
    {
        counterX++;
        glfwSetMousePos(8, ypos);
    }

    if(ypos > 760)
    {
        counterY++;
        glfwSetMousePos(xpos, 5);
    }

    if (xpos < 6)
    {
        counterX--;
        glfwSetMousePos(1016, ypos);
    }
    if (ypos < 4)
    {
        counterY--;
        glfwSetMousePos(xpos, 758);
    }


    xvirtual = xpos + 1023 * counterX;
    yvirtual = ypos + 760 * counterY;
/////////////////////////////////////////////

    //const float mouseSensitivity = 0.1f;
    // double cursorX, cursorY;
    // Reset mouse position for next frame
    //BS: but it causes lag in mouse viewing

//    if (xpos!= 1042/2) xvirtual += (xpos - 1024/2);
//    if (ypos!= 768/2) yvirtual += (ypos - 768/2);

    //if (xpos > 800 || ypos > 600) glfwSetMousePos(1024/2, 768/2);

	// Reset mouse position for next frame
	// EDIT : Doesn't work on Mac OS, hence the code below is a bit different from the website's
    //glfwSetMousePos(1024/2, 768/2);

	// Compute new orientation
    horizontalAngle =  0.053 + mouseSpeed * float(1024/2 - xvirtual );   // use xvirtual/yvirtual instead of xpos to allow mouse to rotate freely
    verticalAngle   =  -0.399 + mouseSpeed * float( 768/2 - yvirtual );



	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
    glm::vec3 up = glm::cross( right, direction );

    if (glfwGetKey( GLFW_KEY_SPACE ) == GLFW_PRESS){
        walkspeed = 5.0;
    }

    if (glfwGetKey( GLFW_KEY_SPACE ) == GLFW_RELEASE){
        walkspeed = 1.0;
    }

	// Move forward
    if (glfwGetKey( GLFW_KEY_w ) == GLFW_PRESS){
        position =  position +  vec3(0.0,0.0,1.0) * deltaTime * walkspeed;
    }
    // Move backward
    if ( glfwGetKey( GLFW_KEY_s ) == GLFW_PRESS){
        position =  position +  vec3(0.0,0.0,-1.0) * deltaTime * walkspeed;
    }
	// Strafe right
//    if (glfwGetKey( GLFW_KEY_d ) == GLFW_PRESS){
//        position =  position +  vec3(-1.0,0.0,0.0) * deltaTime * walkspeed;
//    }
	// Strafe left
    if (glfwGetKey( GLFW_KEY_a ) == GLFW_PRESS){
        position =  position +  vec3(1.0,0.0,0.0) * deltaTime * walkspeed;
    }
    if (glfwGetKey( GLFW_KEY_RSHIFT ) == GLFW_PRESS){
        position =  position +  vec3(0.0,0.001,0.0);
    }
    if (glfwGetKey( GLFW_KEY_RCTRL ) == GLFW_PRESS){
        position =  position -  vec3(0.0,0.001,0.0);
    }

	float FoV = initialFoV - 5 * glfwGetMouseWheel();


    if (glfwGetKey( GLFW_KEY_UP )  == GLFW_PRESS){
        position += direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){
        position -= direction * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey( GLFW_KEY_LEFT )== GLFW_PRESS){
        position -= right * deltaTime * speed;
    }

//    //B: to allow to to freely rotate in the game
//    if (xpos == 1023)
//        xpos = 1;
//    glfwSetMousePos(xpos, ypos);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 200.0f); //was only 100
	// Camera matrix
	ViewMatrix       = glm::lookAt(
                                position,           // Camera is here
                                position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

    //std::cout << position.x << " " << position.y << " " << position.z << endl;
    //std::cout << horizontalAngle << " " << verticalAngle << endl;

    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;

}

