
#include "plane.hpp"

bool PlaneClass::update()
{
    //implement update function
    //to update the buffers MVP and matrices belonging to this .obj
    cout << "Suzanne updated";

    // hena 7asab el zrayer el ana dayes-ha hayod5ol fl function di we y3'aiar fl model matrix
    // be functions translate , euler rotate , we scale we keda


}

PlaneClass::PlaneClass()
{
    //.obj file and .bmp texture file
    fileLocation = "3dmodels/plane10.obj";
    //fileLocation = "cube.obj";
    textureLocation = "3dmodels/planetexbmp.bmp";
    Texture = loadBMP_custom(textureLocation);

    res = loadOBJ(fileLocation, this->vertices, this->uvs, this->normals);
    //generateAndBindBuffers(); mynfa3sh di tt3ml hna , 3ashan ana wana barsem
    // kol mara haloop 3la kol el objects , a3ml bind warsmhom wad5ol 3l ba3do w keda
    // mynf3sh a bind mn l awel

    //these belongs to contol.cpp bas ana ha3ml wa7da zyha we hyb2a fiha el projection wel view matrices bto3 el world
    // Projection and view are global , laken model fi mnha fi kol wa7ed
    cout << "done" <<endl;
 //   updateMVP_Phong();
    generateAndBindBuffers();
}
