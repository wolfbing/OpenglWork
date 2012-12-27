#ifndef FRAMEWORKFUN_H
#define FRAMEWORKFUN_H

#include <string>

using namespace std;

//////事件函数
void Reshape( int w , int h );
void Keyboard( unsigned char key , int x , int y  );
void Mouse( int button , int state , int x , int y  );
void SpecialKey( int key , int x , int y );

///////
void Display();
void CreateMenus();
void MenuFun( int );
void MenuSelLightMode( int );
void Idle();

void makeImages();///等待删除。。。



#endif