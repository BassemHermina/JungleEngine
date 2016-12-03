
#include "Suzanne.hpp"

bool SuzanneClass::update()
{
    //implement update function
    //to update the buffers MVP and matrices belonging to this .obj
    cout << "Suzanne updated";

    // hena 7asab el zrayer el ana dayes-ha hayod5ol fl function di we y3'aiar fl model matrix
    // be functions translate , euler rotate , we scale we keda


}

SuzanneClass::SuzanneClass()
{
    //.obj file and .bmp texture file
    fileLocation = "Harry Potter/Harry_without_wand.obj";
        //fileLocation = "cube.obj";
    textureLocation = "Harry Potter/Harry_all.bmp";
    res = loadOBJ(fileLocation, this->vertices, this->uvs, this->normals);
    //generateAndBindBuffers(); mynfa3sh di tt3ml hna , 3ashan ana wana barsem
    // kol mara haloop 3la kol el objects , a3ml bind warsmhom wad5ol 3l ba3do w keda
    // mynf3sh a bind mn l awel
    Texture = loadBMP_custom(textureLocation);

    //these belongs to contol.cpp bas ana ha3ml wa7da zyha we hyb2a fiha el projection wel view matrices bto3 el world
    // Projection and view are global , laken model fi mnha fi kol wa7ed
    cout << "done" <<endl;
//    updateMVP();
    generateAndBindBuffers();


}

GLuint SuzanneClass::getTextureSamplerIDtoBind()
{
    return getTextureIDtoBind();
}




