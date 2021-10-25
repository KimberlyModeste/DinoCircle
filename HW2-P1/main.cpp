//CSC470 HW2
//Kimberly Modeste
#include <GL/glut.h>
#include <math.h>
#include <stdio.h> 
#include <fstream>
#include <iostream>
#include "classes.h"

using namespace std;

char title[] = "Dino Circle";
Canvas cvs(640, 480, title);


void drawPolyLineFile(char* fileName)
{
	fstream inStream;
	inStream.open(fileName, ios::in); // open the file
	if (inStream.fail())
		return;
	
	GLint numpolys, numLines, x, y;
	inStream >> numpolys; // read the number of polylines
	for (int j = 0; j < numpolys; j++) // read each polyline
	{
		inStream >> numLines;
		glBegin(GL_LINE_STRIP); // draw the next polyline
		for (int i = 0; i < numLines; i++)
		{
			inStream >> x >> y; // read the next x, y pair
			glVertex2i(x, y);
		}
		glEnd();
	}
	glFlush();
	inStream.close();
}

void display() {

	char dino[] = "Brontoi.dat";
	float theta;
	float r = 1;
	Point2 c;

	cvs.clearScreen();
	cvs.setBackgroundColor(1.0, 1.0, 1.0);
	cvs.setViewport(0, 640, 0, 480);
	cvs.setWindow(0, 640, 0, 480);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);

	glPushMatrix();
	
	//inner rotation
	c.set(420, 120);
	cvs.setColor(1.0, 0.0, 0.0);
	glTranslatef(440, 30, 0.0);
	glScalef(0.0625, 0.0625, 1.0);
	for (int i = 0; i < 360; i += 20)
	{
		theta = i * 3.14159265 / 180;
		glTranslatef(r * cos(theta) + c.getX(), r * sin(theta) + c.getY(), 0.0);
		glRotatef(20.0f, 0.0, 0.0, 1.0);

		drawPolyLineFile(dino);
	}
	glPopMatrix();

	glPushMatrix();

	//outer rotation
	cvs.setColor(0.0, 1.0, 0.0);
	glTranslatef(140, 420, 0.0);
	glScalef(0.0625, 0.0625, 1.0);
	for (int i = 0; i < 360; i += 10)
	{
		theta = i * 3.14159265 / 180;
		glTranslatef(r * cos(theta) + c.getX(), r * sin(theta) + c.getY(), 0.0);
		glRotatef(-20.0f, 0.0, 0.0, 1.0);

		drawPolyLineFile(dino);
	}
	glPopMatrix();


	//standing up
	r = 80;
	c.set(140, 120);
	cvs.setColor(0.0, 0.0, 1.0);
	for (int i = 0; i < 360; i += 20)
	{
		theta = i * 3.14159265 / 180;
		glViewport(r * cos(theta) + c.getX(), r * sin(theta) + c.getY(), 40, 30);
		drawPolyLineFile(dino);
	}

	//upside down
	c.set(420, 320);
	cvs.setColor(1.0, 0.0, 1.0);
	cvs.setWindow(0, 640, 480, 0);
	for (int i = 0; i < 360; i += 20)
	{
		theta = i * 3.14159265 / 180;
		glViewport(r * cos(theta) + c.getX(), r * sin(theta) + c.getY(), 40, 30);
		drawPolyLineFile(dino);
	}


}

void main(void)
{
	glutDisplayFunc(display);
	glutMainLoop();

}
