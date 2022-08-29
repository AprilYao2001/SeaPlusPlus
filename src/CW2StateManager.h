#pragma once
#include "header.h"
#include <vector>


class CW2Engine;
class CW2GameState;
class InitState;
class MenuState;
class PlayState;
class WinState;
class LoseState;
class HighscoreState;


/*this class is used to manage different state, passing state between class and switch between them */
class CW2StateManager
{
public:

	CW2StateManager(CW2Engine* pEngine);


	~CW2StateManager();

	void virtSetupBackgroundBuffer();
	int virtInitialiseObjects();
	void virtMouseDown(int iButton, int iX, int iY);
	void virtKeyDown(int iKeyCode);
	void virtDrawStringsOnTop();


	void virtMainLoopDoBeforeUpdate();
	void copyAllBackgroundBuffer();
	void virtMainLoopDoAfterUpdate();


	
	
	// init the state according to state number
	void initState();

	// switch between different state
	void switchToState(int iStateNum);

	//// check the state is loaded or not
	//bool isLoaded(int iStateEnum);
	//
	//
	//// unload the state according to state number
	//void unloadState(int iStateEnum);
	//
	CW2GameState* getState() { return m_pCurrentState; }
	CW2GameState* getStateByIndex(int index) { return m_vStates[index]; }
	
private:

	CW2Engine* m_pEngine;

	//std::unique_ptr<CW2GameState> m_pCurrentState;
	CW2GameState* m_pCurrentState;
	std::vector<CW2GameState*> m_vStates;

};

