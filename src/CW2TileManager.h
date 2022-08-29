#pragma once
#include "TileManager.h"
#include "Config.h"
#include "CW2ImagePixelMapping.h"


class CW2TileManager :
    public TileManager
{
public:
	CW2TileManager(int iTileHeight, int iTileWidth, int iMapWidth, int iMapHeight);
	~CW2TileManager();

	void LoadData(std::string fileURL, std::vector<std::vector<int>> &vName);
	void drawLayer(BaseEngine* pEngine, DrawingSurface* pSurface, std::vector<std::vector<int>>& vName, int iLayer);

	void drawMap(BaseEngine* pEngine, DrawingSurface* pSurface);		// do same as drawAllTiles

	bool canStand(int x, int y);

	std::vector<std::vector<int>> getLayerValue(int state, int iLayer);

	int getState() const { return m_iState; }
	void setState(int istate) { m_iState = istate; }

private:

	std::unique_ptr<CW2ImagePixelMapping> m_pTileSets;
	CW2ImagePixelMapping m_oMapping;

	std::vector<std::vector<int>> m_iTileSetData;		// to read and store tilesets image's raw data form file
	std::vector<std::vector<int>> m_vMapLayer1;		// to read and store map's raw data form file
	std::vector<std::vector<int>> m_vMapLayer2Init;
	std::vector<std::vector<int>> m_vMapLayer2Bonus;
	int m_iState;

};

