#include "I_cHUDCube.h"



I_cHUDCube::I_cHUDCube()
{
 
}


I_cHUDCube::~I_cHUDCube()
{
}



void I_cHUDCube::Init()
{
 
}

void I_cHUDCube::Draw()
{
 glLoadIdentity();									
 glTranslatef(posx_,posy_,posz_);					
									 
 switch (rotation_)
        {
         case ROTATION_LEFT:
         case ROTATION_RIGHT:
         glRotatef(anglex_,0,1,0);            			
         break;
         case ROTATION_UP:
         case ROTATION_DOWN:
         glRotatef(angley_,1,0,0);              
         default:
         break;
        }

	glBindTexture(GL_TEXTURE_2D, texture_list[0]);
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glEnd();

}