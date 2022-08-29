#include "header.h"
#include "CW2TileManager.h"
#include "Config.h"
#include <fstream>
#include <sstream>


/*This tile manager base on three csv files to render tilemap,
* form the the tileset image generate a tileset csv file record each tile's id in the tielset image,
* form map created by 'Tiled', generate two map layer csv file record which tile is used to draw the map,
* load the data in 2d vector and use the location on tileset image to render tilemap.
*/

CW2TileManager::CW2TileManager(int iTileHeight, int iTileWidth, int iMapWidth, int iMapHeight)
	:TileManager(iTileHeight, iTileWidth, iMapWidth, iMapHeight)
{
	SimpleImage tmp = ImageManager::loadImage("images\\tilesets_32x32_ withTileGrid(forRefe).png", true);
	//SimpleImage tmp = ImageManager::loadImage("images\\tilesets_32x32px.png", true);
	m_pTileSets =std::make_unique<CW2ImagePixelMapping>(tmp.getRawImageData());
	//m_pTileSets = ImageManager::loadImage("images\\tilesets_32x32px.png", true); 

	m_iState = 0;
	LoadData("resources\\tilesets_32x32px.csv", m_iTileSetData);
	LoadData("resources\\map_layer1.csv", m_vMapLayer1);
	LoadData("resources\\map_layer2_init.csv", m_vMapLayer2Init);
	LoadData("resources\\map_layer2_bonus.csv", m_vMapLayer2Bonus);

	//std::cout << "load succ" << std::endl;

	setTopLeftPositionOnScreen(START_DRAW_X, START_DRAW_Y);

	std::cout << "CW2TileManager created" << std::endl;
}

CW2TileManager::~CW2TileManager()
{
	ImageManager::destroyImageManager();
	std::vector<std::vector<int>>().swap(m_iTileSetData);
	std::vector<std::vector<int>>().swap(m_vMapLayer1);
	std::vector<std::vector<int>>().swap(m_vMapLayer2Init);
	std::vector<std::vector<int>>().swap(m_vMapLayer2Bonus);
	std::cout << "CW2TileManager destroied" << std::endl;
}

void CW2TileManager::drawMap(BaseEngine* pEngine, DrawingSurface* pSurface)		//state value 0 for initTilemap, state value1 for bonusTilemap
{
	// first render first layer
	drawLayer(pEngine, pSurface, m_vMapLayer1, 1);

	// then render second layer according to state
	//update tilemap if player killed 10 monster and get score over 150
	if(m_iState == 0)
		drawLayer(pEngine, pSurface, m_vMapLayer2Init, 2);
	if(m_iState == 1)
		drawLayer(pEngine, pSurface, m_vMapLayer2Bonus, 2);
}

bool CW2TileManager::canStand(int x, int y)		// check if this tile is roadblock, the x,y is the feet of the creature
{
	//it is not roadblock if layer2 tile value (!=96/98/352/353/376/377) && layer1 tile value (!=216/217/218/240/242/264/265/266/97/120/122/144/145/146/168/169/170/192/193/194)

	int notAllowLayer1[] = { 216 , 217 , 218 , 240 , 242 , 264 , 265 , 266 , 97 , 120 , 122 , 144 , 145 , 146 , 168 , 169 , 170 , 192 , 193 , 194 };
	int notAllowLayer2[] = { 96  ,  98 , 352 , 353 , 376, 377 };

	// m_iTileSetData[0][4] = 96 == m_vMapLayer2Init[19][6] == (START_DRAW_X + TILE_WIDTH * 6, START_DRAW_Y + TILE_HEIGHT * 19) == (x,y)
	int mapX = (x - START_DRAW_X) / TILE_WIDTH;			//get map index
	int mapY = (y - START_DRAW_Y) / TILE_HEIGHT;
	int iValue = m_vMapLayer1[mapY][mapX];			// get map value

	bool layer1Result = true;
	bool layer2Result = false;

	// check layer 1
	for (int i = 0; i < sizeof(notAllowLayer1) / sizeof(int); i++)
	{
		if (iValue == notAllowLayer1[i])
			return  false;
	}

	iValue = m_vMapLayer2Init[mapY][mapX];
	// check layer 2
	for (int j = 0; j < sizeof(notAllowLayer2) / sizeof(int); j++)
	{
		if (iValue == notAllowLayer2[j])
			return false;
	}

	return true;
}

std::vector<std::vector<int>> CW2TileManager::getLayerValue(int istate, int iLayer)
{
	if (iLayer == 1)
		return m_vMapLayer1;
	else if (iLayer == 2)
	{
		if(istate==0)
			return m_vMapLayer2Init;
		else if (istate == 1)
			return m_vMapLayer2Bonus;
	}
		
	else
	return std::vector<std::vector<int>>();
}


void CW2TileManager::LoadData(std::string fileURL, std::vector<std::vector<int>>& vName)
{
	std::ifstream file;
	file.open(fileURL);

	if (!file.good()) 
	{
		std::cout << fileURL << " file wrong!" << std::endl;
		return;
	}

	std::string line, val;
	std::vector<int> tmp;
	while (std::getline(file, line))
	{
		std::stringstream linestream(line);
		while (std::getline(linestream, val, ','))
		{
			tmp.push_back(stoi(val));
		}
		vName.push_back(tmp);
		tmp.clear();
	}

	file.close();
}

void CW2TileManager::drawLayer(BaseEngine* pEngine, DrawingSurface* pSurface, std::vector<std::vector<int>>& vName, int iLayer)
{
	
	int iCurrentTileValue;
	for (int mapY = 0; mapY < vName.size(); mapY++)
	{
		for (int mapX = 0; mapX < vName[mapY].size(); mapX++)
		{
			iCurrentTileValue = vName[mapY][mapX];		// find which tile needs to draw

			for (int tileSet = 0; tileSet < m_iTileSetData.size(); tileSet++)
			{
				auto it = std::find(m_iTileSetData[tileSet].begin(), m_iTileSetData[tileSet].end(), iCurrentTileValue);			// find where this tile in tileset
				if (it != m_iTileSetData[tileSet].end())
				{
					m_oMapping.setXShift(TILE_WIDTH * std::distance(m_iTileSetData[tileSet].begin(), it));			// set the offset value according to the current tile location
					m_oMapping.setYShift(TILE_HEIGHT * tileSet);

					if (iLayer == 1)
					{
						pSurface->mySDLLockSurface();
						m_pTileSets->renderImageApplyingMapping(pEngine, pSurface,		// render layer1, without mask
							START_DRAW_X + TILE_WIDTH * mapX, START_DRAW_Y + TILE_HEIGHT * mapY, TILE_WIDTH, TILE_HEIGHT, &m_oMapping);
						pSurface->mySDLUnlockSurface();
						pEngine->redrawDisplay();
					}
					else
					{
						pSurface->mySDLLockSurface();
						m_pTileSets->renderImageApplyingMappingAndMask(pEngine, pSurface,		// render other layer with mask
							START_DRAW_X + TILE_WIDTH * mapX, START_DRAW_Y + TILE_HEIGHT * mapY, TILE_WIDTH, TILE_HEIGHT, 0x000000, &m_oMapping);
						pSurface->mySDLUnlockSurface();
						pEngine->redrawDisplay();
					}
						
				}
			}
		}
	}
}
