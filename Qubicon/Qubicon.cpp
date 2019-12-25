// Qubicon.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Qubicon.h"
#include "include\I_cGlobal.h"
#include "include\I_cEngine.h"
#include "include\I_cAssetManager.h"
#include "include\I_cSettings.h"
#include <SDL_image.h>
#include "conio.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR    lpCmdLine,int       nCmdShow)
{
	

 int err = 0;
 char path[256];
 
 GetCurrentDirectory(256,path);
 
 
 // ako je program pokrenut s '-d' parametrom otvori konzolu
 gData = new I_cGlobal();
 if (string(lpCmdLine) == "-d")
    {
      gData->SetDebugMode(FILE_MODE);
    }else {
           gData->SetDebugMode(CONSOLE_MODE);
          }
 gData->SetDebugFile("cubicon.txt");
 gData->ResetLog();
 gData->SetCurrentDir(path);
 srand(time(0));
 
 gSettings = new I_cSettings();
 gSettings->LoadSettings();
 float a = gSettings->GetDistance();
 printf("distance = %f\n",a);
  
  
 gAssetManager = new I_cAssetManager(); 
    
 I_cEngine *gameEngine = new I_cEngine();
 gameEngine->Start();
 
                
 
 bool done = false;

 while(gameEngine->IsRunning())
 {
 }// while done
 
 delete gameEngine;

 




 return 0;
}



