#include "mainwindow.h"
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <iostream>
#include "color.h"
#include "point.h"
#include "utilities.h"
#include "math.h"
#include <vector>
#include "EasyBMP/EasyBMP.h"

#define CIRCLE_SENSIVITY 20
#define BRUSH 0
#define BLUR_BRUSH 1
#define LINE 2
#define CIRCLE 3
#define RECTANGLE 4
#define TRIANGLE 5

#define HEIGHT 270
#define WIDTH 480

GLubyte image[HEIGHT][WIDTH][4];
GLuint texname;
BMP readImage;

Color *selectedColor;
Color *clearColor;
point *start;
point *end;
int selectedSize = 5;
int currentMode;

float pointx;
float pointy;

bool isFirstCall = false;
bool isPressed = false;
bool isErase = false;
bool isFilled = false;
bool isActive = false;
float height = 270;
float width = 480;
using namespace std;

void changeTexelColor(GLuint, GLint, GLint, uint8_t, uint8_t, uint8_t, uint8_t);
void DrawBlur(point *start, float radius)
{
    BMP bufferImg;
    RGBApixel temp;
    bufferImg.SetBitDepth(16);
    bufferImg.SetSize(WIDTH, HEIGHT);
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            glReadPixels(i,j,1,1,GL_RED, GL_UNSIGNED_BYTE, &temp.Red);
            glReadPixels(i,j,1,1,GL_GREEN, GL_UNSIGNED_BYTE, &temp.Green);
            glReadPixels(i,j,1,1,GL_BLUE, GL_UNSIGNED_BYTE, &temp.Blue);
            glReadPixels(i,j,1,1,GL_ALPHA, GL_UNSIGNED_INT, &temp.Alpha);
            bufferImg.SetPixel(i, j, temp);
        }
    }

    RGBApixel sum;
    for(int i = 0; i< (int)radius/2; i++)
    {
        int jj;
        sum.Red = sum.Green = sum.Blue = sum.Alpha = 0;
        for(int j = 0; j<(int)radius/2; j++)
        {
            //i,j selected pixel
            int k = (int)start->getX() + i - (int)radius/4;
            int l =(int)start->getY() + j - (int)radius/4;
            sum.Red += bufferImg(k,l)->Red;
            sum.Green += bufferImg(k,l)->Green;
            sum.Blue += bufferImg(k,l)->Blue;
            sum.Alpha += bufferImg(k,l)->Alpha;
            jj = j;
        }
        sum.Red /= (radius/2);
        sum.Green /= (radius/2);
        sum.Blue /= (radius/2);
        sum.Alpha /= (radius/2);
        bufferImg(i,jj)->Red = sum.Red;
        bufferImg(i,jj)->Blue = sum.Blue;
        bufferImg(i,jj)->Green = sum.Green;
        bufferImg(i,jj)->Alpha = sum.Alpha;
    }

    int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for ( j = 0; j < WIDTH; j++) {
            image[HEIGHT - i -1][j][0] = (GLubyte)((int)bufferImg(j,i)->Red);
            image[HEIGHT - i -1][j][1] = (GLubyte)((int)bufferImg(j,i)->Green);
            image[HEIGHT - i -1][j][2] = (GLubyte)((int)bufferImg(j,i)->Blue);
            image[HEIGHT - i -1][j][3] = 255;
        }
    }
    isFirstCall=false;

}

void reshape(int w, int h)
{
    w = w < 1 ? 1 : w;
    h = h < 1 ? 1 : h;
    height = h;
    width = w;
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, 0.0, h, 1.0, -1.0);
}

void bindBackground()
{
    glClearColor (0.0, 1.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable (GL_DEPTH_TEST);
    glPixelStorei (GL_PACK_ALIGNMENT, 1);

    glGenTextures (1, &texname);
    glBindTexture (GL_TEXTURE_2D, texname);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT,0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glEnable (GL_TEXTURE_2D);
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture (GL_TEXTURE_2D, texname);
    glMatrixMode (GL_MODELVIEW);
    glPushMatrix ();
    glLoadIdentity ();
    glMatrixMode (GL_PROJECTION);
    glPushMatrix ();
    glLoadIdentity ();
    glBegin (GL_QUADS);
    glTexCoord2f (0, 0.0);
    glVertex3i (-1, -1, -1);
    glTexCoord2f (1, 0.0);
    glVertex3i (1, -1, -1);
    glTexCoord2f (1, 1.0);
    glVertex3i (1, 1, -1);
    glTexCoord2f (0, 1.0);
    glVertex3i (-1, 1, -1);
    glEnd ();
    glPopMatrix ();
    glDisable (GL_TEXTURE_2D);
    isFirstCall = true;
}

void display(void){
    if(!isFirstCall)
        bindBackground();

    if (isPressed)
    {
        if(!isErase)
        {
            if(currentMode == BRUSH)
                utilities::DrawBrusher(end, (float)selectedSize, CIRCLE_SENSIVITY, selectedColor);

        }
        else
        {
                utilities::DrawBrusher(end, (float)selectedSize, CIRCLE_SENSIVITY, clearColor);
        }
    }
    else
    {
        if(!isErase && isActive)
        {
            if(currentMode == LINE)
                utilities::DrawLine(start, end, selectedColor, (float)selectedSize);
            else if( currentMode == CIRCLE)
                utilities::DrawCircle(start, end, selectedColor, (float)selectedSize, isFilled);
            else if(currentMode == RECTANGLE)
                utilities::DrawSquare(start, end, selectedColor, (float)selectedSize, isFilled);
            else if(currentMode == TRIANGLE)
                utilities::DrawTriangle(start, end, selectedColor, (float)selectedSize, isFilled);
            else if(currentMode == BLUR_BRUSH)
                DrawBlur(end, (float)selectedSize);
            isActive = false;
        }
        //
    }

    glFlush();

}

void motion(int x, int y)
// called when a mouse is in motion with a button down
{
    if (isPressed)
    {
        //pointy = height - y;
        //pointx = x;
        end->setX(x);
        end->setY(height - y);
    }
    glutPostRedisplay();
}

void spindisplay(void)
{
    glutPostRedisplay();
}

void mouse(int bin, int state, int x, int y) {
    if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        isPressed = true;
        start->setX(x);
        start->setY(height - y);
        end->setX(x);
        end->setY(height - y);
    }

    if (bin == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        isPressed = false;
        isActive = true;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27 || key == 'q' || key == 'Q')
        exit(EXIT_SUCCESS);
}


void init(void)
{
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            image[HEIGHT-i-1][j][0] = (GLubyte)255;
            image[HEIGHT-i-1][j][1] = (GLubyte)255;
            image[HEIGHT-i-1][j][2] = (GLubyte)255;
            image[HEIGHT-i-1][j][3] = 255;
        }
    }
}

/*Main*/

int main(int argc, char** argv){
    currentMode = BRUSH;
    selectedColor = new Color;
    selectedColor->setA(100);
    clearColor = new Color;
    clearColor->setR(256);
    clearColor->setG(256);
    clearColor->setB(256);
    clearColor->setA(100);
    start = new point;
    end = new point;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(width, height);
    /*Set the posotion of window*/
    glutInitWindowPosition(0, 0);
    glutCreateWindow("My Vindow");
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutIdleFunc(spindisplay);
    glutReshapeFunc(reshape);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    glutMainLoop();
}


void MainWindow::on_pushButtonLoad_clicked()
{
    cout << "load" << endl;
    QString filename = QFileDialog::getOpenFileName();
    //readImage.ReadFromFile("/Users/umitulusoy/EasyBMPbackground.bmp");
    if(!filename.toStdString().empty())
    {
        readImage.ReadFromFile(filename.toStdString().c_str());
        int i, j;
        for (i = 0; i < HEIGHT; i++) {
            for ( j = 0; j < WIDTH; j++) {
                image[HEIGHT-i-1][j][0] = (GLubyte)((int)readImage(j,i)->Red);
                image[HEIGHT-i-1][j][1] = (GLubyte)((int)readImage(j,i)->Green);
                image[HEIGHT-i-1][j][2] = (GLubyte)((int)readImage(j,i)->Blue);
                image[HEIGHT-i-1][j][3] = 255;
            }
        }
        isFirstCall=false;
    }
}

void MainWindow::on_pushButtonColorDialog_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    cout <<" red " <<color.red() << " blue " << color.blue() << " green " << color.green() << endl;
    selectedColor->setR(color.red());
    selectedColor->setG(color.green());
    selectedColor->setB(color.blue());
    MainWindow::updateUIComponents(color.red(), color.green(), color.blue(), color.alpha());
}

void MainWindow::on_pushButtonSave_clicked()
{
    cout << "save" << endl;
    BMP output;
    RGBApixel temp;
    output.SetBitDepth(16);
    output.SetSize(WIDTH, HEIGHT);
    QString filters("BMP files (*.bmp)");
    QString defaultFilter("BMP files (*.bmp)");
    QString fileName2 = QFileDialog::getSaveFileName(0, "Save file", QDir::homePath(),filters, &defaultFilter);

    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {

            glReadPixels(i,j,1,1,GL_RED, GL_UNSIGNED_BYTE, &temp.Red);
            glReadPixels(i,j,1,1,GL_GREEN, GL_UNSIGNED_BYTE, &temp.Green);
            glReadPixels(i,j,1,1,GL_BLUE, GL_UNSIGNED_BYTE, &temp.Blue);
            glReadPixels(i,j,1,1,GL_ALPHA, GL_UNSIGNED_INT, &temp.Alpha);
            output.SetPixel(i, j, temp);
        }
    }
    output.WriteToFile(fileName2.toStdString().c_str());
}

//checkbox
void MainWindow::on_checkBoxErase_stateChanged(int param){
  cout << "checkbox " << param << endl;
  if(param == 2)
      isErase = true;
  else
      isErase = false;
}

void MainWindow::on_checkBoxFilled_stateChanged(int param){

  cout << "checkbox fill" << param << endl;
  if(param == 2)
      isFilled = true;
  else
      isFilled = false;
}

//sliders
void MainWindow::on_horizontalSliderRed_valueChanged(int param){
    cout << "red " << param  << " " << param << endl;
    selectedColor->setR(param);
}
void MainWindow::on_horizontalSliderGreen_valueChanged(int param){
    cout << "green " << param  << " " << param << endl;
    selectedColor->setG(param);
}
void MainWindow::on_horizontalSliderBlue_valueChanged(int param){
    cout << "blue " << param  << " " << param << endl;
    selectedColor->setB(param);
}
void MainWindow::on_horizontalSliderSize_valueChanged(int param){
    cout << "size " << param << endl;
    selectedSize = param;
}
void MainWindow::on_horizontalSliderAlpha_valueChanged(int param){
    cout << "alpha " << param << endl;
    selectedColor->setA(param);
}

//combo box
void MainWindow::on_comboBox_currentIndexChanged(int param){
    cout << "combo box " << param << endl;
    currentMode = param;
}

void changeTexelColor(GLuint id, GLint x, GLint y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    uint8_t data[4];
    data[0] = r;
    data[1] = g;
    data[2] = b;
    data[3] = a;
    glBindTexture(GL_TEXTURE_2D, id);
    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    x,
                    y,
                    1,
                    1,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    data);
}


