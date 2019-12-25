#pragma once
#include "gamedef.h"
#include "qubicon.h"

class I_cCube
{
 public:
        I_cCube();
       ~I_cCube();
       
 public:
		void SetPos(float x, float y, float z);     
        void SetPosx(float x);
		void SetRot(float x, float y, float z);  // rotiraj za angle stupnja po kojoj osi != 0
		void SetCubeGridPos(int x, int y);
		void GetCubeGridPos(int &x, int &y);  
		void Draw(GAMEAPI_DRAW_TYPE draw_type, int letter);      // TODO: redizajnirati ovo. parameter letter ne pripada ovdje, samo za sada
		float GetPosx(void);
		float GetPosy(void);
		int UpdateRotation(void);  // zove se iz animatora, ako postoji rotacija, updateaj kocku 
		                           // da reflektira trenutni kut
        bool RotationEnd();		                           
		                           
        void SetRotation(GAMEAPI_ROTATION rotation);
        void Rotate(float degree);
        void SetTextureList(GLuint *tex);
		                           
		
 //private:
         float posx_,posy_,posz_;	
         float rotx_,roty_,rotz_;
         float currRotx_,currRoty_,currRotz_;  // trenutna  rotacija (upravljano od animatora)
         float endRotx_,endRoty_,endRotz_;  // krajnja rotacija. kada dodje do ovdje brise se iz animatora
         int gridX_,gridY_; // pozicja u 2d polju
         
         
         GAMEAPI_ROTATION rotation_;
         float anglex_,angley_;
         float endAnglex_,endAngley_;
         GLuint *texture_list;
         

 //private:
         void DrawWire();
         void DrawPoly();     
         void DrawTex();    	
		 void DrawIntro(int letter);
 
};