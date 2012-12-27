
#include "stdafx.h"
#include "DrawFunc.h"
#include <gl\glut.h>
#include "GlobalVar.h"
#include <GL/glext.h>

#include <string>
using namespace std;

/////画草坪
void CreateLawn( float l , float w ,float h )
{
	char * cao="cao.bmp";
	TexLawn=LoadTex(cao);
	glBindTexture( GL_TEXTURE_2D , TexLawn );
	glEnable( GL_TEXTURE_2D );
	//glColor3d( 1 , 0 , 0 );	
	glBegin( GL_POLYGON );
	glTexCoord2f( 1.0 , 0.0 );
	glVertex3d( l , w , h );
	glTexCoord2f( 1 , 1.0 );
	glVertex3d( -l , w , h );
	glTexCoord2f( 0.0 , 1.0 );
	glVertex3d( -l , -w , h );
	glTexCoord2f( 0.0 , 0.0 );
	glVertex3d( l , -w , h );
	glEnd();
}


///////画天空
void CreateSky( float l , float w , float h )
{
	char * tian="tian.bmp";
	TexSky=LoadTex( tian );
	glBindTexture( GL_TEXTURE_2D , TexSky );
	glEnable(GL_TEXTURE_2D);
	glBegin( GL_POLYGON );
	glTexCoord2f( 1.0 , 0.0 );
	glVertex3d( l , w , h );
	glTexCoord2f( 1.0 , 1.0 );
	glVertex3d( -l , w , h );
	glTexCoord2f( 0.0 , 1.0 );
	glVertex3d( -l , -w , h );
	glTexCoord2f( 0.0 , 0.0 );
	glVertex3d( l , -w , h );
	glEnd();

}

unsigned int LoadTex(char * Image)
{
    unsigned int Texture;

    FILE* img = NULL;
    //img = fopen(Image.c_str(),"rb");
	fopen_s( &img , Image , "rb" );

    unsigned long bWidth = 0;    
    unsigned long bHeight = 0;    
    DWORD size = 0;    

    fseek(img,18,SEEK_SET);
    fread(&bWidth,4,1,img);
    fread(&bHeight,4,1,img);
    fseek(img,0,SEEK_END);
    size = ftell(img) - 54;

    unsigned char *data = (unsigned char*)malloc(size);

    fseek(img,54,SEEK_SET);    // image data
    fread(data,size,1,img);

    fclose(img);

    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bWidth, bHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	
    if (data)
        free(data);
    
    return Texture;
}


void CreateLight()
{
	glEnable( GL_LIGHTING );
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE , GL_FALSE );
	////环境光
	GLfloat global_ambient[4]={ 1.0 , 1.0 , 1.0 , 1.0 };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT , global_ambient );
	///光源0
	GLfloat light0_ambient[4]={ 1.0 , 1.0 , 1.0 ,1.0 };
	GLfloat light0_diffuse[4]={ 1.0 , 1.0 , 1.0 ,1.0 };
	GLfloat light0_specular[4]={ 1.0 , 1.0 , 1.0 ,1.0 };
	GLfloat light0_position[4]={ 0.0 , 4.0 , 3.0 , 1.0 };
	glLightfv( GL_LIGHT0 , GL_AMBIENT , light0_ambient );
	glLightfv( GL_LIGHT0 , GL_DIFFUSE , light0_diffuse );
	glLightfv( GL_LIGHT0 , GL_SPECULAR , light0_specular );
	glLightfv( GL_LIGHT0 , GL_POSITION , light0_position );
	glEnable( GL_LIGHT0 );

	

	
}


void SolidHalfSphere(double radius , int slices , int stacks )
{
	double SliceAngle=pi*2/slices;
	double StackAngle=pi/2/stacks;
	for ( int i=0; i != stacks ; ++i )
	{
		for ( int j=0; j != slices ; ++j )
		{
			glBegin(GL_POLYGON);
			glNormal3d(radius*cos(StackAngle*i)*cos(SliceAngle*j),
				radius*cos(StackAngle*i)*sin(SliceAngle*j),radius*sin(StackAngle*i));
			glVertex3d(radius*cos(StackAngle*i)*cos(SliceAngle*j),
				radius*cos(StackAngle*i)*sin(SliceAngle*j),radius*sin(StackAngle*i));
			glNormal3d(radius*cos(StackAngle*i)*cos(SliceAngle*(j+1)),
				radius*cos(StackAngle*i)*sin(SliceAngle*(j+1)),radius*sin(StackAngle*i));
			glVertex3d(radius*cos(StackAngle*i)*cos(SliceAngle*(j+1)),
				radius*cos(StackAngle*i)*sin(SliceAngle*(j+1)),radius*sin(StackAngle*i));
			glNormal3d(radius*cos(StackAngle*(i+1))*cos(SliceAngle*(j+1)),
				radius*cos(StackAngle*(i+1))*sin(SliceAngle*(j+1)),radius*sin(StackAngle*(i+1)));
			glVertex3d(radius*cos(StackAngle*(i+1))*cos(SliceAngle*(j+1)),
				radius*cos(StackAngle*(i+1))*sin(SliceAngle*(j+1)),radius*sin(StackAngle*(i+1)));
			glNormal3d(radius*cos(StackAngle*(i+1))*cos(SliceAngle*j),
				radius*cos(StackAngle*(i+1))*sin(SliceAngle*j),radius*sin(StackAngle*(i+1)));
			glVertex3d(radius*cos(StackAngle*(i+1))*cos(SliceAngle*j),
				radius*cos(StackAngle*(i+1))*sin(SliceAngle*j),radius*sin(StackAngle*(i+1)));
			glEnd();
		}
	}
	glBegin(GL_POLYGON);
	glNormal3d(0.0,0.0,-1.0);
	for ( int i=0; i != slices ; ++ i )
	{
		
		glVertex3d(radius*cos(SliceAngle*i),radius*sin(SliceAngle*i),0.0);
	}
	glEnd();
}

void SolidCylinder(double radius ,double height , int slices)
{
	double SliceAngle=2*pi/slices;
	for ( int i=0; i!=slices ; ++i )
	{
		glBegin(GL_POLYGON);
		glNormal3d(radius*cos(SliceAngle*i),radius*sin(SliceAngle*i),0);
		glVertex3d(radius*cos(SliceAngle*i),radius*sin(SliceAngle*i),0);
		glNormal3d(radius*cos(SliceAngle*(i+1)),radius*sin(SliceAngle*(i+1)),0);
		glVertex3d(radius*cos(SliceAngle*(i+1)),radius*sin(SliceAngle*(i+1)),0);
		glNormal3d(radius*cos(SliceAngle*(i+1)),radius*sin(SliceAngle*(i+1)),0);
		glVertex3d(radius*cos(SliceAngle*(i+1)),radius*sin(SliceAngle*(i+1)),height);
		glNormal3d(radius*cos(SliceAngle*i),radius*sin(SliceAngle*i),0);
		glVertex3d(radius*cos(SliceAngle*i),radius*sin(SliceAngle*i),height);
		glEnd();
	}
	glBegin(GL_POLYGON);
	glNormal3d(0,0,-1);
	for (int i=0; i!= slices ; ++i )
	{
		glVertex3d(radius*cos(i*SliceAngle),radius*sin(i*SliceAngle),0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3d(0,0,1);
	for (int i=0; i!= slices ; ++i )
	{
		glVertex3d(radius*cos(i*SliceAngle),radius*sin(i*SliceAngle),height);
	}
	glEnd();


}

void SolidRoundCylinder(double radius ,double height , int slices , int stacks)
{
	SolidCylinder(radius,height,slices);
    glPushMatrix();
    glTranslated(0.0,0.0,height);
    SolidHalfSphere(radius,slices,stacks);
    glPopMatrix();
    glPushMatrix();
    glRotated(180,1,0,0);
    SolidHalfSphere(radius,slices,stacks);
    glPopMatrix();
}

void FanCircle(float radius,int slices)
{
	float a=2*pi/slices;
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0;i!=slices;++i)
	{
		glVertex3d(radius*cos(a*i),radius*sin(a*i),0);
	}
	glEnd();

}


///////  ----------------------机器人类  BEGIN   ------------------

Robot::Robot()
{
	radius=0.8;
	matcolor[0]=0.0 ;
	matcolor[1]=1.0 ;
	matcolor[2]=0.0 ;
	matcolor[3]=1.0 ;
	matshininess=100.0;
	LeftArmAngle=0;
	RightArmAngle=0;
	LeftLegAngle=0;
	RightLegAngle=0;

}


void Robot::SolidHead(double radius, int slices , int stacks )
{
    double AntennaAngle=pi/6.0;
    double AntennaLen=radius/2.6;
    double AntennaRadius=AntennaLen/10.0;
    int AntennaSlices=slices/2;
    int AntennaStacks=stacks/2;
    double EyeRadius=radius/10;
	SolidHalfSphere(radius,slices,stacks);
	glColor3d(1,1,1);
	float x=1;
	float y=-0.8;
	float z=0.8;
	float s=sqrt(pow(x,2)+pow(y,2)+pow(z,2));
	glPushMatrix();
	glTranslated(radius*x/s,radius*y/s,radius*z/s);
	glRotated(180.0/pi*acos(z/s),-y,x,0);
	DefMat_RobotEye();
	FanCircle(EyeRadius,20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(radius*x/s,-radius*y/s,radius*z/s);
	glRotated(180.0/pi*acos(z/s),y,x,0);
	FanCircle(EyeRadius,20);
	glPopMatrix();

	glColor3d(0,1,0);
	DefMat_Robot();
    glPushMatrix();
    glTranslated(0,-radius*sin(AntennaAngle),radius*cos(AntennaAngle));
    glRotated(AntennaAngle*180.0/pi,1,0,0);
	SolidRoundCylinder(AntennaRadius,AntennaLen,AntennaSlices,AntennaStacks);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,radius*sin(AntennaAngle),radius*cos(AntennaAngle));
    glRotated(-AntennaAngle*180.0/pi,1,0,0);
	SolidRoundCylinder(AntennaRadius,AntennaLen,AntennaSlices,AntennaStacks);
    glPopMatrix();
}

void Robot::DefMat_RobotEye()
{
	GLfloat mat_ambient[]={1,1,1,1};
	GLfloat mat_diffuse[]={1,1,1,1};
	GLfloat mat_specular[]={1,1,1,1};
	GLfloat mat_shininess=80.0;
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialf(GL_FRONT,GL_SHININESS,mat_shininess);
}


void Robot::DefMat_Robot()
{
	glMaterialfv(GL_FRONT,GL_AMBIENT,matcolor);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,matcolor);
	glMaterialfv(GL_FRONT,GL_SPECULAR,matcolor);
	glMaterialf(GL_FRONT,GL_SHININESS,matshininess);
}

void Robot::SolidAndriodRobot()
{
	
	glColor3d(0,1,0);
    double Gap=radius*3.0/25.0;
    double BodyRadius=radius;
    double BodyHeight=radius*1.6;
    int BodySlices=BodyRadius/0.5*40;
    int BodyStacks=BodyRadius/0.5*20;
    double HeadRadius=radius;
    double ArmRadius=radius/5.0;
    double ArmLen=radius;
    int ArmSlices=ArmRadius/0.5*80;
    int ArmStacks=ArmRadius/0.5*40;
    double LegRadius=radius/5.0;
    double LegLen=radius*3.0/5.0;
    int LegSlices=LegRadius/0.5*80;
    int LegStacks=LegRadius/0.5*40;
    int HeadSlices=BodySlices;
	glTranslated(0,0,LegLen+LegRadius);
	DefMat_Robot();
	SolidCylinder(BodyRadius,BodyHeight,BodySlices);
    glPushMatrix();
    glTranslated(0,0,BodyHeight+Gap);
	SolidHead(HeadRadius,HeadSlices,10);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,-(BodyRadius+Gap+ArmRadius),BodyHeight-ArmRadius-ArmLen);
	
	glTranslated(0,0,ArmLen);
	glRotated(RightArmAngle,0,1,0);
	glTranslated(0,0,-ArmLen);
	SolidRoundCylinder(ArmRadius,ArmLen,ArmSlices,ArmStacks); 
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,(BodyRadius+Gap+ArmRadius),BodyHeight-ArmRadius-ArmLen);


	glTranslated(0,0,ArmLen);
	glRotated(LeftArmAngle,0,1,0);
	glTranslated(0,0,-ArmLen);
	SolidRoundCylinder(ArmRadius,ArmLen,ArmSlices,ArmStacks);
	glPopMatrix();
    glPushMatrix();
    glTranslated(0,-LegRadius*2,-LegLen);
		
	glTranslated(0,0,LegLen);
	glRotated(RightLegAngle,0,1,0);
	glTranslated(0,0,-LegLen);

	SolidRoundCylinder(LegRadius,LegLen,LegSlices,LegStacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,LegRadius*2,-LegLen);
	
	
	glTranslated(0,0,LegLen);
	glRotated(LeftLegAngle,0,1,0);
	glTranslated(0,0,-LegLen);
	
	SolidRoundCylinder(LegRadius,LegLen,LegSlices,LegStacks);
    glPopMatrix();
	
	glColor3d(1,1,1);

}


///////////  ------------------------机器人类  END -------------------


