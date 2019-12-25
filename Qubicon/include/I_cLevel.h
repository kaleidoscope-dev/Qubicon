#pragma once
#include <vector>
#include "I_cCube.h"

using namespace std;

class I_cLevel
{
 public:
        I_cLevel();
       ~I_cLevel();
       
 public:
        void Init(float startx, float starty, float startz, int rows, int cols);
        void Draw(); 
        bool CursorRight();
        bool CursorLeft();
        bool CursorUp();
        bool CursorDown();
        void SetTextureList(GLuint *tex);
        
       
 
 //private:
         float startx_,starty_,startz_;
         int rows_,cols_;
		 vector<I_cCube *>vCubeList;
		 I_cCube *cursor_cube;
		 I_cCube ***cubeGrid;
		 GLuint *texture_list;
		 
        
       
};