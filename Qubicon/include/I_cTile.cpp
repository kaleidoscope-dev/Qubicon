#include "I_cTile.h"
#include "I_cAssetManager.h"

I_cTile::I_cTile()
{
 useDefualtTex = false;
}


I_cTile::~I_cTile()
{
}





// sx,sy - Tile Size
// useDefaultTex - Da li se koristi defaultna textura

void I_cTile::Init(int sx, int sy, GLuint texture)
{
 sizex = sx;
 sizey = sy;
 tileTexture = texture;
}


// da li se nlazi koji item na ovom tileu?
void I_cTile::CreateTileItem(GLuint tex)
{
}

// unisti tile item ako se nalazi item na tileu
void I_cTile::DestroyTileItem(void)
{
}



// sprite moda explicitno postaviti koju texturu prikazujemo
void I_cTile::SetTexture(GLuint tex)
{
 tileTexture = tex;
}

void I_cTile::SetTileId(GAMEAPI_TILE_ID tileid)
{
 tileId1_ = tileid;
}



void I_cTile::Draw(int posx, int posy)
{
 
 tileRect.x = posx;
 tileRect.y = posy;
 tileRect.w = tileRect.x + sizex;
 tileRect.h = tileRect.y + sizey;


 glEnable(GL_TEXTURE_2D);
 
     glBindTexture( GL_TEXTURE_2D, tileTexture);

    glBegin( GL_QUADS );
	// gore ljevo 
	glTexCoord2i( 0, 0 );
	glVertex3i( tileRect.x,  tileRect.y, 0 );
 
	// gore desno
	glTexCoord2i( 1, 0 );
	glVertex3f( tileRect.w, tileRect.y, 0 );
 
	// dolje desno (corner)
	glTexCoord2i( 1, 1 );
	glVertex3f( tileRect.w, tileRect.h, 0 );
 
	// dolje ljevo
	glTexCoord2i( 0, 1 );
	glVertex3f(  tileRect.x,  tileRect.h, 0 );

glEnd();

glDisable(GL_TEXTURE_2D);




}

