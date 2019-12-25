#include "I_cLevel.h"
#include "I_cAssetManager.h"
#include "I_cSettings.h"


I_cLevel::I_cLevel()
{
}


I_cLevel::~I_cLevel()
{
}


void I_cLevel::Init(float startx, float starty, float startz, int rows, int cols)
{
 startx_ = startx;
 starty_ = starty;
 startz_ = startz;
 rows_ = rows;
 cols_ = cols;

 cubeGrid = new I_cCube**[rows_];
 for (int c=0;c<rows_;c++)
      cubeGrid[c] = new I_cCube*[cols_];
      

 float px = startx_, py = starty_;
 for (int y=0; y<rows_; y++)
     {
      for (int x=0; x<cols_; x++)
          {
           I_cCube *cube = new I_cCube();
           cube->SetPos(px,py,startz_);
           cube->SetCubeGridPos(x,y);
           cube->SetTextureList(texture_list);
           cubeGrid[y][x] = cube;
           vCubeList.push_back(cube);
           px+=gSettings->GetDistance();
          }
      py -= gSettings->GetDistance();
      px = startx_;
     }


 cursor_cube = new I_cCube();
 cursor_cube->SetPos(startx_,starty_,startz_);
 cursor_cube->SetCubeGridPos(0,0);     
   
}       


void I_cLevel::SetTextureList(GLuint *tex)
{
 texture_list = tex;
}


void I_cLevel::Draw()
{
 for (int c=0;c<vCubeList.size();c++)
     {
      I_cCube *qube = vCubeList[c];
      qube->Draw(DRAW_TYPE_TEX,0);
     }
 
}



bool I_cLevel::CursorRight()
{
 int posx,posy;
 cursor_cube->GetCubeGridPos(posx,posy);
 if (posx+1 > cols_-1) return false;
 
 float x = cursor_cube->GetPosx();
 float y = cursor_cube->GetPosy(); 
 cursor_cube->SetPos(x+gSettings->GetDistance(),y,startz_);
 cursor_cube->SetCubeGridPos(1,0);
 
 return true;
}

bool I_cLevel::CursorLeft()
{
 int posx,posy;
 cursor_cube->GetCubeGridPos(posx,posy);
 if (posx-1 < 0) return false;
 
 float x = cursor_cube->GetPosx();
 float y = cursor_cube->GetPosy(); 
 cursor_cube->SetPos(x-gSettings->GetDistance(),y,startz_);      
 cursor_cube->SetCubeGridPos(-1,0);
 return true;
}

bool I_cLevel::CursorUp()
{
 int posx,posy;
 cursor_cube->GetCubeGridPos(posx,posy);
 if (posy-1 < 0) return false;
 
 float x = cursor_cube->GetPosx();
 float y = cursor_cube->GetPosy(); 
 cursor_cube->SetPos(x,y+gSettings->GetDistance(),startz_);
 cursor_cube->SetCubeGridPos(0,-1);
 return true;
}

bool I_cLevel::CursorDown()
{
 int posx,posy;
 cursor_cube->GetCubeGridPos(posx,posy);
 if (posy+1 > rows_-1) return false;
 
 float x = cursor_cube->GetPosx();
 float y = cursor_cube->GetPosy(); 
 cursor_cube->SetPos(x,y-gSettings->GetDistance(),startz_);
 cursor_cube->SetCubeGridPos(0,1);
 return true;
}



