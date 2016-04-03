#include <GL\glut.h>
#include <GL\glaux.h>

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

void init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0,1.0,0.0,1.0,0.0,1.0);
	gluPerspective(90.0,1.0,0.0,100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,1.0,0.0,0.0,-50.0,0.0,1.0,0.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.25,0.25,0.0);
	glVertex3f(0.75,0.25,0.0);
	glVertex3f(0.75,0.75,0.0);
	glVertex3f(0.25,0.75,0.0);
	glEnd();

	glFlush();
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow("hello ");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}