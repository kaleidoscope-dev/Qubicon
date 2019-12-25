#include "I_cButton.h"
#include "I_cAssetManager.h"


I_cButton::I_cButton()
{
}


I_cButton::~I_cButton()
{
}


       
void I_cButton::Init(GLuint texture)
{
 texture_ = texture;
}
        
        
void I_cButton::Draw(int x, int y)
{
 glBindTexture(GL_TEXTURE_2D, gAssetManager->menuAssets[texture_]);
 glPushMatrix();
 glTranslatef((float)x,(float)y,0);
 glLoadName(12);

 glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0f, 0.0f);  glVertex2f(256, 0.0);
    glTexCoord2f(1.0f, 1.0f);  glVertex2f(256, 32.0);
    glTexCoord2f(0.0f, 1.0f);  glVertex2f(0.0, 32.0);    
 glEnd(); 
 glPopMatrix();
}



void I_cButton::OnClick(void)
{
 printf("click()\n");
}


