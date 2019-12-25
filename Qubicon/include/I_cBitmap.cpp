#include "I_cBitmap.h"
#include "I_cGlobal.h"
#include <SDL_image.h>
//#include <gl\glaux.h>		// Header File For The Glaux Library

I_cBitmap::I_cBitmap()
{
}


I_cBitmap::~I_cBitmap()
{
}



//======================================================================================// 
//===================[ LOAD IMAGE FROM DISK ]===========================================// 
// Ucitava bmp sliku s diska. koristeci SDL_Image lib
// openGL koristi texture tako da ih binda na GLuint texID
// Prvo se generira textura s glGenTextures(1,texture);
// i onda se binda na texture_id koji je prametar u ovoj funkciji. 
// Asset Manager dalje sprema tex_id u svoje liste text_Id-eva
// TODO:
// - sto se desava ako nema slike?
//======================================================================================// 
int I_cBitmap::Load(string path, GLuint *texture)
{

 GLenum texture_format =0;
 GLint  nOfColors=0;
 
 surface = IMG_Load(path.c_str());

 //surface = SDL_LoadBMP(path.c_str());


 nOfColors = surface->format->BytesPerPixel;


 if (nOfColors == 4)     // contains an alpha channel
    {
     if (surface->format->Rmask == 0x000000ff)
         texture_format = GL_RGBA;
     else 
         texture_format = GL_BGRA;
   } else if (nOfColors == 3)     // no alpha channel
             {
              if (surface->format->Rmask == 0x000000ff)
                  texture_format = GL_RGB;
              else
                  texture_format = GL_BGR;
            } else {
                    gData->AppendLog("LOADBMP: warning: the image is not truecolor..  this will probably break\n");
                    // this error should not go unhandled
                   } 


 glGenTextures(1,texture);  // generiraj texturu
 glBindTexture( GL_TEXTURE_2D, *texture );  // ovo je 2D textura
 
 // Set the texture's stretching properties
 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); 
 
 // opisi kako ce openGL koristiti ovu texturu
 glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,texture_format, GL_UNSIGNED_BYTE, surface->pixels ); 

 // velicina slike
 bitmapRect.x = 0;
 bitmapRect.y = 0;
 bitmapRect.w = surface->w;
 bitmapRect.h = surface->h;

 if (surface) 
    { 
	 SDL_FreeSurface( surface );
    } 
    
 return 0;
}





int I_cBitmap::LoadGLTexturesPNG(GLuint *p_tex, string file)									// Load Bitmaps And Convert To Textures
{

 GLenum texture_format =0;
 GLint  nOfColors=0;
 
 SDL_Surface *surface = IMG_Load(file.c_str());



 nOfColors = surface->format->BytesPerPixel;
 if (nOfColors == 4)     // contains an alpha channel
    {
     if (surface->format->Rmask == 0x000000ff)
         texture_format = GL_RGBA;
     else 
         texture_format = GL_BGRA;
   } else if (nOfColors == 3)     // no alpha channel
             {
              if (surface->format->Rmask == 0x000000ff)
                  texture_format = GL_RGB;
              else
                  texture_format = GL_BGR;
            } else {
                    gData->AppendLog("LOADBMP: warning: the image is not truecolor..  this will probably break\n");
                    // this error should not go unhandled
                   } 


 GLenum enumerr = glGetError();
 const GLubyte *errstr =  gluErrorString(enumerr); 

 glGenTextures(1, p_tex);  // generiraj texturu
 glBindTexture( GL_TEXTURE_2D, *p_tex);  // ovo je 2D textura

 
 // Set the texture's stretching properties
 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); 
 
 // opisi kako ce openGL koristiti ovu texturu
 glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,texture_format, GL_UNSIGNED_BYTE, surface->pixels ); 


 if (surface) 
    { 
	 SDL_FreeSurface( surface );
    } 
 return 0;
}


void I_cBitmap::Draw()
{
}
