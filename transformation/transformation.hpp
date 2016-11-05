#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

class Coords3f {
public:
   float x=0,y=0,z=0;

};

class TransformationClass
{
private:
    Coords3f rotationCords;
    Coords3f positionCords;
    Coords3f scalingCords;

public:
    bool rotater(float x,float y,float z);
    bool positioner(float x,float y,float z);
    bool scaler(float x,float y,float z);
    TransformationClass();
};

#endif // TRANSFORMATION_H
