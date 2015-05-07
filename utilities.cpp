#include "utilities.h"
#include <math.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <iostream>
#include "EasyBMP/EasyBMP.h"
using namespace std;

utilities::utilities()
{

}

utilities::~utilities()
{

}

void utilities::DrawBrusher(point *start, float r, int num_segments, Color *c)
{
    glColor4f((GLfloat)c->getR() / 256.0f, (GLfloat)c->getG() / 256.0f, (GLfloat)c->getB() / 256.0f, (GLfloat)c->getA() / 100.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(20);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + start->getX(), y + start->getY());
    }
    glEnd();
}

void utilities::DrawSquare(point *start, point *end, Color *c, float size, bool isFilled){
    glColor4f((GLfloat)c->getR() / 256.0f, (GLfloat)c->getG() / 256.0f, (GLfloat)c->getB() / 256.0f, (GLfloat)c->getA() / 100.0f);

    if(isFilled)
        glBegin(GL_POLYGON);
    else
        glBegin(GL_LINE_LOOP);

    glVertex3f(start->getX(), start->getY(), 0.0f); // The bottom left corner
    glVertex3f(end->getX(), start->getY(), 0.0f); // The top left corner
    glVertex3f(end->getX(), end->getY(), 0.0f); // The top right corner
    glVertex3f(start->getX(), end->getY(), 0.0f); // The bottom right corner
    glEnd();
    glLineWidth(size);
}

void utilities::DrawCircle(point *start, point *end, Color *c, float size, bool isFilled){
    float r = 0.0,cx,cy;
    glColor4f((GLfloat)c->getR() / 256.0f, (GLfloat)c->getG() / 256.0f, (GLfloat)c->getB() / 256.0f, (GLfloat)c->getA() / 100.0f);
    if(isFilled)
        glBegin(GL_POLYGON); // Start drawing a line primitive
    else
        glBegin(GL_LINE_LOOP);
    //calculate radius
    r = sqrt(pow(abs(end->getX() - start->getX()),2) + pow(abs(end->getY() - start->getY()),2))/2;
    if (end->getX() > start->getX())
        cx = start->getX() +( (end->getX() - start->getX()) / 2);
    else
        cx = end->getX() + ((start->getX() - end->getX()) / 2);
    if (end->getY() > start->getY())
        cy = start->getY() + ((end->getY() - start->getY()) / 2);
    else
        cy = end->getY() + ((start->getY() - end->getY()) / 2);

    for (int i = 0; i < (int)r*2; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(25);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
    glLineWidth(size);

}

void utilities::DrawLine(point *start, point *end, Color *c, float size){
    glColor4f((GLfloat)c->getR() / 256.0f, (GLfloat)c->getG() / 256.0f, (GLfloat)c->getB() / 256.0f, (GLfloat)c->getA() / 100.0f);;
    glBegin(GL_LINE_LOOP); // Start drawing a line primitive
    glVertex3f(start->getX(), start->getY(), 0.0f); // The bottom left corner
    glVertex3f(end->getX(), end->getY(), 0.0f); // The top left corner
    glEnd();
    glLineWidth(size);
}

void utilities::DrawTriangle(point *start, point *end, Color *c, float size ,bool isFilled){
        glColor4f((GLfloat)c->getR() / 256.0f, (GLfloat)c->getG() / 256.0f, (GLfloat)c->getB() / 256.0f, (GLfloat)c->getA() / 100.0f);
        if(isFilled)
            glBegin(GL_POLYGON);
        else
            glBegin(GL_LINE_LOOP);

        glVertex3f(start->getX(), start->getY(), 0.0f); // The bottom left corner
        glVertex3f(end->getX(), start->getY(), 0.0f); // The top left corner
        glVertex3f(end->getX(), end->getY(), 0.0f); // The top right corner
        glEnd();
        glLineWidth(size);
}



