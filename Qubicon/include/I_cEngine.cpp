#include "gameapi.h"
#include "I_cEngine.h"
#include "I_cGlobal.h"
#include "include\I_cAssetManager.h"
#include <SDL_image.h>
#include "include\I_cSettings.h"
//#include "freetype.h"






//freetype::font_data our_font;	




I_cEngine::I_cEngine() 
{
 outputSurface_ = NULL; 
 run_ = true;
 showOverlay_ = true;
 current_level = NULL;
 intro_ = true;
}



I_cEngine::~I_cEngine()
{
 gAnimator->Stop();
 IMG_Quit();
}



int I_cEngine::Init(void)
{
 int err = 0;
 
 int initted = IMG_Init(IMG_INIT_PNG); 
 
if (TTF_Init() != 0)
     printf("I_cEngine::Init: TTF_Init error\n");

 
 err = InitSDL(GAMEAPI_WINDOW_W,GAMEAPI_WINDOW_H,true);
 if (err < 0)
    {
     return -1;
    }
    
 InitAssets();
 InitGL();    



 gAnimator = new I_cAnimator();  
 int ret = gAnimator->Start();
 if (ret < 0)
    {
     printf("I_cEngine::Init: Failed to start animator.\n");
     return -1;
    }
 
 //our_font.init("test.TTF", 16);		
 
 
 hud_ = new I_cHUD();		
 hud_->Init(gAssetManager->menuAssets);	      

 
 // nemoj prikazati intro
 intro_ = NULL;
 /*
 intro = new I_cIntro();
 intro->SetTextureList(gAssetManager->logoAssets);
 intro->Init();
 intro->StartIntro();
 */


 I_cLevel* level = new I_cLevel();
 level->SetTextureList(gAssetManager->cubeAssets);
 level->Init(gSettings->GetStartx(), gSettings->GetStarty(), gSettings->GetStartz(), gSettings->GetRows(), gSettings->GetCols());
 current_level = level;

 
}





int I_cEngine::InitSDL(int w, int h, bool fs)
{
 if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
     return -1;
    }
 

 screen_ = SDL_CreateWindow("Cubicon",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H,
                          SDL_WINDOW_OPENGL);

 
 
 if (!screen_) 
    {
     gData->AppendLog("SYSTEM: Unable to set video mode.");
     return -1;
    }  

 SDL_GLContext glcontext = SDL_GL_CreateContext(screen_);


  
  
 return 0; 
}


int I_cEngine::InitAssets(void)
{
 gAssetManager->LoadAssets();


 return 0;
}


//==============================================================================================//
//=====================[ INIT GL ]==============================================================//
//==============================================================================================//
bool I_cEngine::InitGL(void)
{
 glViewport(0,0,GAMEAPI_WINDOW_W,GAMEAPI_WINDOW_H);						// Reset The Current Viewport
 glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
 glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
 gluPerspective(45.0f,(GLfloat)GAMEAPI_WINDOW_W/(GLfloat)GAMEAPI_WINDOW_H,0.1f,100.0f);
 glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
 glLoadIdentity();	

	
 glDisable(GL_CULL_FACE);
 glEnable(GL_BLEND);  
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
 //glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
 glClearColor(1.0f, 1.0f, 1.0f, 1.0f);				// Black Background
 //glClearDepth(1.0f);									// Depth Buffer Setup
 glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
 glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
 glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
 
 //our_font.init("test.TTF", 16);					    //Build the freetype font

 return true;
}
//______________________________________________________________________________________________//



void I_cEngine::PushEvent(GAMEAPI_EVENT event)
{
 vEventList.push_back(event);
}



GAMEAPI_EVENT I_cEngine::PollEvent(void)
{
 GAMEAPI_EVENT popEvent = GAMEAPI_EVENT_NO_EVENT;
 if (vEventList.size() > 0)
    {
     popEvent = vEventList[vEventList.size()-1];
     vEventList.pop_back();    
    }
 return popEvent;
}



void I_cEngine::HandleEvents(void)
{
 GAMEAPI_EVENT event = PollEvent();
 
 //if (!current_level) 
 //    return;

 //float x = current_level->cursor_cube->GetPosx();
 //float y = current_level->cursor_cube->GetPosy();

 switch(event)
       {
        case GAMEAPI_EVENT_QUIT:
         run_ = false;
         break;
        

        case GAMEAPI_EVENT_KEY_LEFT:
        {
		 if (current_level)
		    {
			 I_cCube *sel_cube = GetSelectedCube();
			 if (current_level->CursorLeft() == true)
				{
				 ANIMA *anima = new ANIMA;
				 anima->pCube = sel_cube;
				 anima->type = ANIMA_TYPE_ROTATION;
				 anima->rot.direction = ROTATION_LEFT;
				 gAnimator->AddAnima(anima);
				}
			}

         break;
        }
        case GAMEAPI_EVENT_KEY_RIGHT:
        {
		 if (current_level)
		    {
			 I_cCube *sel_cube = GetSelectedCube();
			 if (current_level->CursorRight() == true) // u granicama?
				{
				 ANIMA *anima = new ANIMA;
				 anima->pCube = sel_cube;
				 anima->type = ANIMA_TYPE_ROTATION;
				 anima->rot.direction = ROTATION_RIGHT;
				 gAnimator->AddAnima(anima);
				}
			}

         break;
        }
        case GAMEAPI_EVENT_KEY_UP:
        {
		 if (current_level)
		    {
			 I_cCube *sel_cube = GetSelectedCube();
			 if (current_level->CursorUp() == true)
				{
				 ANIMA *anima = new ANIMA;
				 anima->pCube = sel_cube;
				 anima->type = ANIMA_TYPE_ROTATION;
				 anima->rot.direction = ROTATION_UP;
				 gAnimator->AddAnima(anima);
				}
			 }
         break;
        }
        case GAMEAPI_EVENT_KEY_DOWN:
        {
		 if (current_level)
		    {
			 I_cCube *sel_cube = GetSelectedCube();
			 if (current_level->CursorDown() == true)
			   {
				 ANIMA *anima = new ANIMA;
				 anima->pCube = sel_cube;
				 anima->type = ANIMA_TYPE_ROTATION;
				 anima->rot.direction = ROTATION_DOWN;
				 gAnimator->AddAnima(anima);
			   }
			}
         break;
        }

		case GAMEAPI_EVENT_KEY_START:
		{
         /*
		 hud_->Enable();
		 intro_ = false;
		 I_cLevel *level = new I_cLevel();
		 level->SetTextureList(gAssetManager->cubeAssets);
		 level->Init(gSettings->GetStartx(),gSettings->GetStarty(),gSettings->GetStartz(),gSettings->GetRows(),gSettings->GetCols());
		 current_level = level;
		 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);		
         */
		 break;
		}
        
        case GAMEAPI_EVENT_KEY_ESC:
        {
         if (!hud_->IsActive())
             hud_->Enable();
             else hud_->Disable();
         break;
        }
        
        case GAMEAPI_EVENT_MOUSE_CLICK:
        {
         if (hud_->IsActive())
            {
             hud_->OnClick(sdlEvent_.button.x,sdlEvent_.button.y);
            }
         break;
        }
        
		case GAMEAPI_EVENT_KEY_TEST_KEY:
		{
		 intro->key_test();
		}

        default: break;
       } 
}


I_cCube *I_cEngine::GetSelectedCube()
{
 int cur_x = 0, cur_y = 0;
 current_level->cursor_cube->GetCubeGridPos(cur_x,cur_y);
 return current_level->cubeGrid[cur_y][cur_x];

 return NULL; // ovdje po pravilu nebi smjeli doci
}




bool I_cEngine::IsRunning()
{
 return run_;
}


DWORD I_cEngine::Run(LPVOID)
{
 char tmp[8];
 Init();
 

 while(run_)
 {
 while(SDL_PollEvent(&sdlEvent_))  // NOTE! ako ovdje maknemo while onda cemo dobiti kontinuirani input
      {
       
	   switch (sdlEvent_.type)
			  {

			  
			   case SDL_QUIT:
			   { 
				PushEvent(GAMEAPI_EVENT_QUIT);
				break;
			   }
              
               case SDL_KEYDOWN:
               {
                switch (sdlEvent_.key.keysym.sym )
                       {
                        case SDLK_RIGHT:
                        PushEvent(GAMEAPI_EVENT_KEY_RIGHT);		
                        break;	  
                        case SDLK_UP:
                        PushEvent(GAMEAPI_EVENT_KEY_UP);		
                        break;	  
                        case SDLK_LEFT:
                        PushEvent(GAMEAPI_EVENT_KEY_LEFT);		
                        break;	  
                        case SDLK_DOWN:
                        PushEvent(GAMEAPI_EVENT_KEY_DOWN);		
                        break;	  
                        case SDLK_ESCAPE:
                        PushEvent(GAMEAPI_EVENT_KEY_ESC);	
                        break;	
						case SDLK_t:
						PushEvent(GAMEAPI_EVENT_KEY_TEST_KEY);
						break;
						case SDLK_RETURN:
						PushEvent(GAMEAPI_EVENT_KEY_START);
						break;
                       }
                break;
               } 
  
               
               case SDL_MOUSEBUTTONUP:
               {
                if (sdlEvent_.button.button == 1)  // ljevi gumb je pritisnut
                   {
                    PushEvent(GAMEAPI_EVENT_MOUSE_CLICK);	
                   }
                break;
               }
               
               case SDL_MOUSEMOTION:
               {
                printf("%d, %d\n",sdlEvent_.motion.x,sdlEvent_.motion.y);
                mouse_x_ = sdlEvent_.motion.x;
                mouse_y_ = sdlEvent_.motion.y;
                break;
               }
               
			  }      
       
       HandleEvents();

      }
       //startPicking(mouse_x_,mouse_y_);
       Render();
       
       framerate.Update();
       sprintf(tmp,"%d",framerate.GetFPS());
       //SDL_WM_SetCaption(tmp,0);       
       Sleep(1);
      }
 return 0;
}


//==============================================================================================//
//=====================[ RENDER ]===============================================================//
//==============================================================================================//
void I_cEngine::Render(void)
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear Screen And Depth Buffer
 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
 
 
 if (current_level)
    {
     current_level->Draw();
     current_level->cursor_cube->Draw(DRAW_TYPE_WIRE,0);
    }

 if (intro_ == true)
    {
	 intro->Draw();
	}
 
  HUDRender();

  int ret = framerate.GetFPS();
  char fps[32];
  sprintf(fps,"%d",ret);
  SDL_SetWindowTitle(screen_,fps);


  SDL_GL_SwapWindow(screen_);
  Sleep(1);
}



void I_cEngine::HUDRender()
{
 //hud_->Render();

}



void I_cEngine::RenderOverlay()
{

glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(10.0, 0.0);
    glVertex2f(10.0, 10.0);
    glVertex2f(0.0, 10.0);
glEnd();

}


void I_cEngine::RenderHelpText()
{

 //freetype::print(our_font, 0, 0, "alpha = %d",123);
}







