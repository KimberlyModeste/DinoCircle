#pragma once
#ifndef CLASSES_H // include guard
#define CLASSES_H
#include <GL/glut.h>
#include <math.h>

// << Support Classes for Canvas >>
class Point2   //single point w/ floating point coordinates
{
public:
    Point2() { x = y = 0.0f; } //constructor 1
    Point2(float xx, float yy) { x = xx; y = yy; } //constructor 2
    void set(float xx, float yy) { x = xx; y = yy; }
    float getX() { return x; }
    float getY() { return y; }
    void draw(void) {
        glBegin(GL_POINTS); //draw this point
        glVertex2f((GLfloat)x, (GLfloat)y);
        glEnd();
    }
private:
    float x, y;
};

class IntRect {
    //aligned rectangle with integer coordinates, used for viewport
public:
    IntRect() { l = 0; r = 100; b = 0; t = 100; } //constructors
    IntRect(int left, int right, int bottom, int top)
    {
        l = left; r = right; b = bottom; t = top;
    }
    void set(int left, int right, int bottom, int top) {
        l = left; r = right; b = bottom; t = top;
    }
    void draw(void) { //draw this rectangle using OpenGL
        glBegin(GL_LINE_STRIP); //draw this polygon
        glVertex2i(l, b);
        glVertex2i(r, b);
        glVertex2i(r, t);
        glVertex2i(l, t);
        glVertex2i(l, b);
        glEnd();
    }
    int getL(void) { return l; }
    int getR(void) { return r; }
    int getT(void) { return t; }
    int getB(void) { return b; }

private:
    int l, r, b, t;
};

class RealRect {
    //simlar to IntRect but w/ floating points & used for world window
public:
    RealRect() { l = 0; r = 100; b = 0; t = 100; } //constructors
    RealRect(float left, float right, float bottom, float top)
    {
        l = left; r = right; b = bottom; t = top;
    }
    void set(float left, float right, float bottom, float top)
    {
        l = left; r = right; b = bottom; t = top;
    }
    float getL(void) { return l; }
    float getR(void) { return r; }
    float getT(void) { return t; }
    float getB(void) { return b; }
    void draw(void) { //draw this rectangle using OpenGL
        glBegin(GL_LINE_STRIP); //draw this polygon
        glVertex2f(l, b);
        glVertex2f(r, b);
        glVertex2f(r, t);
        glVertex2f(l, t);
        glVertex2f(l, b);
        glEnd();
    }
private:
    float l, r, b, t;
};

class Canvas {
public:
    Canvas(int width, int height, char* windowTitle); //constructor
    void setWindow(float l, float r, float b, float t);
    void setViewport(int l, int r, int b, int t);
    IntRect getViewport(void); //divulge the viewport data
    RealRect getWindow(void); // divulge the window data
    float getWindowAspectRatio(void);
    void clearScreen();
    void setBackgroundColor(float r, float g, float b);
    void setColor(float r, float g, float b);
    void setColorfv(float c[]);
    void lineTo(float x, float y);
    void lineTo(Point2 p);
    void lineRel(float dx, float dy);
    void moveTo(float x, float y);
    void moveTo(Point2 p);
    void moveRel(float dx, float dy);

private:
    Point2 CP;         //current position in the world
    IntRect viewport;  //the current viewport
    RealRect window;   //the current window

};

#endif