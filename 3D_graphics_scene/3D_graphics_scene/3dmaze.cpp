#include "3dmaze.h"

Wall **Map;
GLdouble camera_eye[3] = {0.0,1.0,0.0};
GLdouble camera_center[3] = {0.0,0.0,0.0};
GLdouble camera_up[3] = {0.0,1.0,0.0};

GLfloat r;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(800, 800);
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
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(45, -1.0, 0.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glRotatef(r, 1.0, 1.0, 1.0);
	r += 0.5;

	glPushMatrix();
		glBegin(GL_QUADS);

		glColor3f(0.0, 1.0, 0.0);			// G
		glVertex3f( 2, 1,-2);			// TOP  UPPER RIGHT
		glVertex3f(-2, 1,-2);			// TOP  UPPER LEFT
		glVertex3f(-2, 1, 2);			// TOP  LOWER LEFT
		glVertex3f( 2, 1, 2);			// TOP  LOWER RIGHT

		glColor3f(1.0, 0.0, 1.0);			// M
		glVertex3f( 2,-1, 2);			// BOTTOM  UPPER RIGHT
		glVertex3f(-2,-1, 2);			// BOTTOM  UPPER LEFT
		glVertex3f(-2,-1,-2);			// BOTTOM  LOWER LEFT
		glVertex3f( 2,-1,-2);			// BOTTOM  LOWER RIGHT

		glColor3f(0.0, 1.0, 1.0);			// R
		glVertex3f( 2, 2, 1);			// FRONT  UPPER RIGHT
		glVertex3f(-2, 2, 1);			// FRONT  UPPER LEFT
		glVertex3f(-2,-2, 1);			// FRONT  LOWER LEFT
		glVertex3f( 2,-2, 1);			// FRONT  LOWER RIGHT

		glColor3f(1.0, 0.0, 0.0);			// C
		glVertex3f( 2,-2,-1);			// REAR  UPPER RIGHT
		glVertex3f(-2,-2,-1);			// REAR  UPPER LEFT
		glVertex3f(-2, 2,-1);			// REAR  LOWER LEFT
		glVertex3f( 2, 2,-1);			// REAR  LOWER RIGHT

		glColor3f(1.0, 1.0, 0.0);			// B
		glVertex3f(-1, 2, 2);			// LEFT  UPPER RIGHT
		glVertex3f(-1, 2,-2);			// LEFT  UPPER LEFT 
		glVertex3f(-1,-2,-2);			// LEFT  LOWER LEFT 
		glVertex3f(-1,-2, 2);			// LEFT  LOWER RIGHT

		glColor3f(0.0, 0.0, 1.0);			// Y
		glVertex3f(1, 2,-2);			// RIGHT  UPPER RIGHT
		glVertex3f(1, 2, 2);			// RIGHT  UPPER LEFT 
		glVertex3f(1,-2, 2);			// RIGHT  LOWER LEFT 
		glVertex3f(1,-2,-2);			// RIGHT  LOWER RIGHT

		glEnd();
	glPopMatrix();
	glFlush();
}

void Idle(void)
{
	glutSwapBuffers();
	glutPostRedisplay();
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(camera_eye[0], camera_eye[1], camera_eye[2], camera_center[0], camera_center[1], camera_center[2], camera_up[0], camera_up[1], camera_up[2]);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
		case 'W':
			camera_eye[2] - MoveUnit;
			break;
		case 's':
		case 'S':
			camera_eye[2] + MoveUnit;
			break;
		case 'a':
		case 'A':
			camera_eye[0] - MoveUnit;
			break;
		case 'd':
		case 'D':
			camera_eye[0] + MoveUnit;
			break;

		default:
			break;
	}
}

void Mouse(int button, int state, int x, int y)
{

}

void Motion(int x, int y)
{

}
