#pragma once
#include "gamedef.h"
#include "qubicon.h"
#include "I_cButton.h"
#include "I_cHUDCube.h"

class I_cHUD
{
 public:
        I_cHUD();
       ~I_cHUD();

 public:
        void Init(GLuint *tex_list);  
        void Render(void);    
		void RenderHUDElement(void);
        void Enable();
        void Disable();
        bool IsActive();
        void OnClick(int px, int py);
        
        
        
 private: 
         void Enable2D(void);
         void Disable2D(void);
         void RenderMenu(void);
         void DrawTitle(void);
         void DrawButton(GLuint texture, int x, int y);
         void DrawBottom(void);
         void startPicking(int cursorX, int cursorY);
         
 private:
         bool menuActive_;
         GLuint *textureList;
         I_cButton *btn_start;
         I_cButton *btn_opt;
         I_cButton *btn_quit;
		 I_cHUDCube *hud_element;
                 
};