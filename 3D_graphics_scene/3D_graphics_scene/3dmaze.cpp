#include "3dmaze.h"

Wall **Map;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3D Maze");
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutIdleFunc(Idle);
	glutDisplayFunc(Display);
	
	Init();
	glutMainLoop();
	return 0;
}

void Init(void)
{
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void Display(void)
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);          // �}�l���T���� 
	glColor3f(1.0f, 0.0f, 0.0f);         // �]�w��X�⬰���� 
	glVertex2f(0.0f, 1.0f);           //(x1,y1)=(0, 1)
	glColor3f(0.0f, 1.0f, 0.0f);         // �]�w��X�⬰��� 
	glVertex2f(0.87f, -0.5f);            //(x2,y2)=(0.87,-0.5)
	glColor3f(0.0f, 0.0f, 1.0f);         // �]�w��X�⬰�Ŧ� 
	glVertex2f(-0.87f, -0.5f);           //(x3,y3)=(-0.87,-0.5)
	glEnd();                               // �������T���� 
	glPopMatrix();
	glutSwapBuffers();
}

void Idle(void)
{
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{

}

void Mouse(int button, int state, int x, int y)
{

}

void Motion(int x, int y)
{

}
