#include "classes.h"
//changes current point
void Canvas::moveTo(float x, float y)
{
    CP.set(x, y);
}

//draws a line from current point to new point
void Canvas::lineTo(float x, float y) {
    glBegin(GL_LINES);
    glVertex2f((GLfloat)CP.getX(), (GLfloat)CP.getY());
    glVertex2f((GLfloat)x, (GLfloat)y); //draw the line
    glEnd();
    CP.set(x, y); //update current point to new point
    glFlush();
}

void Canvas::setWindow(float l, float r, float b, float t) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D((GLdouble)l, (GLdouble)r, (GLdouble)b, (GLdouble)t);
    window.set(l, r, b, t);
}

void Canvas::setViewport(int l, int r, int b, int t) {
    glViewport((GLint)l, (GLint)b, (GLint)r - l, (GLint)t - b);
    // viewport.set(l, r, b, t);
}

IntRect Canvas::getViewport(void)
{
    return viewport;
}

RealRect Canvas::getWindow(void)
{
    return window;
}

void Canvas::clearScreen(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Canvas::setBackgroundColor(float r, float g, float b)
{
    glClearColor(r, g, b, 0.0);
}

void Canvas::setColor(float r, float g, float b)
{
    glColor3f(r, g, b);
}

void Canvas::setColorfv(float c[])
{
    glColor3fv(c);
}

void Canvas::lineTo(Point2 p) {
    glBegin(GL_QUADS);

    glVertex2f((GLfloat)CP.getX(), (GLfloat)CP.getY());
    glVertex2f((GLfloat)p.getX(), (GLfloat)p.getY());
    glEnd();
    CP.set(p.getX(), p.getY());
    glFlush();
}

Canvas::Canvas(int width, int height, char* windowTitle) {
    char* argv[1];  //dummy argument list for glutinit()
    char dummyString[16];
    argv[0] = dummyString;  //hook up the pointer
    int argc = 1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(20, 20);
    glutCreateWindow(windowTitle);
    setWindow(0, (float)width, 0, (float)height); // default world window
    setViewport(0, width, 0, height); //default viewport
    CP.set(0.0f, 0.0f); //initialize the CP to (0,0)

}

void Canvas::moveTo(Point2 p)  //moves current point CP to point p object
{
    CP.set(p.getX(), p.getY());
}

float Canvas::getWindowAspectRatio(void) {
    //calculates aspect ratio of world window
    float width, height, aspectRatio;
    width = window.getR() - window.getL();
    height = window.getT() - window.getB();
    aspectRatio = width / height;
    return aspectRatio;
}

void Canvas::moveRel(float dx, float dy) {
    CP.set(CP.getX() + dx, CP.getY() + dy);
}

void Canvas::lineRel(float dx, float dy) {
    float x = CP.getX() + dx, y = CP.getY() + dy;
    lineTo(x, y);
    CP.set(x, y);
}