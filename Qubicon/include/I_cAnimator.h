#pragma once
#include <vector>
#include "I_cCube.h"
#include "SDL_thread.h"
#include "SDL_timer.h"

using namespace std;


typedef struct ANIMA_ROTATION
{
 GAMEAPI_ROTATION direction;
 float end_;
 float current_degree_; 
}ANIMA_ROTATION;

typedef struct ANIMA_MOVEMENT
{
 GAMEAPI_MOVEMENT mov;
 float end_;
 float current_pos_;
}ANIMA_MOVEMENT;


typedef struct ANIMA
{
 I_cCube *pCube;
 GAMEAPI_ANIMA_TYPE type;
 ANIMA_ROTATION rot;
 ANIMA_MOVEMENT mov;
}ANIMA;



class I_cAnimator
{
 public:
		I_cAnimator();
	   ~I_cAnimator();
	   
	   
	    int Start(void);
	    void Stop(void);
	   
	    void AddAnima(ANIMA *anima); // dodaj qube na stack. 
	    void RemoveAnima(ANIMA *anima);  // TODO get anima count
	    int GetCubeCount(void);
	    ANIMA *GetAnima(int num);
	    void SetRunning(bool run);
	    bool GetRunning(void);
	   
 private:
         vector<ANIMA*>vAnimaList;  // trenutna lista kocaka u pokretu	   
         SDL_Thread *thread;
         static int Animate(void *ptr);
         bool running_;

 private: 
         void RemoveCube(I_cCube *cube); // kada se zavrsi rotacija/aktivnost makni kocku s stacka         
         
};


extern I_cAnimator *gAnimator;
