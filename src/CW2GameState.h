#pragma once
#include <vector>


class CW2Engine;
class CW2StateManager;
class CW2TileManager;
class Player;
class Monster;
class MappableImageObject;
class ImagePixelMappingRotate;
class CW2ImagePixelMapping;
class CW2Wand;
class CW2AnimatedManager;
class DrawingSurface;


/*This is a class contain all of the game stages, where class CW2GameStage is an abstract class and all other stages are the subclass implement CW2GameStage*/

class CW2GameState
{
	// actually an abstract class with all function be set as virtual

public:
	CW2GameState(CW2Engine* pEngine, CW2StateManager* pStateManager);
	~CW2GameState();

	// initialize state itself
	void initSelf();
	
	
	// rewrited from CW2Engine functions
	virtual void virtSetupBackgroundBuffer() {}
	virtual void virtMouseDown(int iButton, int iX, int iY) {}
	virtual void virtKeyDown(int iKeyCode) {}
	virtual void virtDrawStringsOnTop() {}
	virtual  void virtMainLoopDoBeforeUpdate() {}
	virtual int virtInitialiseObjects() { return 0; }
	virtual void copyAllBackgroundBuffer() {}
	virtual void virtMainLoopDoAfterUpdate() {}

protected:
	int m_iStateNum = -1;		// state number represents which state it is
	CW2Engine* m_pEngine;
	CW2StateManager* m_pStateManager;
	std::shared_ptr <CW2TileManager> m_pTile;
	int m_iPlayerScorePlace = 0;		//player's score place in highscore rank
};


class InitState : public CW2GameState
{
public:
	InitState(CW2Engine* m_pEngine, CW2StateManager* m_pStateManager);
	~InitState();

	// rewrited from CW2Engine functions
	void virtSetupBackgroundBuffer()  override;
	void virtMouseDown(int iButton, int iX, int iY)  override;
	void virtKeyDown(int iKeyCode) override;
	void virtDrawStringsOnTop()  override;
	void virtMainLoopDoBeforeUpdate() override;
	int virtInitialiseObjects()override;
	void copyAllBackgroundBuffer() override;
	void virtMainLoopDoAfterUpdate() override;
private:
	/*SimpleImage image;
	DrawingSurface m_oTheExtraSurface1;
	DrawingSurface m_oTheExtraSurface2;
	DrawingSurface m_oTheExtraSurface3;
	DrawingSurface m_oTheExtraSurface4;
	DrawingSurface m_oTheExtraSurface5;
	int m_iSurfauceNum;*/
};


class MenuState : public CW2GameState
{
	
public:

	MenuState(CW2Engine* m_pEngine,  CW2StateManager* m_pStateManager) : CW2GameState(m_pEngine, m_pStateManager) { std::cout << "MenuState created" << std::endl; }
	~MenuState();

	// rewrited from CW2Engine functions
	void virtSetupBackgroundBuffer()  override;
	void virtMouseDown(int iButton, int iX, int iY)  override;
	void virtKeyDown(int iKeyCode) override;
	void virtDrawStringsOnTop()  override;
	void virtMainLoopDoBeforeUpdate() override;
	void copyAllBackgroundBuffer() override;
	void virtMainLoopDoAfterUpdate() override;
};


class PlayState : public CW2GameState
{
public:
	PlayState(CW2Engine* m_pEngine, CW2StateManager* m_pStateManager);
	~PlayState();

	// rewrited from CW2Engine functions
	void virtSetupBackgroundBuffer()  override;
	void virtMouseDown(int iButton, int iX, int iY)  override;
	void virtKeyDown(int iKeyCode) override;
	void virtDrawStringsOnTop()  override;
	void virtMainLoopDoBeforeUpdate() override;
	int virtInitialiseObjects() override;
	void copyAllBackgroundBuffer() override;
	void virtMainLoopDoAfterUpdate() override;

	Player& getPlayer() { return *m_pPlayer; }

	void saveState();
	void loadState();

	void setAllPause(bool bPause);

private:
	Player* m_pPlayer;
	int m_iMonsterShouldCreateTime;
	//CW2TileManager* m_pTile;
};


class GameoverState : public CW2GameState
{
public:
	GameoverState(CW2Engine* m_pEngine, CW2StateManager* m_pStateManager) : CW2GameState(m_pEngine, m_pStateManager) {}
	~GameoverState(){}

	void virtSetupBackgroundBuffer()  override;
	void virtMouseDown(int iButton, int iX, int iY)  override;
	void virtKeyDown(int iKeyCode) override;
	void virtDrawStringsOnTop()  override;
	void virtMainLoopDoBeforeUpdate() override;
	void copyAllBackgroundBuffer() override;
	void virtMainLoopDoAfterUpdate() override;
};


class LoseState : public CW2GameState
{
public:
	LoseState(CW2Engine* m_pEngine, CW2StateManager* m_pStateManager);
	~LoseState();

	void virtSetupBackgroundBuffer()  override;
	void virtMouseDown(int iButton, int iX, int iY)  override;
	void virtKeyDown(int iKeyCode) override;
	void virtDrawStringsOnTop()  override;
	void virtMainLoopDoBeforeUpdate() override;
	void copyAllBackgroundBuffer() override;
	int virtInitialiseObjects() override;
	void virtMainLoopDoAfterUpdate() override;
private:
	int m_iOffset;		// to change the background
	int m_iScore;		// the player's final score
};

class HighscoreState : public CW2GameState
{
public:
	HighscoreState(CW2Engine* m_pEngine, CW2StateManager* m_pStateManager) : CW2GameState(m_pEngine, m_pStateManager) 
	{
		m_sPlayerName = "";
	}
	~HighscoreState();

	void virtSetupBackgroundBuffer()  override;
	void virtMouseDown(int iButton, int iX, int iY)  override;
	void virtKeyDown(int iKeyCode) override;
	void virtDrawStringsOnTop()  override;
	void virtMainLoopDoBeforeUpdate() override;
	void copyAllBackgroundBuffer() override;
	void virtMainLoopDoAfterUpdate() override;

private:
	std::string m_sPlayerName;
};



