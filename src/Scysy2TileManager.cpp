#if 0

#include "header.h"
#include "Scysy2TileManager.h"


void Scysy2TileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY);		// set to result the rand()
	pSurface->drawTriangle(
		iStartPositionScreenX,	
		iStartPositionScreenY,	
		iStartPositionScreenX - getTileWidth()/2 - 1,		
		iStartPositionScreenY + getTileHeight() - 1,	
		iStartPositionScreenX + getTileWidth()/2 - 1,
		iStartPositionScreenY + getTileHeight() - 1,
		iMapValue);	// Pixel colour
}

#endif