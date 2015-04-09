#ifndef _3DMAZE_H
#define _3DMAZE_H

#include <GL/glut.h>
#include <math.h>

#define N 0
#define E 1
#define S 2
#define W 3

/* Struct */
typedef struct Wall {
	bool way[4]; // N E S W
	int type; // maybe somthing will use it
	Wall() :way[0](false), way[1](false), way[2](false), way[3](false){}
} Wall;

/* Function */
void Init(void);
void Display(void);
void Idle(void);
void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);
void Motion(int, int);

void CreateMaze(int, int);

#endif