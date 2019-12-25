#include "I_cIntro.h"
#include "I_cSettings.h"
#include "gameapi.h"


I_cIntro::I_cIntro()
{
}


I_cIntro::~I_cIntro()
{
}


void I_cIntro::Init(void)
{
 for (int c = 0; c < 7; c++)
 {
  cube_title[c] = new I_cCube();
  cube_title[c]->SetPos(-16.5, 0, gSettings->GetStartz());
  cube_title[c]->SetTextureList(texture_list);
 }

}


int I_cIntro::StartIntro(void)
{
 thread = SDL_CreateThread(RunIntro, "IntroThread", (void *)this);

 if (!thread)
 {
  printf("SDL_CreateThread failed: %s\n", SDL_GetError());
  return -1;
 }
 else return 0;


 RunIntro(this);


}


void I_cIntro::SetTextureList(GLuint *tex)
{
 texture_list = tex;
}


void I_cIntro::Draw(void)
{

 cube_title[0]->Draw(DRAW_TYPE_INTRO,TEX_N);
 cube_title[1]->Draw(DRAW_TYPE_INTRO,TEX_O);
 cube_title[2]->Draw(DRAW_TYPE_INTRO,TEX_C);
 cube_title[3]->Draw(DRAW_TYPE_INTRO,TEX_I);
 cube_title[4]->Draw(DRAW_TYPE_INTRO,TEX_B);
 cube_title[5]->Draw(DRAW_TYPE_INTRO,TEX_U);
 cube_title[6]->Draw(DRAW_TYPE_INTRO,TEX_C);
}



int I_cIntro::RunIntro(void *ptr)
{
 I_cIntro *intro = (I_cIntro*)ptr;

 intro->RunMovement();
 intro->RunRotation();
 return 0;
}


void I_cIntro::RunMovement(void)
{
 float pos = 23.0;
 for (int c = 0; c < 7; c++,pos-=2.1)
 {
  ANIMA *anima = new ANIMA;

  ANIMA_MOVEMENT mov;
  mov.mov = MOVEMENT_RIGHT;
  mov.current_pos_ = cube_title[c]->GetPosx();
  mov.end_ = cube_title[c]->GetPosx() + pos;

  anima->mov = mov;
  anima->pCube = cube_title[c];
  anima->type = ANIMA_TYPE_MOVEMENT;

  gAnimator->AddAnima(anima);
  Sleep(400);
 }

}

void I_cIntro::RunRotation(void)
{
 for (int c = 6; c > -1; c--)
 {
  ANIMA *anima = new ANIMA;

  ANIMA_ROTATION rot;
  rot.direction = ROTATION_RIGHT;

  anima->rot = rot;
  anima->pCube = cube_title[c];
  anima->type = ANIMA_TYPE_ROTATION;

  gAnimator->AddAnima(anima);
  Sleep(150);
 } 


}


void I_cIntro::key_test(void)
{
 static int c=0;
 static float pos = 13.0;

  ANIMA *anima = new ANIMA;

  ANIMA_MOVEMENT mov;
  mov.mov = MOVEMENT_RIGHT;
  mov.current_pos_ = cube_title[c]->GetPosx();
  mov.end_ = cube_title[c]->GetPosx() + pos;

  anima->mov = mov;
  anima->pCube = cube_title[c];
  anima->type = ANIMA_TYPE_MOVEMENT;

  gAnimator->AddAnima(anima);
  c++;
}