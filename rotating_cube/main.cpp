#include <iostream>
#include "GL/glut.h"

GLfloat speed_of_rotate = 0;
int RotateOnFlag = 0, RotateOffFlag = 0, RotateOnOneSide = -1;
bool speed_flag = true;

void Menu(int id)
{
	if (id == 1)
		RotateOnFlag = 1;
	else if (id == 2)
		RotateOnFlag = -1;
	else if (id == 5)
		exit(0);
	else if (id == 3)
		speed_flag = true;
	else if (id == 4)
		speed_flag = false;

	RotateOffFlag = 1;
	glutPostRedisplay();
}

void Spin()
{
	if (speed_flag)
		speed_of_rotate = speed_of_rotate + 0.1;
	else
		speed_of_rotate = speed_of_rotate - 0.1;

	if (speed_of_rotate > 360)
		speed_of_rotate = 0;
	glutPostRedisplay();
}

void myInit()
{
	glClearColor(0, 0, 0, 1);
	glColor3f(1, 0, 0);
	glEnable(GL_DEPTH_TEST);
}

void Face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[])
{
	glBegin(GL_POLYGON);

		glVertex3f(A[0], A[1], A[2]);
		glVertex3f(B[0], B[1], B[2]);
		glVertex3f(C[0], C[1], C[2]);
		glVertex3f(D[0], D[1], D[2]);

	glEnd();
}

void Cube(GLfloat v0[], GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat v4[], GLfloat v5[], GLfloat v6[], GLfloat v7[])
{
	glColor3f(1, 0, 0);
	Face(v0, v1, v2, v3);

	glColor3f(0, 1, 0);
	Face(v4, v5, v6, v7);

	glColor3f(0, 0, 1);
	Face(v0, v3, v7, v4);

	glColor3f(1, 0, 1);
	Face(v1, v2, v6, v5);

	glColor3f(1, 1, 0);
	Face(v0, v1, v5, v4);

	glColor3f(0, 1, 1);
	Face(v3, v2, v6, v7);
}

void Draw()
{
	GLfloat point[8][3] = 
	{
		{-0.5, 0.5, 0.5},
		{0.5, 0.5, 0.5},
		{0.5, -0.5, 0.5},
		{-0.5, -0.5, 0.5},

		{-0.5, 0.5, -0.5},
		{0.5, 0.5, -0.5},
		{0.5, -0.5, -0.5},
		{-0.5, -0.5, -0.5}
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(speed_of_rotate, RotateOnOneSide, RotateOnFlag, RotateOffFlag);
	Cube(point[0], point[1], point[2], point[3], point[4], point[5], point[6], point[7]);

	glutSwapBuffers();
}

int main(int argC, char* argV[])
{
	glutInit(&argC, argV);

	glutInitWindowPosition(250, 50);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Rotating cube");
	myInit();

	glutCreateMenu(Menu);
	glutAddMenuEntry("Rotate counterclockwise", 1);
	glutAddMenuEntry("Rotate clockwise", 2);
	glutAddMenuEntry("Increase speed of rotate", 3);
	glutAddMenuEntry("Reduce rotation speed", 4);
	glutAddMenuEntry("Exit", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutIdleFunc(Spin);
	glutDisplayFunc(Draw);
	glutMainLoop();
	
	return 0;
}