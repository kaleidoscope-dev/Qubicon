#pragma once
#include <vector>
#include "gamedef.h"
#include "I_cFrame.h"
#include "Thread.h"
#include "Framerate.h"
#include "I_cCube.h"
#include "I_cAnimator.h"
#include "I_cLevel.h"
#include "I_cHUD.h"
#include <gl\glu.h>			// Header File For The GLu32 Library
//#include <gl\glaux.h>		// Header File For The Glaux Library
#include "I_cIntro.h"

class I_cEngine: public CThread
{
 public:
		I_cEngine();
	   ~I_cEngine();
	   
        int Init(void);	   
	   
	    void HandleEvents(void);
	   
	   int InitSDL(int w, int h, bool fs);
	   bool InitGL(void);
	   int InitAssets(void);
	   
	   void PushEvent(GAMEAPI_EVENT event);
	   GAMEAPI_EVENT PollEvent(void);
	   
	   I_cCube *GetSelectedCube();
	   
	   

       bool IsRunning();
       
 
 vector<GAMEAPI_EVENT>vEventList;
 
 SDL_Surface *outputSurface_;	  
 SDL_Window *screen_;
 

  I_cLevel *current_level;

 private:
         DWORD Run(LPVOID);
         void Render();
         void HUDRender();
         
         void RenderOverlay();
         void RenderHelpText();
         

         
 private:
         bool run_;   
         Framerate framerate;    
         SDL_Event sdlEvent_; 
         bool showOverlay_;
         I_cHUD *hud_;
         int mouse_x_,mouse_y_;
         I_cIntro *intro;
		 bool intro_;
         
 
};