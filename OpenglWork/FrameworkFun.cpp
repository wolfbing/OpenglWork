#include "stdafx.h"
#include "FrameworkFun.h"
#include <gl\glut.h>
#include <GL/glext.h>
#include "GlobalVar.h"
#include "DrawFunc.h"
#include <math.h>

//////创建菜单
void CreateMenus()
{
	int lightmode=glutCreateMenu(MenuSelLightMode);
	glutAddMenuEntry("Open",1);
	glutAddMenuEntry("Close",2);
	glutCreateMenu(MenuFun);
	glutAddSubMenu("Light Mode",lightmode);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//////菜单函数
void MenuFun( int value )
{
	switch (value)
	{
	
	default:
		break;
	}
	glutPostRedisplay();
}

void MenuSelLightMode( int value )
{
	switch (value)
	{
	case 1:
		{LightMode=true;break;}
	case 2:
		{LightMode=false;break;}
	default:
		break;
	}
	glutPostRedisplay();
}

///////显示函数
void Display()
{
	//glClearColor(1.0,1.0,1.0,1.0);
	glClearColor(0,0,0,1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//glEnable( GL_TEXTURE_2D | GL_DEPTH_TEST );

	glViewport( 0 , 0 , WINWIDTH , WINHEIGHT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	if( WINWIDTH < WINHEIGHT )
		glFrustum( -1 , 1 , -0.3*float(WINHEIGHT)/float(WINWIDTH) , 1.7*float(WINHEIGHT)/float(WINWIDTH) , 1 , 100 );
	else
		glFrustum( -float(WINWIDTH)/float(WINHEIGHT) , float(WINWIDTH)/float(WINHEIGHT) , -1*0.3 , 1*1.7 ,1 ,100 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt( VIEWPOS_X , VIEWPOS_Y , VIEWPOS_Z , VIEWPOS_X+cos( VIEWANGLE/180.0*pi ) , VIEWPOS_Y+sin( VIEWANGLE/180*pi ) ,VIEWPOS_Z-0.5 , 0 , 0 ,1.0 );
	//gluLookAt( VIEWPOS_X , VIEWPOS_Y , VIEWPOS_Z , 0,0,0 , 0 , 0 ,1.0 );
	CreateLight();
	if( LightMode == false )
		glDisable( GL_LIGHTING );
	glEnable(GL_DEPTH_BUFFER_BIT);

	

	////草坪和天空
	CreateLawn( LAWNSIZE , LAWNSIZE , 0 );
	CreateSky( SKYSIZE , SKYSIZE , SKYHEIGHT );
	//Robot robot;
	//robot.SolidAndriodRobot();

	glutSwapBuffers();

}

/////////闲置函数
void Idle(){}

/////////键盘事件
void Keyboard( unsigned char key , int x , int y ){}

//////////鼠标事件
void Mouse( int button , int state , int x , int y ){}

////////特殊按键函数
void SpecialKey( int key , int x , int y )
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		{VIEWANGLE+=20.0;break;}
	case GLUT_KEY_RIGHT:
		{VIEWANGLE-=20.0;break;}
	case GLUT_KEY_UP:
		{
			VIEWPOS_X+=VIEWMOVSTEP*cos(VIEWANGLE/180.0*pi);
			VIEWPOS_Y+=VIEWMOVSTEP*sin(VIEWANGLE/180.0*pi);
			break;
		}
	case GLUT_KEY_DOWN:
		{
			VIEWPOS_X-=0.1*cos(VIEWANGLE/180.0*pi);
			VIEWPOS_Y-=0.1*sin(VIEWANGLE/180.0*pi);
			break;
		}
		
	default:
		break;
	}
	glutPostRedisplay();
}

///////窗口大小变化的响应函数
void Reshape( int w , int h )
{
	WINWIDTH = w ;
	WINHEIGHT = h ;

}


/*  等待删除。。。

void makeImages()
{
	int i, j, c;
	for (i = 0; i < 64; i++) {
		for (j = 0; j < 64; j++) {
			T0[i][j][0] = (GLubyte) 0;
			T0[i][j][1] = (GLubyte) i * 5 + j * 5;
			T0[i][j][2] = (GLubyte) 0;
			T0[i][j][3] = (GLubyte) 255;
		}
	}


}
*/

