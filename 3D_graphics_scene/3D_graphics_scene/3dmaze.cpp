#include "3dmaze.h"

/*window*/
int window_size[2] = { 800, 800 };

/* camera */
GLdouble camera_eye[3] = {0.0,0.0,20.0};
GLdouble camera_center[3] = {0.0,0.0,0.0};
GLdouble camera_up[3] = {0.0,1.0,0.0};
GLfloat angle = 0.0;
GLfloat cx = 0.0, cz = -1.0;

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
			glColor3f(1.0f, 0.0f, 0.0f);         // 設定輸出色為紅色 
			glVertex3f(0.5f, 5.0f, 0.5f);
			glVertex3f(-0.5f, 5.0f, 0.5f);
			glVertex3f(-0.5f, 0.0f, 0.5f);
			glVertex3f(0.5f, 0.0f, 0.5f);
		glEnd();
	
		glBegin(GL_POLYGON);
			glColor3f(0.0f, 0.0f, 1.0f);         // 設定輸出色為綠色 
			glVertex3f(-0.5f, 5.0f, 0.5f);
			glVertex3f(-0.5f, 5.0f, -0.5f);
			glVertex3f(-0.5f, 0.0f, -0.5f);
			glVertex3f(-0.5f, 0.0f, 0.5f);
		glEnd();
	
		glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 1.0f);         // 設定輸出色為紫色 
			glVertex3f(-0.5f, 5.0f, -0.5f);
			glVertex3f(0.5f, 5.0f, -0.5f);
			glVertex3f(0.5f, 0.0f, -0.5f);
			glVertex3f(-0.5f, 0.0f, -0.5f);
		glEnd();
	
		glBegin(GL_POLYGON);
			glColor3f(0.0f, 1.0f, 1.0f);         // 設定輸出色為黃色 
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
	gluLookAt(camera_eye[0], camera_eye[1], camera_eye[2], camera_eye[0]+cx, camera_center[1], camera_eye[2]+cz, camera_up[0], camera_up[1], camera_up[2]);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glRotatef(45, -1.0, 0.0, 0.0);
		glRotatef(45, 0.0, 0.0, 1.0);
		glRotatef(r, 1.0, 1.0, 1.0);
		r += 0.5;
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
	cx = sin(angle + deltaAngle);
	cz = -cos(angle + deltaAngle);
	
	/*
	int move_dis[2];
	move_dis[0] = x - old_mouse_pos[0];
	move_dis[1] = (window_size[1] - y) - old_mouse_pos[1];
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(10, 0, 1, 0);
	glRotated(10, 0, 0, 1);
	old_mouse_pos[0] = x;
	old_mouse_pos[1] = y;
	*/
}
