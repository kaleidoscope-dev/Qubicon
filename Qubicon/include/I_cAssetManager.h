#pragma once
#include "I_cBitmap.h"
#include "gameapi.h"
#include "namedef.h"
#include <time.h>

/*
 globalni Asset Manager objekt. 
 ucitava sve texture s diska koristeci I_cBitmap::Load funkciju i prenoseci
 GLuint za tu texturu kao prametar.
*/

//TODO: load intro tex


class I_cAssetManager: public I_cBitmap
{
 public:
        I_cAssetManager();
       ~I_cAssetManager();
       
        int LoadAssets(void);
       
        int LoadCubeTextures(void);
        int LoadMenuTextures(void);
        int LoadLogoTextures(void);
        
        GLuint GetTextureAsset(GAMEAPI_TILE_ID asset);

        GLuint cubeAssets[6];
        GLuint menuAssets[8];
        GLuint logoAssets[7];
         
};



extern I_cAssetManager *gAssetManager;