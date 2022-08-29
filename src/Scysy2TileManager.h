#pragma once
#include "TileManager.h"
class Scysy2TileManager :
    public TileManager
{
public:
    Scysy2TileManager()
        : TileManager(25,25){}


	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
};

