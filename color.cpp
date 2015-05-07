#include "color.h"

Color::Color()
{
    red = 0;
    green = 0;
    alpha = 0;
    blue = 0;
}

Color::~Color()
{

}

void Color::setA(int p)
{
    alpha = p;
}

void Color::setB(int p)
{
    blue = p;
}

void Color::setG(int p)
{
    green = p;
}

void Color::setR(int p)
{
    red = p;
}

int Color::getG()
{
    return green;
}

int Color::getB()
{
    return blue;
}

int Color::getR()
{
    return red;
}

int Color::getA()
{
    return alpha;
}
