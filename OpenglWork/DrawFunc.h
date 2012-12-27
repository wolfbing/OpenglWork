#ifndef DRAWFUNC_H
#define DRAWFUNC_H

#include <gl/glut.h>

unsigned int LoadTex(char * Image);

void CreateLawn( float l , float w , float h );
void CreateSky( float l , float w , float h );

/////定义光源
void CreateLight();

////画基本集合体
void SolidHalfSphere(double radius , int slices , int stacks );
void SolidCylinder(double radius ,double height , int slices);
void SolidRoundCylinder(double radius ,double height , int slices , int stacks);
void FanCircle(float radius,int slices);

/////机器人类
class Robot
{
public:
	Robot();
	void SolidHead(double radius, int slices , int stacks );
	void DefMat_RobotEye();
	void DefMat_Robot();
	void SolidAndriodRobot();

private:
	GLfloat matcolor[4];
	GLfloat matshininess;
	GLfloat LeftArmAngle;
	GLfloat RightArmAngle;
	GLfloat LeftLegAngle;
	GLfloat RightLegAngle;
	GLfloat radius;
};


#endif