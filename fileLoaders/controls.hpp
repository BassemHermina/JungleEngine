#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
glm::vec3 getCameraPosition();
void setViewMatrix (glm::mat4 V);
void setProjectionMatrix(glm::mat4 V);
#endif
