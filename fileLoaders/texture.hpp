#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>
#include <string>

// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);

// Helper function to load a Bmp for cube map and return pointer to it's data
// called 6 times in a row
unsigned char* loadBMPdata_cubeMap(const char * imagepath, int & width , int & height);

// Load a .TGA file using GLFW's own loader
GLuint loadTGA_glfw(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);



#endif
