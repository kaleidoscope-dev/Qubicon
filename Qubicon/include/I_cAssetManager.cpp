#include "I_cAssetManager.h"
#include "I_cGlobal.h"


I_cAssetManager *gAssetManager = 0;


I_cAssetManager::I_cAssetManager()
{

}


I_cAssetManager::~I_cAssetManager()
{
}




// TODO: dodati provjeru errora
int I_cAssetManager::LoadAssets(void)
{
 int err = 0;

 err = LoadCubeTextures();
 if (err < 0)
    {
     gData->AppendLog("MAIN: LoadAssets: Cube failed!");
     return -1;
    }     

 err = LoadMenuTextures();
 if (err < 0)
    {
     gData->AppendLog("MAIN: LoadAssets: Menu failed!");
     return -1;
    }     
    
 LoadLogoTextures();    

 return 0;
}



int I_cAssetManager::LoadCubeTextures(void)
{
 LoadGLTexturesPNG(&cubeAssets[TEX_FRONT],"data/cubetex/front.png");
 LoadGLTexturesPNG(&cubeAssets[TEX_BACK],"data/cubetex/back.png");
 LoadGLTexturesPNG(&cubeAssets[TEX_LEFT],"data/cubetex/left.png");
 LoadGLTexturesPNG(&cubeAssets[TEX_RIGHT],"data/cubetex/right.png");
 LoadGLTexturesPNG(&cubeAssets[TEX_UP],"data/cubetex/up.png");
 LoadGLTexturesPNG(&cubeAssets[TEX_DOWN],"data/cubetex/down.png");
     
 return 0; 
}



int I_cAssetManager::LoadMenuTextures(void)
{
 LoadGLTexturesPNG(&menuAssets[TEX_MAIN_TOP],"data/menu/title.png");
 LoadGLTexturesPNG(&menuAssets[TEX_MAIN_BOTTOM],"data/menu/bottom.png");
 LoadGLTexturesPNG(&menuAssets[TEX_START_OFF],"data/menu/00-start-h.png");
 LoadGLTexturesPNG(&menuAssets[TEX_START_ON],"data/menu/00-start.png");
 LoadGLTexturesPNG(&menuAssets[TEX_SETTINGS_OFF],"data/menu/00-settings-h.png");
 LoadGLTexturesPNG(&menuAssets[TEX_SETTINGS_ON],"data/menu/00-settings.png");
 LoadGLTexturesPNG(&menuAssets[TEX_QUIT_OFF],"data/menu/00-quit-h.png");
 LoadGLTexturesPNG(&menuAssets[TEX_QUIT_ON],"data/menu/00-quit.png"); 
 
 return 0;
}


int I_cAssetManager::LoadLogoTextures(void)
{
 LoadGLTexturesPNG(&logoAssets[TEX_C],"data/logotex/c_logo.png");
 LoadGLTexturesPNG(&logoAssets[TEX_U],"data/logotex/u_logo.png");
 LoadGLTexturesPNG(&logoAssets[TEX_B],"data/logotex/b_logo.png");
 LoadGLTexturesPNG(&logoAssets[TEX_I],"data/logotex/i_logo.png");
 LoadGLTexturesPNG(&logoAssets[TEX_O],"data/logotex/o_logo.png");
 LoadGLTexturesPNG(&logoAssets[TEX_N],"data/logotex/n_logo.png");
 LoadGLTexturesPNG(&logoAssets[TEX_W],"data/logotex/white.png");
 
 return 0;
}




GLuint I_cAssetManager::GetTextureAsset(GAMEAPI_TILE_ID asset)
{
 //GLuint asst =  assetList[asset];
 //return asst;
 return 0;
}



