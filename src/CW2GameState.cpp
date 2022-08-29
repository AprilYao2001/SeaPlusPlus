#include "header.h"
#include "CW2GameState.h"
#include <fstream>
#include <sstream>

#include "CW2Engine.h"
#include "CW2Creature.h"
#include "CW2TileManager.h"
#include "CW2AnimatedManager.h"

#include "CW2Magic.h"
#include "CW2Wand.h"
#include "DrawingSurface.h"



CW2GameState::CW2GameState(CW2Engine* pEngine, CW2StateManager* pStateManager)
	: m_pEngine(pEngine)
{
	m_pStateManager = pStateManager;
	m_pTile = std::make_shared<CW2TileManager>(TILE_HEIGHT, TILE_WIDTH, MAP_WIDTH, MAP_HEIGHT);
}

CW2GameState::~CW2GameState()
{
	ImageManager::destroyImageManager();
	m_pEngine->destroyOldObjects(true);
	std::cout << "CW2GameState destroied" << std::endl; 
}

void CW2GameState::initSelf()
{
	m_pEngine->CW2Engine::virtInitialise();
}



InitState::InitState(CW2Engine* m_pEngine, CW2StateManager* m_pStateManager)
	: CW2GameState(m_pEngine, m_pStateManager)
	/*,m_iSurfauceNum(0)
	, m_oTheExtraSurface1(m_pEngine)
	, m_oTheExtraSurface2(m_pEngine)
	, m_oTheExtraSurface3(m_pEngine)
	, m_oTheExtraSurface4(m_pEngine)
	, m_oTheExtraSurface5(m_pEngine)*/
{
	//image = ImageManager::loadImage("images\\jellyfish\\move.png");
	std::cout << "InitState created" << std::endl;
}

InitState::~InitState()
{
	//std::cout << "InitState destroied" << std::endl;
}

void InitState::virtSetupBackgroundBuffer()
{
	unsigned int uiWidthColor = 0x5499C7;
	int iHeightChange = SCREENHEIGHT / 5;

	for (int iY = 0; iY < SCREENHEIGHT; iY++) {
		for (int iX = 0; iX <SCREENWIDTH; iX++) {
			m_pEngine->setBackgroundPixel(iX, iY, uiWidthColor);
		}

		switch (iY / iHeightChange)
		{
		case 1: uiWidthColor = 0x2980B9; break;
		case 2: uiWidthColor = 0x2471A3; break;
		case 3: uiWidthColor = 0x1F618D; break;
		case 4: uiWidthColor = 0x1A5276; break;
		case 5: uiWidthColor = 0x154360; break;
		default:break;
		}
	}

	m_pEngine->drawBackgroundString(200, 320, "WELCOME TO SEA++, ENJOY YOUR GAME", CRString2, NULL);
	//m_pEngine->drawBackgroundString(80, 700, "CLECK MOUSE TO START THE GAME", CRString, NULL);
	m_pEngine->drawBackgroundString(80, 730, "PRESS H TO SEE THE HIGHSCORES", CRString, NULL);
	m_pEngine->drawBackgroundString(80, 760, "PRESS ESC TO EXIT THE GAME", CRString, NULL);


	/*m_iSurfauceNum = rand()%5;
	switch (m_iSurfauceNum)
	{
	case 5: 
	{
		m_pEngine->getBackgroundSurface() = &m_oTheExtraSurface5;
	}
		;
		break;
	case 4: m_pBackgroundSurface = &m_oTheExtraSurface1; break;
	case 3: m_pBackgroundSurface = &m_oTheExtraSurface2; break;
	case 2: m_pBackgroundSurface = &m_oTheExtraSurface3; break;
	case 1: m_pBackgroundSurface = &m_oTheExtraSurface3; break;
	default: m_pBackgroundSurface = &m_oTheExtraSurface3; break;
	}
	
	m_pAnim->drawThisFram(m_pEngine, m_pEngine->getBackgroundSurface(), 300, 400);*/
}

void InitState::virtMouseDown(int iButton, int iX, int iY)
{
	// click mouse to play the game
	m_pStateManager->switchToState(PLAY);
	m_pStateManager->initState();
}

void InitState::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode) {

	case SDLK_ESCAPE: // End program when escape is pressed
		
		m_pEngine->setExitWithCode(0);
		break;

	case SDLK_h:
		// switch state to the Menu
		m_pStateManager->switchToState(MENU);
		m_pStateManager->initState();
		break;

	case SDLK_l:		// load last save

		// switch state to the Play with load data
		m_pStateManager->switchToState(PLAY);
		dynamic_cast<PlayState*>(m_pStateManager->getStateByIndex(PLAY))->loadState();
		//m_pStateManager->initState();
		break;
	}
}

void InitState::virtDrawStringsOnTop()
{
	// check if now have last saved data, if have, draw the string
	std::ifstream infile("resources\\lastsave.csv");

	if (infile.good())
	{
		m_pEngine->drawForegroundString(80, 670, "PRESS L TO LOAD YOUR LAST SAVE", CRString, NULL);
		m_pEngine->drawForegroundString(80, 700, "CLECK MOUSE TO START NEW GAME", CRString, NULL);
	}
	else
		m_pEngine->drawForegroundString(80, 700, "CLECK MOUSE TO START THE GAME", CRString, NULL);

	infile.close();
}

void InitState::virtMainLoopDoBeforeUpdate()
{
	//m_iOffset = (m_iOffset+10) % SCREENWIDTH;
	//m_pEngine->lockBackgroundForDrawing();
	//virtSetupBackgroundBuffer(); // You could redraw background if you wanted each step, but it's faster to just shift it...
	//m_pEngine->unlockBackgroundForDrawing();
	//m_pEngine->redrawDisplay();
}

int InitState::virtInitialiseObjects()
{

	//m_pEngine->drawableObjectsChanged();
	//m_pEngine->destroyOldObjects(true);		// Destroy any existing objects

	//SimpleImage vAnim = ImageManager::loadImage("images\\Jellyfish_224x160px_7x5.png", true);
	//CW2AnimatedManager* test = new CW2AnimatedManager(SCREENWIDTH / 2, SCREENHEIGHT / 2, m_pEngine, 32, 32, vAnim, 5);

	//

	//m_pEngine->setAllObjectsVisible(true);
	return 0;
}

void InitState::copyAllBackgroundBuffer()
{
	m_pEngine->getForegroundSurface()->copyEntireSurface(m_pEngine->getBackgroundSurface());
}

void InitState::virtMainLoopDoAfterUpdate()
{
}




MenuState::~MenuState()
{
	std::cout << "MenuState destroied" << std::endl;
}

void MenuState::virtSetupBackgroundBuffer()
{
	m_pEngine->fillBackground(0x000000);
	m_pEngine->drawBackgroundString(SCREENWIDTH/2-150, 50, "HIGHSCORES", CRString, NULL);
	m_pEngine->drawBackgroundString(80, 730, "PRESS ANY KEY OR CLICK MOUSE TO GO BACK", CRString, NULL);
	m_pEngine->drawBackgroundString(80, 760, "PRESS ESC TO EXIT THE GAME", CRString, NULL);
}

void MenuState::virtMouseDown(int iButton, int iX, int iY)
{
	// click mouse to go back to init state
	m_pStateManager->switchToState(INITIAL);
	m_pStateManager->initState();
}

void MenuState::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode) {

	case SDLK_ESCAPE: // End program when escape is pressed
		
		m_pEngine->setExitWithCode(0);
		break;
	default:
		// switch state to the Init
		m_pStateManager->switchToState(INITIAL);
		m_pStateManager->initState();
		break;
	}
}

void MenuState::virtDrawStringsOnTop()			
{
	char buf[128];
	// open and draw highscore data from file
	std::ifstream file;
	file.open("resources\\highscores.csv");

	if (file.good())	// exist this file
	{
		int iLineNum = 0;		// only allow first 10 lines to draw

		std::string sLine, sVal;
		std::vector<std::string> vsData;

		while (std::getline(file, sLine) && iLineNum < 10) 
		{
			std::stringstream linestream(sLine);
			while (std::getline(linestream, sVal, ','))
			{
				vsData.push_back(sVal);		// get the data to draw
			}

			// draw data
			sprintf(buf, "%-2d PLACE: %-s - %-s", (iLineNum + 1), vsData.at(0).c_str(), vsData.at(1).c_str());
			m_pEngine->drawForegroundString(300, 90 + iLineNum * 30, buf, CRString, NULL);

			iLineNum++;
		}

		if (iLineNum == 0)			// exist file but no data inside
		{
			m_pEngine->drawForegroundString(300, SCREENHEIGHT / 2 - 80, "THERE ARE NO HIGHSCORES NEW", CRString2, NULL);
			m_pEngine->drawForegroundString(300, SCREENHEIGHT / 2 - 40, "PLAY GAME AND MAKE YOUR OWN HIGHSCORE!!", CRString2, NULL);
		}
	}
	else		// file not exist.
	{
		m_pEngine-> drawForegroundString(300, SCREENHEIGHT/2-80, "THERE ARE NO HIGHSCORES NEW", CRString2, NULL);
		m_pEngine->drawForegroundString(300, SCREENHEIGHT/2-40, "PLAY GAME AND MAKE YOUR OWN HIGHSCORE!!", CRString2, NULL);
	}

	file.close();
}

void MenuState::virtMainLoopDoBeforeUpdate()
{
}

void MenuState::copyAllBackgroundBuffer()
{
	m_pEngine->getForegroundSurface()->copyEntireSurface(m_pEngine->getBackgroundSurface());
}

void MenuState::virtMainLoopDoAfterUpdate()
{
}





PlayState::PlayState(CW2Engine* m_pEngine, CW2StateManager* m_pStateManager)
	: CW2GameState(m_pEngine, m_pStateManager)
{
	m_pPlayer = nullptr;
	std::cout << "PlayState created" << std::endl;
	m_iMonsterShouldCreateTime = 0;
}

PlayState::~PlayState()
{
	//m_pEngine->destroyOldObjects(true);		// Destroy any existing objects();
	ImageManager::destroyImageManager();
	/*delete m_pEngine;
	delete m_pStateManager;*/
	std::cout << "PlayState destroied" << std::endl;
}


void PlayState::virtSetupBackgroundBuffer()
{
	m_pEngine->fillBackground(CRMain);

	// use tileManager to draw the tilemap
	//m_pTile = std::make_unique<CW2TileManager>(new CW2TileManager(TILE_HEIGHT, TILE_WIDTH, MAP_WIDTH, MAP_HEIGHT));
	std::dynamic_pointer_cast<CW2TileManager>(m_pTile)->drawMap(m_pEngine, m_pEngine->getBackgroundSurface());

	m_pEngine->drawBackgroundString(SCREENWIDTH / 2 - 300, 15, "WELCOME TO SEA++, ENJOY YOUR GAME", CRString2, NULL);
	m_pEngine->drawBackgroundString(80, 760, "PRESS ESC TO EXIT THE GAME", CRString, NULL);
	m_pEngine->drawBackgroundString(80, 700, "PRESS S TO SAVE THE GAME AND RETURN TO STATR MENU", CRString, NULL);

	if (m_pEngine->isPaused())
		m_pEngine->drawBackgroundString(80, 730, "PRESS SPACE RETURN TO GAME", CRString, NULL);
	else
		m_pEngine->drawBackgroundString(80, 730, "PRESS SPACE TO PAUSE THE GAME", CRString, NULL);
}

void PlayState::virtMouseDown(int iButton, int iX, int iY)
{
	if (iButton == SDL_BUTTON_LEFT)
		m_pPlayer->useMagic();
}

void PlayState::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode) {

	case SDLK_o:// just for debug
		//m_pPlayer->deleteThisObject();
		m_pEngine->destroyOldObjects(true);
		m_pStateManager->switchToState(GAMEOVER);
		m_pStateManager->initState();
		break;

	case SDLK_h:// just for debug
		m_pEngine->destroyOldObjects(true);
		m_pStateManager->switchToState(HIGHSCORE);
		m_pStateManager->initState();
		break;

	case SDLK_s:		// save state in a file and swith to InitState
		saveState();
		m_pEngine->destroyOldObjects(true);
		m_pStateManager->switchToState(INITIAL);
		m_pStateManager->initState();
		break;

	case SDLK_SPACE:
		
		if (m_pEngine->isPaused())
		{
			setAllPause(false);
			m_pEngine->unpause();
		}
		else
		{
			setAllPause(true);
			m_pEngine->pause();		// pause the time
		}

		//m_enemySpawnNextEnemyTime -= getRawTime(); // we have paused it so subtract the current time from the time limit to get the difference then add the time onto that difference when unpaused
		break;
	}
}

void PlayState::virtDrawStringsOnTop()
{
	// draw play's current score on the top of the screen
	char buf[128];
	sprintf(buf, "SCORE:  %d", m_pPlayer->getScore());
	m_pEngine->drawForegroundString(START_DRAW_X + MAP_WIDTH - 200, 50, buf, CRString, NULL);

	if (m_pEngine->isPaused())
	{
		m_pEngine->drawForegroundRectangle(START_DRAW_X - 200, SCREENHEIGHT/2-50, START_DRAW_X + MAP_WIDTH + 200, SCREENHEIGHT / 2 + 50, 0x424949);
		m_pEngine->drawForegroundString(SCREENWIDTH/2-100, SCREENHEIGHT / 2-15, "GAME PAUSED", CRString, NULL);
	}
}

void PlayState::virtMainLoopDoBeforeUpdate()
{


	//m_pEngine->lockBackgroundForDrawing();
	//virtSetupBackgroundBuffer(); // You could redraw background if you wanted each step, but it's faster to just shift it...
	//m_pEngine->unlockBackgroundForDrawing();
	//m_pEngine->redrawDisplay();

	// CHECK IF IT'S TIME TO CREATE NEw MONSTER

	if (m_pEngine->getRawTime() > m_iMonsterShouldCreateTime && !(m_pEngine->isPaused()))
	{

		int iMonsterXCoord, iMonsterYCoord;
		while (1)
		{
			iMonsterXCoord = (rand() % (VALIDX_END / 2 - VALIDX_START + 1)) + VALIDX_START;
			iMonsterYCoord = (rand() % (VALIDY_END - 138 - VALIDY_START + 1)) + VALIDY_START;

			// check if the creat pos is valid on the tilemap, otherwise loop
			if (m_pTile->canStand(iMonsterXCoord, iMonsterYCoord))
				break;
		}


		m_pEngine->drawableObjectsChanged();
		//m_pEngine->destroyOldObjects(true);		// Destroy any existing objects

		int iType = rand() % 3;
		int iHealth = rand() % 150;
		int iSpeed = rand() % 25;
		int iValue = rand() % 20;
		switch (iType)
		{
		case 1:
			m_pEngine->appendObjectToArray(new AggressiveMonster(iMonsterXCoord, iMonsterYCoord, m_pEngine, iHealth, iHealth, m_pTile, iValue, iSpeed,1, 32,32));
			break;
		case 2:
			m_pEngine->appendObjectToArray(new NomalMonster(iMonsterXCoord, iMonsterYCoord, m_pEngine, iHealth, iHealth, m_pTile, iValue, iSpeed,3,32,32));
			break;
		case 3:
			m_pEngine->appendObjectToArray(new PeacefulMonster(iMonsterXCoord, iMonsterYCoord, m_pEngine, iHealth, iHealth, m_pTile, iValue, iSpeed,2,32,32));

			break;
		default:
			break;
		}

		int timeSpace = rand() % (MONSTER_CREATE_TIME_MAX + MONSTER_CREATE_TIME_MIN) + MONSTER_CREATE_TIME_MIN;
		m_iMonsterShouldCreateTime = m_pEngine->getRawTime() + timeSpace;
	}
}

int PlayState::virtInitialiseObjects()
{
	//random set the player's start coord on the tile map
	
	int iPlayerXCoord, iPlayerYCoord;
	while (1)
	{
		iPlayerXCoord = (rand() % (VALIDX_END / 2 - VALIDX_START + 1)) + VALIDX_START;
		iPlayerYCoord = (rand() % (VALIDY_END - 138 - VALIDY_START + 1)) + VALIDY_START;

		// check if the creat pos is valid on the tilemap, otherwise loop
		if (m_pTile->canStand(iPlayerXCoord + 39, iPlayerYCoord + 120))
			break;
	}
	

	m_pEngine->drawableObjectsChanged();
	m_pEngine->destroyOldObjects(true);		// Destroy any existing objects

	m_pPlayer = new Player(iPlayerXCoord, iPlayerYCoord, m_pEngine, 78, 138, (new CW2Wand(iPlayerXCoord - 7, iPlayerYCoord + 50, m_pEngine, 1)), 100, 100, m_pTile, 10, 0);

	m_pEngine->appendObjectToArray(m_pPlayer);

	m_pEngine->setAllObjectsVisible(true);
	return 0;
}

void PlayState::copyAllBackgroundBuffer()
{
	m_pEngine->getForegroundSurface()->copyEntireSurface(m_pEngine->getBackgroundSurface());
}

void PlayState::virtMainLoopDoAfterUpdate()
{
	if (m_pPlayer->isDied())
	{
		m_pStateManager->switchToState(GAMEOVER);
		m_pStateManager->initState();
	}
}

void PlayState::saveState()
{
	std::remove("resources\\lastsave.csv");		// delete the old one

	std::ofstream outfile("resources\\lastsave.csv");		// create and write in new one

	//saving enemy spawn time variables
	//outfile << "nextEnemySpawnTime," << m_enemySpawnNextEnemyTime << "\n"; // time until next enemy spawns - the current time
	//outfile << "enemySpawnDelay," << m_enemySpawnTimeBetweenSpawns << "\n";

	//save the tilestate
	outfile << "tileState," << m_pTile->getState() << "\n";

	//save all CW2OBject in file by get their state and store state string
	std::string sData;
	for (int i = 0; i < m_pEngine->getContentCount(); i++) 
	{
		std::vector<std::string> creatureState = dynamic_cast<CW2Object*>(m_pEngine->getContentItem(i))->getState();
		
		for (int j = 0; j < creatureState.size(); j++)
		{
			sData.append(creatureState.at(j));
			if (j != creatureState.size() - 1)		// add comma to each string data
				sData.push_back(',');
		}
		outfile << sData << "\n";			// reach the end of the state string, write as one line
	}

	outfile.close();
}

void PlayState::loadState()
{
	m_pEngine->destroyOldObjects(true);
	// load data from player's last save
	std::ifstream infile("resources\\lastsave.csv");

	CW2Wand* reloadedWand;
	Player* reloadedPlayer;
	CW2Magic* reloadedMagic;
	std::vector<std::string> vsPlayerData;		// tmp save recreated at end of the reading file

	
	if (infile.good()) 
	{
		
		int iLineNum = 0;

		std::string sLine, sVal;
		std::vector<std::string> vsData;

		std::cout << "last save file open" << std::endl;
		while (std::getline(infile, sLine)) 
		{
			std::stringstream inputstream(sLine);
			while (std::getline(inputstream, sVal, ','))
			{
				vsData.push_back(sVal);		// read all data from file

				//use the first string to know which object it is
				if (vsData.at(0) == "Magic")
				{
					//{ "Magic",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_iLevel), std::to_string(m_dAngle) };
					int iX = std::stoi(vsData.at(1));
					int iY = std::stoi(vsData.at(2));
					int iLevel = std::stoi(vsData.at(3));
					double dAngle = std::stoi(vsData.at(4));
					reloadedMagic = new CW2Magic(iX, iY, m_pEngine, iLevel, dAngle);
					m_pEngine->drawableObjectsChanged();
					m_pEngine->appendObjectToArray(&*reloadedMagic);
				}
				else if (vsData.at(0) == "Wand")
				{
					//{ "Wand",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_iLevel) };
					int iX = std::stoi(vsData.at(1));
					int iY = std::stoi(vsData.at(2));
					int iLevel = std::stoi(vsData.at(3));

					reloadedWand = new CW2Wand(iX, iY, m_pEngine, iLevel);
				}
				else if (vsData.at(0) == "tileState")
				{
					for (int i = 0; i < vsData.size(); i++) {
						std::cout << i << "  " << vsData.at(i) << std::endl;
					}
					//outfile << "tileState," << m_pTile->getState() << "\n";
					int iState = std::stoi(vsData.at(1));
					m_pTile->setState(iState);
				}
				else if (vsData.at(0) == "Player")
				{
					for (int i = 0; i < vsData.size(); i++)
					{
						vsPlayerData.push_back(vsData[i]);		// tmp save recreated at end of the reading file
						std::cout << vsData[i] << " ";
						std::cout << vsPlayerData[i] << " ";
					}

				}
				else if (vsData.at(0) == "Monster")
				{
					/*{ "Monster",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_iType)
		,std::to_string(m_iValue), std::to_string(m_iMaxHealth), std::to_string(m_iCurrentHealth),std::to_string(m_iSpeed), std::to_string(m_iHurt)
		,std::to_string(m_iDrawWidth), std::to_string(m_iDrawHeight)};*/
					int iX = std::stoi(vsData.at(1));
					int iY = std::stoi(vsData.at(2));
					int iType = std::stoi(vsData.at(3));

					int iValue = std::stoi(vsData.at(4));
					int iMaxHealth = std::stoi(vsData.at(5));
					int iCurrentHealth = std::stoi(vsData.at(6));
					int iSpeed = std::stoi(vsData.at(7));
					int iHurt = std::stoi(vsData.at(8));
					int iWidth = std::stoi(vsData.at(9));
					int iHeight = std::stoi(vsData.at(10));

					m_pEngine->drawableObjectsChanged();
					Monster* reloadedMonster = new Monster(iX, iY, m_pEngine, iMaxHealth, iCurrentHealth, m_pTile, iValue, iSpeed, iType, iWidth, iHeight);
					m_pEngine->appendObjectToArray(&*reloadedMonster);
				}
			}
		}

		// created player now
		if (vsPlayerData.at(0) == "Player")
		{
			/*{ "Player",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_iScore)
	,std::to_string(m_iKilled), std::to_string(m_iMaxHealth), std::to_string(m_iCurrentHealth),std::to_string(m_iSpeed)  };*/
			int iX = std::stoi(vsPlayerData.at(1));
			int iY = std::stoi(vsPlayerData.at(2));
			int iScore = std::stoi(vsPlayerData.at(3));

			int iKilled = std::stoi(vsPlayerData.at(4));
			int iMaxHealth = std::stoi(vsPlayerData.at(5));
			int iCurrentHealth = std::stoi(vsPlayerData.at(6));
			int iSpeed = std::stoi(vsPlayerData.at(7));

			reloadedPlayer = new Player(iX, iY, m_pEngine, 73, 138, reloadedWand, iMaxHealth, iCurrentHealth, m_pTile, iSpeed, iScore);
			m_pEngine->drawableObjectsChanged();
			m_pEngine->appendObjectToArray(&*reloadedPlayer);
		}

	}

	infile.close();
	m_pEngine->setAllObjectsVisible(true);

	//redraw background
	m_pEngine->lockAndSetupBackground();
}

void PlayState::setAllPause(bool bPause)
{
	for (int i = 0; i < m_pEngine->getContentCount(); i++)
		dynamic_cast<CW2Object*>(m_pEngine->getContentItem(i))->setPause(bPause);
}




void GameoverState::virtSetupBackgroundBuffer()
{
	std::cout << "GameoverState" << std::endl;
	m_pEngine->fillBackground(0x000000);
	//m_pEngine->drawBackgroundString(150, 0, "THIS IS GameoverState", CRString, NULL);
	//m_pEngine->drawBackgroundString(150, 40, "PRESS ESC TO EXIT THE GAME\nPress ANY key to start a new game\nPress RETURN to go back to initial", CRString, NULL);
}

void GameoverState::virtMouseDown(int iButton, int iX, int iY)
{
}

void GameoverState::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode) {

	case SDLK_ESCAPE: // End program when escape is pressed
		
		m_pEngine->setExitWithCode(0);
		break;

	case SDLK_RETURN:
		//check player's score if its meet heighscore
		std::ifstream infile("resources\\highscores.csv");

		if (infile.good()) 
		{
			int iLineNum = 0;		// only allow first 10 lines to draw

			std::string sLine, sVal;
			std::vector<std::string> vsData;

			while (std::getline(infile, sLine) && iLineNum < 10)		// file is open and already has 10 lines score
			{
				std::stringstream inputStream(sLine);
				while (std::getline(inputStream, sVal, ',')) {
					vsData.push_back(sVal);
				}

				//check if player's score is higher than this line's score
				if (dynamic_cast<PlayState*>(m_pStateManager->getStateByIndex(PLAY))->getPlayer().getScore() > std::stoi(vsData.at(1)))
				{
					m_iPlayerScorePlace = iLineNum;		// store the line number
					break;
				}
				iLineNum++;
			}

			// highscore file hasn't reach 10 line, can create new highscore record
			if (iLineNum < 10) 
			{
				m_pStateManager->switchToState(HIGHSCORE);
				m_pStateManager->initState();
			}

			//iLineNumber = 10, player's score isn't high enought
			else 
			{
				// switch state to the Init
				m_pEngine->destroyOldObjects(true);
				m_pStateManager->switchToState(INITIAL);
				m_pStateManager->initState();
			}
		}
		
		
		else		//the highscore file didnot exist, playe's score must be the 1st place
		{
			m_iPlayerScorePlace = 0;
			//m_pEngine->destroyOldObjects(true);
			m_pStateManager->switchToState(HIGHSCORE);
			m_pStateManager->initState();
		}


		infile.close();
		break;
	}
}

void GameoverState::virtDrawStringsOnTop()
{
	char buf[128];
	sprintf(buf, "YOUR SCORE IS: %d, WISH LUCK NEXT TIME", dynamic_cast<PlayState*>(m_pStateManager->getStateByIndex(PLAY))->getPlayer().getScore());

	m_pEngine->drawForegroundString(200, 320, buf, CRString2, NULL);
	//m_pEngine->drawForegroundString(80, 690, "PRESS ANY KEY TO START NEW GAME", CRString, NULL);
	m_pEngine->drawForegroundString(80, 730, "PRESS RETURN TO START SCREEN", CRString, NULL);
	m_pEngine->drawForegroundString(80, 760, "PRESS ESC TO EXIT THE GAME", CRString, NULL);
}

void GameoverState::virtMainLoopDoBeforeUpdate()
{
}

void GameoverState::copyAllBackgroundBuffer()
{
	m_pEngine->getForegroundSurface()->copyEntireSurface(m_pEngine->getBackgroundSurface());
}

void GameoverState::virtMainLoopDoAfterUpdate()
{
}




LoseState::LoseState(CW2Engine* m_pEngine, CW2StateManager* m_pStateManager)
	: CW2GameState(m_pEngine, m_pStateManager)
	,m_iOffset(0)
	,m_iScore(0)
{
}

LoseState::~LoseState()
{
}

void LoseState::virtSetupBackgroundBuffer()
{
	unsigned int uiWidthColor = 0x5499C7;
	int iHeightChange = SCREENHEIGHT / 5;

	for (int iY = 0; iY < SCREENHEIGHT; iY++) {
		for (int iX = 0; iX < SCREENWIDTH; iX++) {
			m_pEngine->setBackgroundPixel(iX, iY, uiWidthColor);
		}

		switch (iY / iHeightChange)
		{
		case 1: uiWidthColor = 0x2980B9; break;
		case 2: uiWidthColor = 0x2471A3; break;
		case 3: uiWidthColor = 0x1F618D; break;
		case 4: uiWidthColor = 0x1A5276; break;
		case 5: uiWidthColor = 0x154360; break;
		default:break;
		}
	}
	/*m_pEngine->fillBackground(0);
	for (int iX = 0; iX < SCREENWIDTH; iX++)
		for (int iY = 0; iY < SCREENHEIGHT; iY++)
			switch (rand() % 100)
			{
			case 0: m_pEngine->setBackgroundPixel(iX, iY, 0x2980B9); break;
			case 1: m_pEngine->setBackgroundPixel(iX, iY, 0x2471A3); break;
			case 2: m_pEngine->setBackgroundPixel(iX, iY, 0x0000FF); break;
			case 3: m_pEngine->setBackgroundPixel(iX, iY, 0x1F618D); break;
			case 4: m_pEngine->setBackgroundPixel(iX, iY, 0x1A5276); break;
			case 5: m_pEngine->setBackgroundPixel(iX, iY, 0x154360); break;
			}*/
}

void LoseState::virtMouseDown(int iButton, int iX, int iY)
{
}

void LoseState::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode) {

	case SDLK_ESCAPE: // End program when escape is pressed
		
		m_pEngine->setExitWithCode(0);
		break;

	case SDLK_RETURN:
		// switch state to the Init
		m_pStateManager->switchToState(INITIAL);
		m_pStateManager->initState();
		break;

	default:
		// switch state to the Play
		m_pStateManager->switchToState(PLAY);
		m_pStateManager->initState();
	}
}

void LoseState::virtDrawStringsOnTop()
{
	char buf[128];
	sprintf(buf, "YOUR SCORE IS: %d, WISH LUCK NEXT TIME", dynamic_cast<PlayState*>(m_pStateManager->getStateByIndex(PLAY))->getPlayer().getScore());
	
	m_pEngine->drawForegroundString(200, 320, buf, CRString2, NULL);
	m_pEngine->drawForegroundString(80, 690, "PRESS ANY KEY TO START NEW GAME", CRString, NULL);
	m_pEngine->drawForegroundString(80, 730, "PRESS RETURN TO RETURN TO START SCREEN", CRString, NULL);
	m_pEngine->drawForegroundString(80, 760, "PRESS ESC TO EXIT THE GAME", CRString, NULL);
}

void LoseState::virtMainLoopDoBeforeUpdate()
{
	m_iOffset = (m_iOffset + 5) % SCREENWIDTH;
	//m_pEngine->lockBackgroundForDrawing();
	//virtSetupBackgroundBuffer(); // You could redraw background if you wanted each step, but it's faster to just shift it...
	//m_pEngine->unlockBackgroundForDrawing();
	m_pEngine->redrawDisplay();
}

void LoseState::copyAllBackgroundBuffer()
{
	//m_pEngine->getForegroundSurface()->copyEntireSurface(m_pEngine->getBackgroundSurface());
	m_pEngine->getForegroundSurface()->copyRectangleFrom(m_pEngine->getBackgroundSurface(), 0, 0, SCREENWIDTH, SCREENHEIGHT, 0, m_iOffset);
	m_pEngine->getForegroundSurface()->copyRectangleFrom(m_pEngine->getBackgroundSurface(), 0, m_pEngine->getWindowWidth(), m_pEngine->getWindowHeight() - m_iOffset, m_pEngine->getWindowHeight(), 0, m_iOffset - m_pEngine->getWindowHeight());

}

int LoseState::virtInitialiseObjects()
{
	m_pEngine->drawableObjectsChanged();
	m_pEngine->destroyOldObjects(true);		// Destroy any existing objects

	return 0;
}

void LoseState::virtMainLoopDoAfterUpdate()
{
}




HighscoreState::~HighscoreState()
{
}

void HighscoreState::virtSetupBackgroundBuffer()
{
	std::cout << "HighscoreState" << std::endl;
	m_pEngine->fillBackground(0x000000);
	m_pEngine->drawBackgroundRectangle(SCREENWIDTH / 10, SCREENHEIGHT / 25, SCREENWIDTH - SCREENWIDTH / 10, SCREENHEIGHT - SCREENHEIGHT / 25, 0x2a2a2a);	//todo
	
}

void HighscoreState::virtMouseDown(int iButton, int iX, int iY)
{
}


void HighscoreState::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // End program when escape is pressed

		m_pEngine->setExitWithCode(0);
		break;

		// handle user input
	case SDLK_a:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'a';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_b:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'b';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_c:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'c';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_d:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'd';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_e:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'e';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_f:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'f';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_g:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'g';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_h:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'h';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_i:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'i';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_j:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'j';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_k:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'k';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_l:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'l';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_m:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'm';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_n:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'n';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_o:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'o';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_p:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'p';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_q:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'q';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_r:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'r';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_s:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 's';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_t:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 't';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_u:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'u';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_v:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'v';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_w:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'w';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_x:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'x';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_y:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'y';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_z:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += 'z';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

	case SDLK_SPACE:
		m_pEngine->lockForegroundForDrawing();
		m_sPlayerName += ' ';
		m_pEngine->unlockForegroundForDrawing();

		m_pEngine->redrawDisplay();
		break;

		// delete the last character
	case SDLK_BACKSPACE:

		if (m_sPlayerName.size() > 0) 	//check the name length
		{
			m_pEngine->lockForegroundForDrawing();
			m_sPlayerName.pop_back();
			m_pEngine->unlockForegroundForDrawing();

			m_pEngine->redrawDisplay();
		}
		break;

		// player confirmed input, save the player's name and score
	case SDLK_RETURN:

		if (m_sPlayerName.size() > 0) {		//player did put their name

			// write the player highscore to a file

			char buf[128];

			int iLineNum = 0;		// only allow first 10 lines to draw

			std::string sLine;
			std::vector<std::string> vsData;

			// check current highscores file
			std::ifstream infile("resources\\highscores.csv");

			if (infile.good())		// copy the data from old file
			{
				// get the lines before player's place
				while (iLineNum < m_iPlayerScorePlace && std::getline(infile, sLine)) 
				{
					vsData.push_back(sLine.c_str());
					iLineNum++;
				}

				// updata the line where now is play's place
				vsData.push_back(m_sPlayerName + "," + std::to_string(dynamic_cast<PlayState*>(m_pStateManager->getStateByIndex(PLAY))->getPlayer().getScore()));
				iLineNum++;

				// get the lines after player's place, only allowed 10 records
				while (iLineNum < 10 && std::getline(infile, sLine)) 
				{
					vsData.push_back(sLine);
					iLineNum++;
				}
			}
			else			//file not created yet, player's score is the 1st place
				vsData.push_back(m_sPlayerName + "," + std::to_string(dynamic_cast<PlayState*>(m_pStateManager->getStateByIndex(PLAY))->getPlayer().getScore()));

			infile.close();


			//writing data to file, if is's created, overwrite it, if its not create and write
			std::ofstream outfile("resources\\highscores.csv");
			for (int i = 0; i < vsData.size(); i++)
				outfile << vsData.at(i) << '\n';
			outfile.close();
		}

		std::cout << "data stored" << std::endl;
			

		m_sPlayerName = "";		// reset the player name and scores
		m_iPlayerScorePlace = 0;

		//m_pEngine->destroyOldObjects(true);
		m_pStateManager->switchToState(INITIAL);		// swith to initial
		m_pStateManager->initState();
		break;
	}
}

void HighscoreState::virtDrawStringsOnTop()
{
	char buf[128];
	sprintf(buf, "YOUR SCORE IS: %d, WELL DONE!", dynamic_cast<PlayState*>(m_pStateManager->getStateByIndex(PLAY))->getPlayer().getScore());
	sprintf(buf, "YOUR SCORE IS: 30, WELL DONE!");
	m_pEngine->drawForegroundString(200, 120, buf, CRString2, NULL);
	sprintf(buf, "YOUR NAME IS: %s", m_sPlayerName.c_str());
	m_pEngine->drawForegroundString(200, 170, buf, CRString2, NULL);
	m_pEngine->drawForegroundString(80, 220, "PLEASE ENTER YOUR NAME ONLY LETTERS AND SPACES ARE ALLOWED", CRString2, NULL);
	m_pEngine->drawForegroundString(80, 730, "PRESS RETURN TO CONFIRM", CRString, NULL);
	m_pEngine->drawForegroundString(80, 760, "PRESS ESC TO EXIT THE GAME", CRString, NULL);
}


void HighscoreState::virtMainLoopDoBeforeUpdate()
{
}

void HighscoreState::copyAllBackgroundBuffer()
{
	m_pEngine->getForegroundSurface()->copyEntireSurface(m_pEngine->getBackgroundSurface());
}

void HighscoreState::virtMainLoopDoAfterUpdate()
{
}




