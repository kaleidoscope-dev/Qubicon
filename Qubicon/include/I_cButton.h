#pragma once
#include "gamedef.h"
#include "qubicon.h"


class I_cButton
{
 public:
        I_cButton();
       ~I_cButton();
       
        void Init(GLuint texture);
        //bool IsClicked(int px, int py);
        void OnClick(void);
        void Draw(int x, int y);
 private:
         GLuint texture_;       
};