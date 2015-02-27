/*
 Jernej Barbic
 University of Southern California
 January 2012
 
 A basic OpenGL program with GLUT.
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// standard OpenGL include files
// the location of these files varies by platform
#if defined(WIN32) || defined(linux)
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#elif defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

int windowID;
int windowWidth, windowHeight;
double angle = 0.0;
double cameraHeight = 1.0;

void Init()
{
    // set the screen background color to RGB (200, 200, 45) (light yellow)
    glClearColor(200.0 / 255, 200.0 / 255, 45.0 / 255, 0.0);
    
    // enable the depth test (important; disabled by default)
    glEnable(GL_DEPTH_TEST);
    
    //glShadeModel(GL_FLAT); // shade the entire triangle with a flat color
    glShadeModel(GL_SMOOTH); // interpolate vertex colors into the triangle interior
}

// this function gets called continuously (alternates execution with "Display")
void DoIdle()
{
    angle += 0.001; // one of the two triangles circles
    //cameraHeight = 1.0;
    cameraHeight = 1.0 + 0.5 * sin(2*angle); // camera moves up and down
    glutPostRedisplay();
}

// this function gets called whenever the user resizes the window
// x = window x-size (in pixels)
// y = window y-size (in pixels)
void Reshape(int x, int y)
{
    windowWidth = x;
    windowHeight = y;
    
    glViewport(0,0,x,y);
    
    glMatrixMode(GL_PROJECTION); // select the projection matrix
    glLoadIdentity(); // reset the projection matrix to identity
    
    // Calculate The Aspect Ratio Of The Window
    double minZPlane = 0.01;
    double maxZPlane = 10.0;
    double aspectRatio = 1.0 * windowWidth / windowHeight;
    gluPerspective(45.0f, aspectRatio, minZPlane, maxZPlane);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// this function gets called whenever a key is pressed
void KeyboardFunc (unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            // ESC pressed, exit the application
            glutDestroyWindow(windowID);
            exit(0);
            break;
            
        case 'a':
            printf("You pressed the 'a' key.\n");
            break;
            
        default:
            break;
    }
}

// this function gets called continuously (alternates execution with "DoIdle")
void Display()
{
    // clear the screen and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // select the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    // clear the modelview matrix
    glLoadIdentity();
    // set the camera position
    double cameraPosition[3] = {1.0, cameraHeight, 1.0};
    double focusPosition[3] = {0, 0, 0};
    double up[3] = {0,1,0};
    gluLookAt( cameraPosition[0], cameraPosition[1], cameraPosition[2],
              focusPosition[0], focusPosition[1], focusPosition[2],
              up[0], up[1], up[2]);
    
    // draw two triangles
    glBegin(GL_TRIANGLES);
    
    // === triangle 1 ===
    // rotate the triangle along the y-axis
    
    // vertex 1
    // set the white color
    glColor3f(1, 1, 1);
    glVertex3f(0, 0, 0);
    
    // vertex 2
    // set the blue color
    glColor3f(0, 0, 1);
    glVertex3f(0, 0.2, 0); // vertex at (0, 0.2, 0)
    
    // vertex 3
    // set a weak hue of red
    glColor3f(0.2, 0, 0);
    glVertex3f(0.2 * cos(angle), 0, 0.2 * sin(angle));
    
    // === triangle 2 ===
    
    // vertex 1
    // set the green color
    glColor3f(0, 1, 0);
    glVertex3f(0.2, 0, 0);
    
    // vertex 2
    // set black color
    glColor3f(0, 0, 0);
    glVertex3f(0.2, 0.2, 0);
    
    // vertex 3
    // set white color
    glColor3f(1, 1, 1);
    glVertex3f(0.4, 0, 0);
    
    glEnd();
    
    // render coordinate system axes
    glLineWidth(3.0); // set line width
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0.5,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,0.5,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,0.5);
    glEnd();
    
    // swap buffers
    // warning: do not forget this call, or else nothing will be drawn
    glutSwapBuffers();
}

int main (int argc, char ** argv)
{
    // init GLUT
    glutInit(&argc,argv);
    
    // double buffering, use RGBA colors, use depth buffer
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    // create a 400x400 window
    windowWidth = 400;
    windowHeight = 400;
    glutInitWindowSize (windowWidth,windowHeight);
    
    // init window position on the screen
    glutInitWindowPosition (0,0);
    
    // set the window title
    char s[4096] = "Hello world";
    windowID = glutCreateWindow(s);
    //glutFullScreen(); // make window full-screen
    
    // register the display callback
    glutDisplayFunc(Display);
    
    // register the reshape callback
    glutReshapeFunc(Reshape);
    
    // register the idle callback
    glutIdleFunc(DoIdle);
    
    // register the keyboard callback
    glutKeyboardFunc(KeyboardFunc);
    
    // call our initialization
    Init();
    
    // forever sink into an internal GLUT loop
    glutMainLoop();
    
    // we never reach this point
    return(0);
}
