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
Canvas cvs(640, 640, title);

void drawPolyLineFile(char* fileName)
{
	fstream inStream;
	inStream.open(fileName, ios::in); // open the file
	if (inStream.fail())
		return;
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
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

	cvs.clearScreen();
	cvs.setBackgroundColor(1.0, 1.0, 1.0);
	cvs.setColor(0.0, 0.0, 0.0);
	cvs.setWindow(-10, 10, -10, 10);
	cvs.setViewport(0, 640, 0, 640);

}


void main(void)
{
	glutDisplayFunc(display);
	glutMainLoop();

}