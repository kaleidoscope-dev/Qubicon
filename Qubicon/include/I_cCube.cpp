#include "qubicon.h"
#include "I_cCube.h"
#include "I_cAssetManager.h"


I_cCube::I_cCube()
{
 posx_ = 0;
 posy_ = 0;
 posz_ = 0;
 rotx_ = 0;
 roty_ = 0;
 rotz_ = 0; 
 gridX_ = 0;
 gridY_ = 0;
 endRotx_ =0;
 endRoty_ =0;
 endRotz_ =0;
 anglex_ = 0;
 angley_ = 0;
 endAnglex_ = 0;
 endAngley_ = 0;
}


I_cCube::~I_cCube()
{
}


void I_cCube::SetPos(float x, float y, float z)
{
 posx_ = x;
 posy_ = y;
 posz_ = z;
}

void I_cCube::SetPosx(float x)
{
 posx_ = x;
}


void I_cCube::SetCubeGridPos(int x, int y)
{
 gridX_ += x;
 gridY_ += y;
}


void I_cCube::GetCubeGridPos(int &x, int &y)
{
 x = gridX_;
 y = gridY_;
}


void I_cCube::SetRot(float x, float y, float z)
{
 rotx_ = x;
 roty_ = y;
 rotz_ = z; 
}



void I_cCube::SetRotation(GAMEAPI_ROTATION rotation) 
{
 rotation_ = rotation;
 switch(rotation_)
       {
        case ROTATION_RIGHT:
        endAnglex_ += 90;
        break;
        case ROTATION_LEFT:
        endAnglex_ -= 90;        
        break;
        case ROTATION_UP:
        endAngley_ -= 90;
        break;
        case ROTATION_DOWN:
        endAngley_ += 90;        
        break;
        
        default: break;
       }
}

void I_cCube::Rotate(float degree)
{
 switch(rotation_)
       {
        case ROTATION_RIGHT:
        anglex_ += degree;
        if (anglex_ > endAnglex_)  // kraj
           {
            anglex_ = endAnglex_;
           }
        break;
        case ROTATION_LEFT:
        anglex_ -= degree;
        if (anglex_ < endAnglex_)  // kraj
           {
            anglex_ = endAnglex_;
           }
        break;
        
        case ROTATION_UP:
        angley_ -= degree;
        if (angley_ < endAngley_)  // kraj
           {
            angley_ = endAngley_;
           }
        break;
        case ROTATION_DOWN:
        angley_ += degree;
        if (angley_ > endAngley_)  // kraj
           {
            angley_ = endAngley_;
           }
        break;        
        default: break;
       }

}


bool I_cCube::RotationEnd()
{
 if (anglex_ == endAnglex_ && angley_ == endAngley_)
    {
      return true;
     }
 return false;
}	                      

void I_cCube::Draw(GAMEAPI_DRAW_TYPE draw_type, int letter)
{
 switch (draw_type)
        {
         case DRAW_TYPE_WIRE:
		  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		 DrawWire();
		  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		  break;

		case DRAW_TYPE_POLY:
		 DrawPoly();
		break;
		case DRAW_TYPE_TEX:
		 glEnable(GL_TEXTURE_2D);
		 DrawTex();
		 glDisable(GL_TEXTURE_2D);
		break;

		 case DRAW_TYPE_INTRO:
		  glEnable(GL_TEXTURE_2D);
		  DrawIntro(letter);
		  glDisable(GL_TEXTURE_2D);
		 break;

		 break;
	   }
}



void I_cCube::DrawPoly()
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
            break;
            default:
            break;
           }
	
	
	
	glBegin(GL_QUADS);									
		glColor3f(0.0f,0.0f,1.0f);						// Set The Color To Blue
		glVertex3f( 1.0f, 1.0f,-1.0f);					
		glVertex3f(-1.0f, 1.0f,-1.0f);					
		glVertex3f(-1.0f, 1.0f, 1.0f);				
		glVertex3f( 1.0f, 1.0f, 1.0f);					
		glColor3f(1.0f,0.5f,0.0f);						// Set The Color To Orange
		glVertex3f( 1.0f,-1.0f, 1.0f);					
		glVertex3f(-1.0f,-1.0f, 1.0f);					
		glVertex3f(-1.0f,-1.0f,-1.0f);					
		glVertex3f( 1.0f,-1.0f,-1.0f);					
		glColor3f(1.0f,0.0f,0.0f);						// Set The Color To Red
		glVertex3f( 1.0f, 1.0f, 1.0f);					
		glVertex3f(-1.0f, 1.0f, 1.0f);					
		glVertex3f(-1.0f,-1.0f, 1.0f);					
		glVertex3f( 1.0f,-1.0f, 1.0f);					
		glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Yellow
		glVertex3f( 1.0f,-1.0f,-1.0f);					
		glVertex3f(-1.0f,-1.0f,-1.0f);					
		glVertex3f(-1.0f, 1.0f,-1.0f);					
		glVertex3f( 1.0f, 1.0f,-1.0f);					
		glColor3f(0.0f,0.0f,1.0f);						// Set The Color To Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);					
		glVertex3f(-1.0f, 1.0f,-1.0f);				
		glVertex3f(-1.0f,-1.0f,-1.0f);					
		glVertex3f(-1.0f,-1.0f, 1.0f);					
		glColor3f(1.0f,0.0f,1.0f);						// Set The Color To Violet
		glVertex3f( 1.0f, 1.0f,-1.0f);					
		glVertex3f( 1.0f, 1.0f, 1.0f);					
		glVertex3f( 1.0f,-1.0f, 1.0f);				
		glVertex3f( 1.0f,-1.0f,-1.0f);				
	glEnd();	
	

}




void I_cCube::DrawWire()
{

	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(posx_,posy_,posz_);						// Move Right 1.5 Units And Into The Screen 7.0
											// Done Drawing The Quad
	
	
	glBegin(GL_QUADS);									// Draw A Quad
		glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Blue
		glVertex3f( 1.1f, 1.1f,-1.0f);					// Top Right Of The Quad (Top)
		glVertex3f(-1.1f, 1.1f,-1.0f);					// Top Left Of The Quad (Top)
		glVertex3f(-1.1f, 1.1f, 1.0f);					// Bottom Left Of The Quad (Top)
		glVertex3f( 1.1f, 1.1f, 1.0f);					// Bottom Right Of The Quad (Top)
		glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Blue
		glVertex3f( 1.1f,-1.1f, 1.0f);					// Top Right Of The Quad (Bottom)
		glVertex3f(-1.1f,-1.1f, 1.0f);					// Top Left Of The Quad (Bottom)
		glVertex3f(-1.1f,-1.1f,-1.0f);					// Bottom Left Of The Quad (Bottom)
		glVertex3f( 1.1f,-1.1f,-1.0f);					// Bottom Right Of The Quad (Bottom)
		glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Blue
		glVertex3f( 1.1f, 1.1f, 1.0f);					// Top Right Of The Quad (Front)
		glVertex3f(-1.1f, 1.1f, 1.0f);					// Top Left Of The Quad (Front)
		glVertex3f(-1.1f,-1.1f, 1.0f);					// Bottom Left Of The Quad (Front)
		glVertex3f( 1.1f,-1.1f, 1.0f);					// Bottom Right Of The Quad (Front)
		glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Blue
		glVertex3f( 1.1f,-1.1f,-1.0f);					// Top Right Of The Quad (Back)
		glVertex3f(-1.1f,-1.1f,-1.0f);					// Top Left Of The Quad (Back)
		glVertex3f(-1.1f, 1.1f,-1.0f);					// Bottom Left Of The Quad (Back)
		glVertex3f( 1.1f, 1.1f,-1.0f);					// Bottom Right Of The Quad (Back)
		glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Blue
		glVertex3f(-1.1f, 1.1f, 1.0f);					// Top Right Of The Quad (Left)
		glVertex3f(-1.1f, 1.1f,-1.0f);					// Top Left Of The Quad (Left)
		glVertex3f(-1.1f,-1.1f,-1.0f);					// Bottom Left Of The Quad (Left)
		glVertex3f(-1.1f,-1.1f, 1.0f);					// Bottom Right Of The Quad (Left)
		glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Blue
		glVertex3f( 1.1f, 1.1f,-1.0f);					// Top Right Of The Quad (Right)
		glVertex3f( 1.1f, 1.1f, 1.0f);					// Top Left Of The Quad (Right)
		glVertex3f( 1.1f,-1.1f, 1.0f);					// Bottom Left Of The Quad (Right)
		glVertex3f( 1.1f,-1.1f,-1.0f);					// Bottom Right Of The Quad (Right)
	glEnd();	
	
 // moramo vratiti boju na bijelu, jer se inace poremeti prikaz textura
 glColor3f(1.0f, 1.0f, 1.0f);	
	
glEnd();

}



void I_cCube::DrawTex()
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

	glBindTexture(GL_TEXTURE_2D, texture_list[TEX_FRONT]);
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture_list[TEX_BACK]);
		// Back Face
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glEnd();
	
		// Top Face
	glBindTexture(GL_TEXTURE_2D, texture_list[TEX_UP]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
     glEnd();		
		// Bottom Face
	glBindTexture(GL_TEXTURE_2D, texture_list[TEX_DOWN]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
     glEnd();	
     		
		// Right face
	glBindTexture(GL_TEXTURE_2D, texture_list[TEX_RIGHT]);
	glBegin(GL_QUADS);			
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
     glEnd();			
		// Left Face
	glBindTexture(GL_TEXTURE_2D, texture_list[TEX_LEFT]);
	glBegin(GL_QUADS);			
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
        
	
 
}



void I_cCube::DrawIntro(int letter)
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

	glBindTexture(GL_TEXTURE_2D, texture_list[TEX_W]);
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture_list[TEX_W]);
		// Back Face
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glEnd();
	
		// Top Face
	glBindTexture(GL_TEXTURE_2D, texture_list[TEX_W]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
     glEnd();		
		// Bottom Face
	glBindTexture(GL_TEXTURE_2D, texture_list[TEX_W]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
     glEnd();	
     		
		// Right face
	glBindTexture(GL_TEXTURE_2D, texture_list[TEX_W]);
	glBegin(GL_QUADS);			
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
     glEnd();			
		// Left Face
	glBindTexture(GL_TEXTURE_2D, texture_list[letter]);
	glBegin(GL_QUADS);			
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
         
}



float I_cCube::GetPosx(void)
{
 return posx_;
}


float I_cCube::GetPosy(void)
{
 return posy_;
}



// sprite moda explicitno postaviti koju texturu prikazujemo
void I_cCube::SetTextureList(GLuint *tex)
{
 texture_list = tex;
}


