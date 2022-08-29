#include "header.h"
#include "CW2GameState.h"
#include "CW2StateManager.h"

CW2StateManager::CW2StateManager(CW2Engine* pEngine)
{
	m_pEngine = pEngine;
	m_pCurrentState = nullptr;
	m_vStates.push_back(new InitState(m_pEngine, this));
	m_vStates.push_back(new MenuState (m_pEngine, this));
	m_vStates.push_back(new PlayState (m_pEngine, this));
	m_vStates.push_back(new GameoverState (m_pEngine, this));
	//m_vStates.push_back(new LoseState(m_pEngine, this));
	m_vStates.push_back(new HighscoreState(m_pEngine, this));

	std::cout << "CW2StateManager created" << std::endl;
}

CW2StateManager::~CW2StateManager()
{
	while (m_vStates.size() != 0) {

		CW2GameState* pOb = m_vStates[0];
		m_vStates[0] = nullptr;
		delete pOb;
		m_vStates.erase(m_vStates.begin());
		std::cout << "m_vStates size" << m_vStates.size() << std::endl;
	}
	std::vector<CW2GameState*>().swap(m_vStates);




	std::cout << "CW2StateManager destroied" << std::endl;
}

void CW2StateManager::virtSetupBackgroundBuffer()
{
	m_pCurrentState->virtSetupBackgroundBuffer();
}

int CW2StateManager::virtInitialiseObjects()
{
	return m_pCurrentState->virtInitialiseObjects();
}

void CW2StateManager::virtMouseDown(int iButton, int iX, int iY)
{
	m_pCurrentState->virtMouseDown(iButton, iX, iY);
}

void CW2StateManager::virtKeyDown(int iKeyCode)
{
	m_pCurrentState->virtKeyDown(iKeyCode);
}

void CW2StateManager::virtDrawStringsOnTop()
{
	m_pCurrentState->virtDrawStringsOnTop();
}


void CW2StateManager::virtMainLoopDoBeforeUpdate()
{
	m_pCurrentState->virtMainLoopDoBeforeUpdate();
}

void CW2StateManager::copyAllBackgroundBuffer()
{
	m_pCurrentState->copyAllBackgroundBuffer();
}

void CW2StateManager::virtMainLoopDoAfterUpdate()
{
	m_pCurrentState->virtMainLoopDoAfterUpdate();
}

void CW2StateManager::initState()
{
	m_pCurrentState->initSelf();
}

void CW2StateManager::switchToState(int iStateEnum)
{
	m_pCurrentState = m_vStates[iStateEnum];
}

//bool CW2StateManager::isLoaded(int iStateEnum)
//{
//	return m_vStates[iStateEnum] != nullptr;
//}
//
//void CW2StateManager::unloadState(int iStateEnum)
//{
//	if (isLoaded(iStateEnum))
//		m_vStates.erase(m_vStates.begin() + iStateEnum); // Remove and delete from current position
//	m_pCurrentState = m_vStates[iStateEnum+1];
//}
