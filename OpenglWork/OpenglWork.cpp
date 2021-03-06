// OpenglWork.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <gl\glut.h>
#include "GlobalVar.h"
#include "FrameworkFun.h"
#include "DrawFunc.h"

int _tmain(int argc, char * argv[])
{
	/*  ----------各种初始化---------------
	
	初始化窗口大小,位置，
	创建窗口
	设置显示模式
	启用各种功能
	*/
	glutInit( & argc , argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
	glEnable( GL_DEPTH_TEST | GL_TEXTURE_2D );
	glutInitWindowSize( WINWIDTH , WINHEIGHT );
	glutCreateWindow( "OPENGL" );

	/*  ------------各种事件响应------------
	窗口大小变化
	鼠标事件
	键盘事件

	*/
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutMouseFunc(Mouse);

	/* -----------定义菜单-----------
	*/
	CreateMenus();
	

	/*  -------------显示函数---------------
	显示函数
	空闲函数
	事件循环
	*/
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutMainLoop();

	return 0;

}