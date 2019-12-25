#include "I_cHUD.h"
#include "gameapi.h"
#include "I_cAssetManager.h"



 
#define BUFSIZE 512
GLuint selectBuf[BUFSIZE];

I_cHUD::I_cHUD()
{
 menuActive_ = false;
}

I_cHUD::~I_cHUD()
{
}




void I_cHUD::Init(GLuint *tex_list)
{
 textureList = tex_list;

 btn_start = new I_cButton();
 btn_opt = new I_cButton();
 btn_quit = new I_cButton(); 

 btn_start->Init(TEX_START_ON);
 btn_opt->Init(TEX_SETTINGS_ON);
 btn_quit->Init(TEX_QUIT_ON);

 hud_element = new I_cHUDCube();
 hud_element->SetPos(0,0,-15.0f);
 hud_element->SetTextureList(tex_list);

}


void I_cHUD::Render()
{
 if (menuActive_)
    {
     Enable2D();
     RenderMenu();
     Disable2D();
    }
 //RenderHUDElement();
}


void I_cHUD::RenderHUDElement(void)
{
 hud_element->Draw();
}


void I_cHUD::RenderMenu()
{
glEnable(GL_TEXTURE_2D);



 DrawTitle();
 btn_start->Draw(270,180);
 btn_opt->Draw(270,230);
 btn_quit->Draw(270,278);  
 DrawBottom();


glDisable(GL_TEXTURE_2D);
}



void I_cHUD::DrawButton(GLuint texture, int x, int y)
{
 glBindTexture(GL_TEXTURE_2D, gAssetManager->menuAssets[texture]);
 glPushMatrix();
 glTranslatef((float)x,(float)y,0);
 glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0f, 0.0f);  glVertex2f(256, 0.0);
    glTexCoord2f(1.0f, 1.0f);  glVertex2f(256, 32.0);
    glTexCoord2f(0.0f, 1.0f);  glVertex2f(0.0, 32.0);    
 glEnd(); 
 glPopMatrix();
}



void I_cHUD::DrawTitle(void)
{
 glBindTexture(GL_TEXTURE_2D, gAssetManager->menuAssets[TEX_MAIN_TOP]);
 glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0f, 0.0f);  glVertex2f(GAMEAPI_WINDOW_W, 0.0);
    glTexCoord2f(1.0f, 1.0f);  glVertex2f(GAMEAPI_WINDOW_W, 128);
    glTexCoord2f(0.0f, 1.0f);  glVertex2f(0.0, 128);
 glEnd();
}



void I_cHUD::DrawBottom(void)
{
 glBindTexture(GL_TEXTURE_2D, gAssetManager->menuAssets[TEX_MAIN_BOTTOM]);
 glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex2f(0.0, GAMEAPI_WINDOW_H-128);
    glTexCoord2f(1.0f, 0.0f);  glVertex2f(GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H-128);
    glTexCoord2f(1.0f, 1.0f);  glVertex2f(GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H);
    glTexCoord2f(0.0f, 1.0f);  glVertex2f(0.0, GAMEAPI_WINDOW_H);
 glEnd();
}


void I_cHUD::Enable2D(void)
{
 glMatrixMode(GL_PROJECTION);
 glPushMatrix();
 glLoadIdentity();
 glOrtho(0.0, GAMEAPI_WINDOW_W, GAMEAPI_WINDOW_H, 0.0, -1.0, 10.0);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 //glDisable(GL_CULL_FACE);
 glClear(GL_DEPTH_BUFFER_BIT);    
}



void I_cHUD::Disable2D(void)
{
 glMatrixMode(GL_PROJECTION);
 glPopMatrix();
 glMatrixMode(GL_MODELVIEW);
}



void I_cHUD::Enable()
{
 menuActive_ = true;
}

void I_cHUD::Disable()
{
 menuActive_ = false;
}



bool I_cHUD::IsActive()
{
 return menuActive_;
}


void I_cHUD::OnClick(int px, int py)
{
 printf("hud\n");
 //btn_start->Draw(120,180);
 //btn_opt->Draw(120,230);
 //btn_quit->Draw(120,278);   
}








 
void I_cHUD::startPicking(int cursorX, int cursorY)
{

	GLuint buff[64] = {0};
 	GLint hits, view[4];
 	int id;
 
 	/*
 		This choose the buffer where store the values for the selection data
 	*/
 	glSelectBuffer(64, buff);
 
 	/*
 		This retrieves info about the viewport
 	*/
 	glGetIntegerv(GL_VIEWPORT, view);
 
 	/*
 		Switching in selecton mode
 	*/
 	glRenderMode(GL_SELECT);
 
 	/*
 		Clearing the names' stack
 		This stack contains all the info about the objects
 	*/
 	glInitNames();
 
 	/*
 		Now fill the stack with one element (or glLoadName will generate an error)
 	*/
 	glPushName(0);
 
 	/*
 		Now modify the viewing volume, restricting selection area around the cursor
 	*/
 	glMatrixMode(GL_PROJECTION);
 	glPushMatrix();
 		glLoadIdentity();
 
 		/*
 			restrict the draw to an area around the cursor
 		*/
 		gluPickMatrix(cursorX, cursorY, 1.0, 1.0, view);
 		gluPerspective(60, (float)view[2]/(float)view[3], 0.0001, 1000.0);
 
 		/*
 			Draw the objects onto the screen
 		*/
 		glMatrixMode(GL_MODELVIEW);
 
 		/*
 			draw only the names in the stack, and fill the array
 		*/
 		RenderMenu();
 
 		/*
 			Do you remeber? We do pushMatrix in PROJECTION mode
 		*/
 		glMatrixMode(GL_PROJECTION);
 	glPopMatrix();
 
 	/*
 		get number of objects drawed in that area
 		and return to render mode
 	*/
 	hits = glRenderMode(GL_RENDER);
 
 	/*
 		Print a list of the objects
 	*/
 	//list_hits(hits, buff);
 
 	/*
 		uncomment this to show the whole buffer
 	* /
 	gl_selall(hits, buff);
 	*/
 
 	glMatrixMode(GL_MODELVIEW);
}









