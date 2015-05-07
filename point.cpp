#include "point.h"

point::point()
{
    x = y = z = 0;
}

point::~point()
{

}

void point::setX(float param)
{
    x = param;
}

void point::setY(float param)
{
    y = param;
}

void point::setZ(float param)
{
    z = param;
}

float point::getX()
{
    return x;
}

float point::getY()
{
    return y;
}

float point::getZ(){
    return z;
}

