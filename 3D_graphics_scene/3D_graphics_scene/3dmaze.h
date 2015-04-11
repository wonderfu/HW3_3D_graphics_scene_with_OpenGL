#ifndef _3DMAZE_H
#define _3DMAZE_H

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159f
#define N 0
#define E 1
#define S 2
#define W 3
#define MoveSpeed 0.1

/* Struct */
typedef struct Wall {
	bool way[4]; // N E S W
	int type; // maybe somthing will use it
} Wall;	

/* Function */
void Init(void);
void Display(void);
void Reshape(int, int);
void Idle(void);
void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);
void Motion(int, int);

#endif