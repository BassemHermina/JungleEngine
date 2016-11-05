#include "transformation.hpp"

TransformationClass::TransformationClass()
{
    rotationCords.x = 0;
    rotationCords.y = 0;
    rotationCords.z = 0;

    positionCords.x = 0;
    positionCords.y = 0;
    positionCords.z = 0;

    scalingCords.x = 0;
    scalingCords.y = 0;
    scalingCords.z = 0;
}

bool TransformationClass::rotater(float x,float y,float z){
    this->rotationCords.x=x;
    this->rotationCords.y=y;
    this->rotationCords.z=z;

}


bool TransformationClass::positioner(float x,float y,float z){
    this->positionCords.x=x;
    this->positionCords.y=y;
    this->positionCords.z=z;
}

bool TransformationClass::scaler(float x,float y,float z)
{
    this->scalingCords.x=x;
    this->scalingCords.y=y;
    this->scalingCords.z=z;

}
