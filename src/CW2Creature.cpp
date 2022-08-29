#include "header.h"
#include "CW2Creature.h"
#include "DisplayableObjectContainer.h"
#include "CW2AnimatedManager.h"
#include "CW2TileManager.h"
#include "CW2Wand.h"




Player::Player(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight, CW2Wand* pWand, int iMaxHealth, int iCurrentHealth, std::shared_ptr<CW2TileManager> pTile, int iSpeed, int iScore)
	:CW2Creature(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight, iMaxHealth, iCurrentHealth, pTile)
	, m_iScore(iScore)
	, m_pWand(pWand)
{
	m_iSpeed = iSpeed;
	m_pAnimIdle = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\Player\\idle.png", true), 3);
	m_pAnimLeft = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\Player\\left.png", true), 3);
	m_pAnimRight = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\Player\\right.png", true), 3);
	m_pAnimBack = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\Player\\back.png", true), 3);
	m_pAnim = m_pAnimIdle;
	std::cout << "player created, ID: " << m_iObjectID<<  std::endl;
}

Player::~Player()
{
	std::cout << "player destroied" << std::endl;
}

void Player::virtDraw()
{
	m_pEngine->lockForegroundForDrawing();
	if (!isVisible()||isPause())
		return;

	m_pAnim->drawThisFram(m_pEngine, m_pEngine->getForegroundSurface(), m_iCurrentScreenX, m_iCurrentScreenY);
	m_pWand->draw();
	drawHealthBar();
	m_pEngine->unlockForegroundForDrawing();
	redrawDisplay();
}


void Player::virtDoUpdate(int iCurrentTime)
{
	
	if (!isVisible()||isPause())
		return;

	if (isDied()) 
	{
		virtDie();
		return;
	}
	
	//player movement
	{
		m_pEngine->lockForegroundForDrawing();
		int targetX, targetY = 0;
		if (getEngine()->isKeyPressed(SDLK_UP) || getEngine()->isKeyPressed(SDLK_w))
		{
			if (m_pTile->canStand(getfeetX(), getfeetY()-m_iSpeed))		// check vaild
				m_iCurrentScreenY -= m_iSpeed;
			m_pAnim = m_pAnimBack;
			//m_pAnim->drawThisFram(m_pEngine, m_pEngine->getForegroundSurface(), m_iCurrentScreenX, m_iCurrentScreenY);
		}

		if (getEngine()->isKeyPressed(SDLK_DOWN) || getEngine()->isKeyPressed(SDLK_s))
		{
			if (m_pTile->canStand(getfeetX(), getfeetY() + m_iSpeed))
				m_iCurrentScreenY += m_iSpeed;
			m_pAnim = m_pAnimIdle;
			//m_pAnim->drawThisFram(m_pEngine, m_pEngine->getForegroundSurface(), m_iCurrentScreenX, m_iCurrentScreenY);
		}

		if (getEngine()->isKeyPressed(SDLK_LEFT) || getEngine()->isKeyPressed(SDLK_a))
		{
			if (m_pTile->canStand(getfeetX()-m_iSpeed, getfeetY()))
				m_iCurrentScreenX -= m_iSpeed;
			m_pAnim = m_pAnimLeft;
			//m_pAnimLeft->drawThisFram(m_pEngine, m_pEngine->getForegroundSurface(), m_iCurrentScreenX, m_iCurrentScreenY);
		}

		if (getEngine()->isKeyPressed(SDLK_RIGHT) || getEngine()->isKeyPressed(SDLK_d))
		{
			
			targetX = getDrawingRegionRight() + m_iSpeed;
			// check vaild
			if (m_pTile->canStand(getfeetX() + m_iSpeed, getfeetY()))
				m_iCurrentScreenX += m_iSpeed;
			m_pAnim = m_pAnimRight;
			//m_pAnimRight->drawThisFram(m_pEngine, m_pEngine->getForegroundSurface(), m_iCurrentScreenX, m_iCurrentScreenY);
		}

		m_pWand->setPosition(m_iCurrentScreenX-7, m_iCurrentScreenY+50);
		m_pEngine->unlockForegroundForDrawing();
		redrawDisplay();
	}

	
	
}

void Player::virtDie()
{
	setVisible(false);
	//m_pWand->deleteThisObject();
	m_pEngine->deleteThisObject(m_iObjectID);
}

void Player::useMagic()
{
	if (isVisible())
		m_pWand->useMagic();
}

std::vector<std::string> Player::getState()
{
	std::vector<std::string> currentState{ "Player",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_iScore)
	,std::to_string(m_iKilled), std::to_string(m_iMaxHealth), std::to_string(m_iCurrentHealth),std::to_string(m_iSpeed)  };
	return currentState;
}


Monster::Monster(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iMaxHealth, int iCurrentHealth, std::shared_ptr<CW2TileManager> pTile, int iValue, int iSpeed, int iType, int iWidth, int iHeight)
	:CW2Creature(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight, iMaxHealth, iCurrentHealth, pTile)
	, m_iType(iType)
	, m_iValue(iValue)
{
	// todo :load anime
	std::cout << "monster created" << std::endl;
}

Monster::~Monster()
{
	std::cout << "monster destroied" << std::endl;
}

void Monster::virtDraw()
{
	m_pEngine->lockForegroundForDrawing();
	if (!isVisible()||isPause())
		return;

	m_pAnim->drawThisFram(m_pEngine, m_pEngine->getForegroundSurface(), m_iCurrentScreenX, m_iCurrentScreenY);
	drawHealthBar();
	m_pEngine->unlockForegroundForDrawing();
	redrawDisplay();
}

void Monster::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible() || isPause())
		return;

	if (isDied()) {
		virtDie();
		return;
	}
	Move();
}

void Monster::virtDie()
{
	m_pAnim = m_pAnimDie;
	m_pEngine->getObjectByType<Player>()->updateScore(m_iValue);
	m_pEngine->deleteThisObject(m_iObjectID);		// delete this object from ObjectArray
}

void Monster::checkCollisions(CW2Creature* pTarget)
{
	if (CollisionDetection::checkRectangles(
		m_iCurrentScreenX, m_iCurrentScreenX + m_iDrawWidth,
		m_iCurrentScreenY, m_iCurrentScreenY + m_iDrawHeight,
		pTarget->getDrawingRegionLeft()- PLAYER_LEFT_EMPTY, pTarget->getDrawingRegionLeft() + pTarget->getDrawWidth()- PLAYER_RIGHT_EMPTY,
		pTarget->getDrawingRegionTop()- PLAYER_TOP_EMPTY, pTarget->getDrawingRegionTop() + pTarget->getDrawHeight()- PLAYER_BOTTOM_EMPTY))
	{
		m_pAnim = m_pAnimAttack;
		pTarget->beHurt(m_iHurt+rand()%21+(-10));		// hurt player by add a random number between -10 to 10
	}
}




AggressiveMonster::AggressiveMonster(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iMaxHealth, int iCurrentHealth, std::shared_ptr<CW2TileManager> pTile, int iValue, int iSpeed, int iType, int iWidth, int iHeight)
	:Monster(iStartXCoord, iStartYCoord, pEngine, iMaxHealth, iCurrentHealth, pTile, iValue, iSpeed, iType, iWidth, iHeight)
{
	m_pAnimIdle = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\crab\\idle.png", true), 4);
	m_pAnimMove = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\crab\\move.png", true), 4);
	m_pAnimAttack = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\crab\\attack.png", true), 4);
	m_pAnimDie = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\crab\\die.png", true), 4);
	m_pAnim = m_pAnimIdle;
	m_iHurt = 20;
	std::cout << "AggressiveMonster created" << std::endl;
}

AggressiveMonster::~AggressiveMonster()
{
	std::cout << "AggressiveMonster destroied" << std::endl;
}

void AggressiveMonster::Move()
{
	m_pAnim = m_pAnimMove;

	//find player
	Player* target = m_pEngine->getObjectByType<Player>();

	if (target)
	{
		std::cout << "player find" << std::endl;
		int i = rand() % (2*m_iSpeed+1) + (-m_iSpeed);		// random number between -m_iSpeed to m_iSpeed
		if (i % 2)
			setPosition(target->getDrawingRegionLeft() + i, target->getDrawingRegionTop() + i);
		else if (i > 0)
			setPosition(target->getDrawingRegionLeft() + i, m_iCurrentScreenY);
		else
			setPosition(m_iCurrentScreenX, target->getDrawingRegionTop() + i);

		checkCollisions(target);
	}
		
	
}

std::vector<std::string> AggressiveMonster::getState()
{
	std::vector<std::string> currentState{ "AggressiveMonster",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_iType)
,std::to_string(m_iValue), std::to_string(m_iMaxHealth), std::to_string(m_iCurrentHealth),std::to_string(m_iSpeed), std::to_string(m_iHurt)
,std::to_string(m_iDrawWidth), std::to_string(m_iDrawHeight) };
	return currentState;
}







PeacefulMonster::PeacefulMonster(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iMaxHealth, int iCurrentHealth, std::shared_ptr<CW2TileManager> pTile, int iValue, int iSpeed, int iType, int iWidth, int iHeight)
	:Monster(iStartXCoord, iStartYCoord, pEngine, iMaxHealth, iCurrentHealth, pTile, iValue, iSpeed, iType, iWidth, iHeight)
{
	iThisTimeHealth = iLastTimeHealth = iMaxHealth;
	m_pAnimIdle = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\octopus\\idle.png", true), 4);
	m_pAnimMove = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\octopus\\move.png", true), 4);
	m_pAnimAttack = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\octopus\\attack.png", true), 4);
	m_pAnimDie = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\octopus\\die.png", true), 6);
	m_pAnim = m_pAnimIdle;
	m_iHurt = 10;
	std::cout << "PeacefulMonster created" << std::endl;
}

PeacefulMonster::~PeacefulMonster()
{
	std::cout << "PeacefulMonster destroied" << std::endl;
}

void PeacefulMonster::Move()
{
	iThisTimeHealth = m_iCurrentHealth;		// store last tiem health

	m_pAnim = m_pAnimMove;

	int r = rand() % 4;		// random move
	switch (r)
	{
	case 1: m_iCurrentScreenX -= m_iSpeed; break;
	case 2: m_iCurrentScreenX += m_iSpeed; break;
	case 3: m_iCurrentScreenY -= m_iSpeed; break;
	case 4: m_iCurrentScreenY += m_iSpeed; break;
	}


	//find player
	Player* target = m_pEngine->getObjectByType<Player>();
	if (target)		// find the player
	{
		std::cout << "player find" << std::endl;
		// check play and monster's distance
		int iDistanceX = getXCentre() - target->getXCentre();
		int iDistanceY = getYCentre() - target->getYCentre();
		double distance = sqrt((pow(iDistanceX, 2)) + (pow(iDistanceY, 2)));

		if (distance > 300)		// if distance > 300, go to player's position
		{
			m_pAnim = m_pAnimMove;
			double time = distance / m_iSpeed;

			int newX = m_iCurrentScreenX + time * iDistanceX;
			int newY = m_iCurrentScreenY + time * iDistanceY;
			if (m_pTile->canStand(newX, newY))
				setPosition(newX, newY);
		}
		else if (abs(iDistanceX) < 250)		// only move X
		{
			if (iDistanceX > 0 && m_pTile->canStand(m_iCurrentScreenX - m_iSpeed, m_iCurrentScreenY))		//player is on the left
				m_iCurrentScreenX -= m_iSpeed;
			else if (iDistanceX < 0 && m_pTile->canStand(m_iCurrentScreenX + m_iSpeed, m_iCurrentScreenY))		// playr on the right
				m_iCurrentScreenX += m_iSpeed;
		}
		else if (abs(iDistanceY) < 250)		// only move Y
		{
			if (iDistanceY > 0 && m_pTile->canStand(m_iCurrentScreenX, m_iCurrentScreenY - m_iSpeed))		//player is on the up
				m_iCurrentScreenY -= m_iSpeed;
			else if (iDistanceY < 0 && m_pTile->canStand(m_iCurrentScreenX, m_iCurrentScreenY + m_iSpeed))		// playr on the down
				m_iCurrentScreenX += m_iSpeed;
		}


		if (iThisTimeHealth < iLastTimeHealth)			// monster be hurt
		{
			m_pAnim = m_pAnimMove;
			int i = rand() % 21 + (-10);		// random number between -10 to 10
			setPosition(target->getDrawingRegionLeft() + i, target->getDrawingRegionTop() + i);
		}
		checkCollisions(target);
	}

	else
	{
		m_pAnim = m_pAnimIdle;		// peaceful around player
	}


	

	iLastTimeHealth = iThisTimeHealth;		// store this time health
}

std::vector<std::string> PeacefulMonster::getState()
{
	std::vector<std::string> currentState{ "PeacefulMonster",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_iType)
,std::to_string(m_iValue), std::to_string(m_iMaxHealth), std::to_string(m_iCurrentHealth),std::to_string(m_iSpeed), std::to_string(m_iHurt)
,std::to_string(m_iDrawWidth), std::to_string(m_iDrawHeight) };
	return currentState;
}





NomalMonster::NomalMonster(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iMaxHealth, int iCurrentHealth, std::shared_ptr<CW2TileManager> pTile, int iValue, int iSpeed, int iType, int iWidth, int iHeight)
	:Monster(iStartXCoord, iStartYCoord, pEngine, iMaxHealth, iCurrentHealth, pTile, iValue, iSpeed, iType, iWidth, iHeight)
{
	m_pAnimIdle = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\jellyfish\\idle.png", true), 5);
	m_pAnimMove = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\jellyfish\\move.png", true), 5);
	m_pAnimAttack = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\jellyfish\\attack.png", true), 5);
	m_pAnimDie = std::make_shared<CW2AnimatedManager>(ImageManager::loadImage("images\\jellyfish\\die.png", true), 7);
	m_pAnim = m_pAnimIdle;
	m_iHurt = 15;
	std::cout << "NomalMonster created" << std::endl;
}

NomalMonster::~NomalMonster()
{
	std::cout << "NomalMonster destroied" << std::endl;
}

void NomalMonster::Move()
{
	m_pAnim = m_pAnimMove;
	std::cout << "NomalMonster Move" << std::endl;
	//moving around for 10 times
	for (int i = 0; i < 10; i++)
	{
		if (i % 2)
			m_iCurrentScreenX += 15;
		else
			m_iCurrentScreenX -= 15;
	}
	 
	//find player
	Player* target = m_pEngine->getObjectByType<Player>();
	if (target)
	{
		std::cout << "player find" << std::endl;

		if (getXCentre() < target->getXCentre())		// player on the right
			m_iCurrentScreenX += m_iSpeed;
		else if (getXCentre() > target->getXCentre())		// player on the left
			m_iCurrentScreenX -= m_iSpeed;

		if (getYCentre() < target->getYCentre())		// player on the down
			m_iCurrentScreenY += m_iSpeed;
		else if (getYCentre() > target->getYCentre())		// player on the up
			m_iCurrentScreenY -= m_iSpeed;
		checkCollisions(target);
	}
	std::cout << "NomalMonster no player" << std::endl;
}

std::vector<std::string> NomalMonster::getState()
{
	std::vector<std::string> currentState{ "NomalMonster",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_iType)
,std::to_string(m_iValue), std::to_string(m_iMaxHealth), std::to_string(m_iCurrentHealth),std::to_string(m_iSpeed), std::to_string(m_iHurt)
,std::to_string(m_iDrawWidth), std::to_string(m_iDrawHeight) };
	return currentState;
}
