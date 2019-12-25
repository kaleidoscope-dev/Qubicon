#pragma once
#include "qubicon.h"
#include "gameapi.h"

//#include <gl\glaux.h>		// Header File For The Glaux Library
/*
Primarni bitmap objekt. AssetManager nasljedjuje ovaj objekt
Ovo bi trebalo drugacije napraviti. AssetManager ne bi smio nasljedivati od ovog.
*/

class I_cBitmap
{
 public:
        I_cBitmap();
       ~I_cBitmap();
       
        int Load(string path, GLuint *texture);
        int LoadGLTexturesPNG(GLuint *p_tex, string file);
        virtual void Draw(void);


 private:
         SDL_Surface *surface;       
         SDL_Rect bitmapRect;
         
         
         
           
};