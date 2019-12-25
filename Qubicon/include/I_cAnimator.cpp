#include "I_cAnimator.h"
#include "gameapi.h"
#include "I_cSettings.h"
#include <SDL_thread.h>


I_cAnimator *gAnimator = NULL;

I_cAnimator::I_cAnimator()
{
}


I_cAnimator::~I_cAnimator()
{
}


int I_cAnimator::Start(void)
{
  SetRunning(true);
  thread = SDL_CreateThread(Animate, "AnimateThread", (void *)this);
 //thread = SDL_CreateThread(Animate,"",NULL);

 
 if (!thread) 
    {
     printf("SDL_CreateThread failed: %s\n", SDL_GetError());
     return -1;
    }else return 0;

}



void I_cAnimator::Stop()
{
 running_ = false;
}

void I_cAnimator::AddAnima(ANIMA *anima)
{
 // TODO: ako anima za ovu kocku postoji u listi nemoj je staviti u listu. vrati -1
 int cnt = GetCubeCount();
 for (int c=0;c<cnt;c++)
     {
      //ANIMA *ptr_anima = GetAnima(c);
      //if (ptr_anima->pCube == anima->pCube)  // nesmijemo dozvoliti da su dvije iste kocke trenutno u razlicitim animacijama
      //   return; 
     }
 
 // HACK: postavi rotaciju samo ako ne postoji
 anima->pCube->SetRotation(anima->rot.direction);  // GAMEAPI_ROTATION
 vAnimaList.push_back(anima);
}


int I_cAnimator::GetCubeCount(void)
{
 return (int)vAnimaList.size();
}

ANIMA *I_cAnimator::GetAnima(int num)
{ 
 if (num > GetCubeCount() || GetCubeCount() <= 0 ) return NULL;
 
 return vAnimaList[num];
}


void I_cAnimator::SetRunning(bool run)
{
 running_ = run;
}


bool I_cAnimator::GetRunning(void)
{
 return running_;
}


void I_cAnimator::RemoveAnima(ANIMA *anima)
{
 for (int c=0;c<GetCubeCount();c++)
     {
      ANIMA *ptr_anima = GetAnima(c);
      if (ptr_anima == anima) 
         {
          delete anima;
          vAnimaList.erase(vAnimaList.begin()+c);
          return;
         }
     }
}

int I_cAnimator::Animate(void *ptr)
{ 
 I_cAnimator *ptr_animator = (I_cAnimator*)ptr;

 while (ptr_animator->GetRunning())
       {
        size_t cube_cnt = ptr_animator->GetCubeCount();
        for (int c=0;c<ptr_animator->GetCubeCount();c++)
            {
             ANIMA *anima = ptr_animator->GetAnima(c);
             
             switch(anima->type)
                   {
                    case ANIMA_TYPE_ROTATION:
                    {
					 anima->pCube->Rotate(gSettings->GetRotSpeed());  
					 if (anima->pCube->RotationEnd()) 
					    {
					 	 ptr_animator->RemoveAnima(anima);
					    }
					 break;
					}      
					
					case ANIMA_TYPE_MOVEMENT:
					{
					 if (anima->mov.current_pos_ < anima->mov.end_)
					    {
					     float posx = anima->pCube->GetPosx();
						 posx += 0.19;
					     anima->pCube->SetPosx(posx);
						 anima->mov.current_pos_ = posx;
					    }else  ptr_animator->RemoveAnima(anima);

					
					}
					break;
					
				    default:
				    break;              
                   }

            }
        
        SDL_Delay(1);
       }
       
       
 return 0;
}

