#pragma once
#include "CW2Object.h"


class CW2AnimatedManager;
class CW2TileManager;
class CW2Wand;


/*This is the base class for all the spirtes*/

class CW2Creature 
	: public CW2Object
{
protected:
	// make the constructor protected, will not accidently creat a object of this class
	// it's actuactly an abstract class but make it more safe
	CW2Creature(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight, int iMaxHealth, int iCurrentHealth, std::shared_ptr<CW2TileManager> pTile)
		: CW2Object(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight)
		, m_iMaxHealth(iMaxHealth)
		, m_iCurrentHealth(iCurrentHealth)
		, m_pTile(pTile)
	{
		//m_pTile = std::make_shared<CW2TileManager>(pTile);
	}

	~CW2Creature() {}

public:
	
	// subclass can overwrite this to draw different
	virtual void virtDraw() override { drawHealthBar(); }

	// subclass must overwrite this
	virtual void virtDoUpdate(int iCurrentTime) override = 0;

	// subclass must overwrite this to show the died behaviour
	virtual void virtDie() = 0;

	//subclass must overwrite this
	virtual std::vector<std::string> getState() override = 0;


	void beHurt(int iDamage) { m_iCurrentHealth -= iDamage; std::cout << "hurt" << std::endl; }		// if creature be attacked, it will get hurt
	bool isDied()					{ return m_iCurrentHealth < 0; }		// if the creature is died
	void setSpeed(int iNewSpeed)	{ m_iSpeed = iNewSpeed; }
	int getSpeed()					{ return m_iSpeed; }
	

	void drawHealthBar()		// use a rectangle fill pixels to show the health bar
	{

		// using the max health of the creature to draw the health bar background
		getEngine()->drawForegroundRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY - m_iDrawHeight / 5,
			m_iCurrentScreenX + m_iDrawWidth,
			m_iCurrentScreenY - m_iDrawHeight / 10,
			0xB3B6B7);

		 double currentProportion = static_cast<double> (m_iCurrentHealth / m_iMaxHealth);		// how many pixels need to fill

		 if (currentProportion < 0)
			 currentProportion = 0;		// current health is 0, do not draw


		// using the current health of the creature to draw the health bar background, different types have differernt health colour
		switch (m_iSpeed)
		{
		case 0:				//tile creature, health colour green
			getEngine()->drawForegroundRectangle(
				m_iCurrentScreenX, m_iCurrentScreenY - m_iDrawHeight / 5,
				m_iCurrentScreenX + m_iDrawWidth * currentProportion,
				m_iCurrentScreenY - m_iDrawHeight / 10,
				0x28B463);
			break;
		default:			// moving creature, health colour red
			getEngine()->drawForegroundRectangle(
				m_iCurrentScreenX, m_iCurrentScreenY - m_iDrawHeight / 5,
				m_iCurrentScreenX + m_iDrawWidth * currentProportion,
				m_iCurrentScreenY - m_iDrawHeight / 10,
				0xCB4335);
			break;
		}
		

		char buf[128];
		sprintf(buf, "%i/%i", m_iCurrentHealth, m_iMaxHealth);				//show current health
		m_pEngine->drawForegroundString(m_iCurrentScreenX-1-0, m_iCurrentScreenY - m_iDrawHeight / 2, buf, CRString2);
	}

protected:
	
	int m_iMaxHealth;
	int m_iCurrentHealth;

	int m_iSpeed = 0;		// moving speed, default is 0

	std::shared_ptr<CW2TileManager>m_pTile;
};


class Player : public CW2Creature
{
public:
	Player(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight, CW2Wand* pWand, int iMaxHealth, int iCurrentHealth, std::shared_ptr<CW2TileManager> pTile, int iSpeed = 10, int iScore = 0);
	~Player();

	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;
	void virtDie() override;

	void useMagic();

	void updateScore(int iScore){ m_iScore += iScore; }
	int getScore() const		{ return m_iScore; }
	int getfeetX() const		{ return getXCentre(); }
	int getfeetY() const		{return getDrawingRegionBottom() - PLAYER_BOTTOM_EMPTY;}
	int getKilled() const		{ return m_iKilled; }
	std::vector<std::string> getState() override;


protected:

	CW2Wand* m_pWand;
	std::shared_ptr<CW2AnimatedManager>m_pAnim;
	std::shared_ptr<CW2AnimatedManager>m_pAnimIdle;
	std::shared_ptr<CW2AnimatedManager>m_pAnimLeft;
	std::shared_ptr<CW2AnimatedManager>m_pAnimRight;
	std::shared_ptr<CW2AnimatedManager>m_pAnimBack;
	int m_iScore;
	int m_iKilled;
};


class Monster : public CW2Creature {
public:
	Monster(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iMaxHealth, int iCurrentHealth, std::shared_ptr<CW2TileManager> pTile, int iValue, int iSpeed = 5, int iType = 0, int iWidth = 0, int iHeight = 0);
	~Monster();

	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;
	void virtDie();
	virtual void Move() {}	// subclass need overwrite ihis function
	void checkCollisions(CW2Creature* pTarget);
	virtual std::vector<std::string> getState() override { return std::vector<std::string>(); }		// subclass need overwrite ihis function

	int getType() { return m_iType; }

protected:
	int m_iType;		// what type of monster it is
	int m_iValue;		// how many scores the monster worth if monster died
	int m_iHurt;		// how much hurt the monster can cause

	std::shared_ptr<CW2AnimatedManager>m_pAnim;
	std::shared_ptr<CW2AnimatedManager>m_pAnimIdle;
	std::shared_ptr<CW2AnimatedManager>m_pAnimMove;
	std::shared_ptr<CW2AnimatedManager>m_pAnimAttack;
	std::shared_ptr<CW2AnimatedManager>m_pAnimDie;
};


class AggressiveMonster : public Monster {
public:
	AggressiveMonster(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iMaxHealth, int iCurrentHealth, std::shared_ptr<CW2TileManager> pTile, int iValue, int iSpeed = 15, int iType = 1, int iWidth = 0, int iHeight = 0);
	~AggressiveMonster();

	void Move() override;
	std::vector<std::string> getState() override;

private:
	
};


class PeacefulMonster : public Monster {
public:
	PeacefulMonster(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iMaxHealth, int iCurrentHealth, std::shared_ptr<CW2TileManager> pTile, int iValue, int iSpeed = 0, int iType = 2, int iWidth = 0, int iHeight = 0);
	~PeacefulMonster();

	void Move() override;
	std::vector<std::string> getState() override;
private:
	int iLastTimeHealth;
	int iThisTimeHealth;
};

class NomalMonster : public Monster {
public:
	NomalMonster(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iMaxHealth, int iCurrentHealth, std::shared_ptr<CW2TileManager> pTile, int iValue, int iSpeed = 15, int iType = 3, int iWidth = 0, int iHeight = 0);
	~NomalMonster();

	void Move() override;
	std::vector<std::string> getState() override;
};


