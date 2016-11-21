

struct Handles {
    GLuint Shader_ProgramID;  //LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
    GLuint Shader_MVPMatrixID; // = glGetUniformLocation(Shader_ProgramID, "MVP");
    GLuint Shader_ViewMatrixID;  // = glGetUniformLocation(programID, "V");
    GLuint Shader_ModelMatrixID; //  = glGetUniformLocation(programID, "M");

    //Needed for requirement 1
    GLuint Shader_p; //= glGetUniformLocation(programID, "LightPower");

    //Needed for requirement 2
    GLuint Shader_rr; // =glGetUniformLocation(programID, "r");
    GLuint Shader_gg; // =glGetUniformLocation(programID, "g");

    // Get a handle for our buffers
    GLuint Shader_vertexPosition_modelspaceID; // = glGetAttribLocation(programID, "vertexPosition_modelspace");
    GLuint Shader_vertexUVID; // = glGetAttribLocation(programID, "vertexUV");
    GLuint Shader_vertexNormal_modelspaceID; // = glGetAttribLocation(programID, "vertexNormal_modelspace");

    // Get a handle for our "myTextureSampler" uniform
    GLuint Shader_TextureID;  //= glGetUniformLocation(programID, "myTextureSampler");

    GLuint Shader_LightID; // = glGetUniformLocation(programID, "LightPosition_worldspace");

    GLuint vertexbuffer;  // TODO . 7ot el buffersw hena , we e3ml bind bas wentra btersem
    GLuint uvbuffer;
    GLuint normalbuffer;
};

Handles getOPENGLTAGS (); //get OPENGLTAGS from main to any other class that don't have access to main but can read this header






