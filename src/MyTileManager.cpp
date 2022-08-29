#include "header.h"
#include "MyTileManager.h"

//copy-pasted from superclass
void MyTileManager::virtDrawTileAt(
	BaseEngine* pEngine, // We don't need this but maybe a student will so it is here to use if needed
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY);		// set to result the rand()
	//unsigned int iColour = 0x101010 * ((iMapX + iMapY + iMapValue) % 16);
	// draw ovals isntend of squares, and changes the colors depending upon the map value of the tile
	unsigned int iColour = (unsigned int)((iMapValue & 0xf00) << 12) // red
		+ (unsigned int)((iMapValue & 0xf0) << 8) // green
		+ (unsigned int)((iMapValue & 0xf) << 4); // blue
	pSurface->drawOval(
		iStartPositionScreenX,	// Left
		iStartPositionScreenY,	// Top
		iStartPositionScreenX + getTileWidth() - 1,		// Right
		iStartPositionScreenY + getTileHeight() - 1,	// Bottom
		iColour);	// Pixel colour
}

