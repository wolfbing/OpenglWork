#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <gl\glut.h>



#define pi 3.1415926

//////窗口
extern GLint WINWIDTH;
extern GLint WINHEIGHT;

/////纹理
static GLubyte T0[64][64][4];
static GLuint Tname0;
static GLuint TexLawn;
static GLuint TexSky;

//////视角
extern GLfloat VIEWPOS_X;
extern GLfloat VIEWPOS_Y;
extern GLfloat VIEWPOS_Z;
extern GLfloat VIEWANGLE;
extern GLfloat VIEWMOVSTEP;

////天空尺寸
extern GLfloat SKYSIZE;
extern GLfloat SKYHEIGHT;
extern GLfloat LAWNSIZE;

/////光源
extern bool LightMode;






#endif
