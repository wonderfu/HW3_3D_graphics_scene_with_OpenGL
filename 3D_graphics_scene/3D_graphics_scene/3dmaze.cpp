#include "3dmaze.h"

/* Window */
int window_size[2] = { 800, 800 }; // W H

/* Camera */
GLdouble camera_eye[3] = { 0.0, 0.0, 20.0 };
GLdouble camera_center[3] = { 0.0, 0.0, 0.0 };
GLdouble camera_up[3] = { 0.0, 1.0, 0.0 };
GLfloat camera_angle = 0.0, camera_RL_angle = 0.0;
GLdouble camera_ray[3] = { 0.0, 0.0, -1.0 }; // eye & angle & ray decide center 

/* Light0 */
bool test_light = true;
GLfloat light0_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light0_position[] = { 5.0, 5.0, 5.0, 1.0 };

/* Light1 */
bool flash_light = true;
GLfloat light1_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_position[] = { 0.0, 0.0, 20.0, 1.0 };
GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };

/* Mouse */
int old_mouse_pos[2] = { window_size[0] >> 1, window_size[1] >> 1 };

/* Maze */
Wall **Map;

void DrawWall(GLfloat x, GLfloat z){

	glPushMatrix();
		glTranslatef(x, 0, z);
	
		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);         // Red
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f( Wall_W,  Wall_H, Wall_W);
			glVertex3f(-Wall_W,  Wall_H, Wall_W);
			glVertex3f(-Wall_W, -Wall_H, Wall_W);
			glVertex3f( Wall_W, -Wall_H, Wall_W);

			glColor3f(0.0f, 0.0f, 1.0f);         // Blue
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-Wall_W,  Wall_H,  Wall_W);
			glVertex3f(-Wall_W,  Wall_H, -Wall_W);
			glVertex3f(-Wall_W, -Wall_H, -Wall_W);
			glVertex3f(-Wall_W, -Wall_H,  Wall_W);

			glColor3f(1.0f, 0.0f, 1.0f);         // Magenta
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-Wall_W,  Wall_H, -Wall_W);
			glVertex3f( Wall_W,  Wall_H, -Wall_W);
			glVertex3f( Wall_W, -Wall_H, -Wall_W);
			glVertex3f(-Wall_W, -Wall_H, -Wall_W);

			glColor3f(0.0f, 1.0f, 1.0f);         // Cyan
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(Wall_W,  Wall_H, -Wall_W);
			glVertex3f(Wall_W,  Wall_H,  Wall_W);
			glVertex3f(Wall_W, -Wall_H,  Wall_W);
			glVertex3f(Wall_W, -Wall_H, -Wall_W);
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
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);

	glutSetCursor(GLUT_CURSOR_NONE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)window_size[0] / (GLfloat)window_size[1], 1.0, 100.0);
}

void Display(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera_center[0] = camera_eye[0] + camera_ray[0];
	camera_center[1] = camera_eye[1] + camera_ray[1];
	camera_center[2] = camera_eye[2] + camera_ray[2];
	gluLookAt(camera_eye[0], camera_eye[1], camera_eye[2], camera_center[0], camera_center[1], camera_center[2], camera_up[0], camera_up[1], camera_up[2]);

	LightSource();

	DrawWall(0.0, 0.0);
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
			camera_eye[0] += MoveSpeed*camera_ray[0];
			camera_eye[2] += MoveSpeed*camera_ray[2];
			break;
		case 's':
		case 'S':
			camera_eye[0] -= MoveSpeed*camera_ray[0];
			camera_eye[2] -= MoveSpeed*camera_ray[2];
			break;
		case 'a':
		case 'A':
			camera_eye[0] -= MoveSpeed*sin(camera_RL_angle);
			camera_eye[2] -= MoveSpeed*-cos(camera_RL_angle);
			break;
		case 'd':
		case 'D':
			camera_eye[0] += MoveSpeed*sin(camera_RL_angle);
			camera_eye[2] += MoveSpeed*-cos(camera_RL_angle);
			break;
		case 'l':
		case 'L':
			flash_light = ~flash_light;
			if (flash_light)
				glEnable(GL_LIGHT1);
			else
				glDisable(GL_LIGHT1);
			break;
		case 't':
		case 'T':
			test_light = ~test_light;
			if (flash_light)
				glEnable(GL_LIGHT0);
			else
				glDisable(GL_LIGHT0);
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
	camera_RL_angle = ((GLdouble)x / window_size[0]) * PI;
	camera_angle = camera_RL_angle - (PI / 2);
	camera_ray[0] = sin(camera_angle);
	camera_ray[2] = -cos(camera_angle);
}

void LightSource(void)
{
	if (flash_light)
	{
		light1_position[0] = camera_eye[0];
		light1_position[1] = camera_eye[1];
		light1_position[2] = camera_eye[2];
		spot_direction[0] = camera_ray[0];
		//spot_direction[1] = camera_ray[1];
		spot_direction[2] = camera_ray[2];

		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
	}
	if (test_light)
	{
		glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	}
}