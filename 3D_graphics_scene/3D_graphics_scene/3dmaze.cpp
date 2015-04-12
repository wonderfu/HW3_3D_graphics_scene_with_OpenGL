#include "3dmaze.h"

/*window*/
int window_size[2] = { 800, 800 };

/* camera */
GLdouble camera_eye[3] = { 0.0, 0.0, 20.0 };
GLdouble camera_center[3] = { 0.0, 0.0, 0.0 };
GLdouble camera_up[3] = { 0.0, 1.0, 0.0 };
GLfloat camera_angle = 0.0;
GLdouble camera_ray[3] = { 0.0, 0.0, -1.0 }; // eye & angle & ray decide center 

/* mouse */
int old_mouse_pos[2] = { window_size[0]>>1, window_size[1]>>1 };
float deltaAngle = 0.0f;
float deltaMove = 0;

GLfloat r;
Wall **Map;

void drawwall(float x, float y){

	glPushMatrix();
		glTranslatef(x, y, 0);
	
		glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 0.0f);         // Red
			glVertex3f(0.5f, 5.0f, 0.5f);
			glVertex3f(-0.5f, 5.0f, 0.5f);
			glVertex3f(-0.5f, 0.0f, 0.5f);
			glVertex3f(0.5f, 0.0f, 0.5f);
		glEnd();
	
		glBegin(GL_POLYGON);
			glColor3f(0.0f, 0.0f, 1.0f);         // Blue
			glVertex3f(-0.5f, 5.0f, 0.5f);
			glVertex3f(-0.5f, 5.0f, -0.5f);
			glVertex3f(-0.5f, 0.0f, -0.5f);
			glVertex3f(-0.5f, 0.0f, 0.5f);
		glEnd();
	
		glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 1.0f);         // Magenta
			glVertex3f(-0.5f, 5.0f, -0.5f);
			glVertex3f(0.5f, 5.0f, -0.5f);
			glVertex3f(0.5f, 0.0f, -0.5f);
			glVertex3f(-0.5f, 0.0f, -0.5f);
		glEnd();
	
		glBegin(GL_POLYGON);
			glColor3f(0.0f, 1.0f, 1.0f);         // Cyan
			glVertex3f(0.5f, 5.0f, -0.5f);
			glVertex3f(0.5f, 5.0f, 0.5f);
			glVertex3f(0.5f, 0.0f, 0.5f);
			glVertex3f(0.5f, 0.0f, -0.5f);
		glEnd();
	glPopMatrix();
	return;
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(window_size[0], window_size[1]);
	glutCreateWindow("3D Maze");
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(Motion);
	glutIdleFunc(Idle);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	
	Init();
	glutMainLoop();
	return 0;
}

void Init(void)
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)window_size[0] / (GLfloat)window_size[1], 1.0, 100.0);
}

void Display(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera_center[0] = camera_eye[0] + camera_ray[0];
	camera_center[1] = camera_eye[1] + camera_ray[1];
	camera_center[2] = camera_eye[2] + camera_ray[2];
	gluLookAt(camera_eye[0], camera_eye[1], camera_eye[2], camera_center[0], camera_center[1], camera_center[2], camera_up[0], camera_up[1], camera_up[2]);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawwall(2.0, 2.0);
}

void Idle(void)
{
	glutSwapBuffers();
	glutPostRedisplay();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	window_size[0] = w;
	window_size[1] = h;
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
		case 'W':
			camera_eye[2] -= MoveSpeed;
			camera_center[2] -= MoveSpeed;
			break;
		case 's':
		case 'S':
			camera_eye[2] += MoveSpeed;
			camera_center[2] += MoveSpeed;
			break;
		case 'a':
		case 'A':
			camera_eye[0] -= MoveSpeed;
			camera_center[0] -= MoveSpeed;
			break;
		case 'd':
		case 'D':
			camera_eye[0] += MoveSpeed;
			camera_center[0] += MoveSpeed;
			break;
		case 27: //ESC
			exit(0);
			break;
	}
}

void Mouse(int button, int state, int x, int y)
{

}

void Motion(int x, int y)
{
	deltaAngle = (x - camera_eye[0]) * 0.001f;
	camera_ray[0] = sin(camera_angle + deltaAngle);
	camera_ray[2] = -cos(camera_angle + deltaAngle);
}
