#pragma once
#include "I_cCube.h"
#include "I_cAnimator.h"

class I_cIntro
{
 public:
        I_cIntro();
       ~I_cIntro();
       
        void Init(void);
        void SetTextureList(GLuint *tex);
        void Draw(void);
		int StartIntro(void);
		static int RunIntro(void *ptr);
		void RunMovement(void);
		void RunRotation(void);

		void key_test(void);
        
 private:
         I_cCube *cube_title[7];        
         //I_cCube *cube;
         GLuint *texture_list;
		 SDL_Thread *thread;
};
