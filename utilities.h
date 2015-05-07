#ifndef UTILITIES_H
#define UTILITIES_H

#include "color.h"
#include "point.h"
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>


class utilities
{
public:
    utilities();
    ~utilities();
    static void DrawBrusher(point*, float, int, Color*);
    static void DrawSquare(point*, point*, Color*, float, bool);
    static void DrawCircle(point*, point*, Color*, float, bool);
    static void DrawLine(point*, point*, Color*, float);
    static void DrawTriangle(point*, point*, Color*, float, bool);
    static void DrawBlur(point*, float, int);
    //static void changeTexelColor(GLuint, GLint, GLint, uint8_t, uint8_t, uint8_t, uint8_t);
};

#endif // UTILITIES_H
