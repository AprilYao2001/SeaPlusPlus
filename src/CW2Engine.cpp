#include "header.h"
#include "CW2Engine.h"
#include "CW2Object.h"

CW2Engine::CW2Engine()
{
	m_oStateManager = std::make_unique<CW2StateManager>(this);
	m_oStateManager->switchToState(PLAY);
	std::cout << "engine created" << std::endl;
}

CW2Engine::~CW2Engine()
{
	m_oStateManager->~CW2StateManager();
	destroyOldObjects(true);		// Destroy any existing objects();
	std::cout << "engine destroied" << std::endl;
}


void CW2Engine::virtSetupBackgroundBuffer()
{
	m_oStateManager->virtSetupBackgroundBuffer();
}


int CW2Engine::virtInitialiseObjects()
{
	return m_oStateManager->virtInitialiseObjects();
}


void CW2Engine::virtMouseDown(int iButton, int iX, int iY)
{
	m_oStateManager->virtMouseDown(iButton, iX, iY);
}


void CW2Engine::virtKeyDown(int iKeyCode)
{
	m_oStateManager->virtKeyDown(iKeyCode);
}


void CW2Engine::virtDrawStringsOnTop()
{
	/*if (m_iExitWithCode == 0)
		return;*/
	m_oStateManager->virtDrawStringsOnTop();
}


int CW2Engine::virtInitialise()
{
	// Set up the background
	lockAndSetupBackground();

	// Create the moving objects
	virtInitialiseObjects();

	return 0; // success
}

void CW2Engine::virtMainLoopDoBeforeUpdate()
{
	/*if (m_iExitWithCode == 0)
		return;*/
	m_oStateManager->virtMainLoopDoBeforeUpdate();
}

void CW2Engine::virtMainLoopDoAfterUpdate()
{
	m_oStateManager->virtMainLoopDoAfterUpdate();
}

void CW2Engine::copyAllBackgroundBuffer()
{
	/*if (m_iExitWithCode == 0)
		return;*/
	m_oStateManager->copyAllBackgroundBuffer();
}

void CW2Engine::deleteThisObject(int iObjectID)
{
	std::cout << " deleteThisObject, ID: " << iObjectID << std::endl;
	int i = 0;
	for (auto it = m_vecDisplayableObjects.begin(); it != m_vecDisplayableObjects.end(); it++)
	{
		if (dynamic_cast<CW2Object*>(m_vecDisplayableObjects.at(i))->getObjectID() == iObjectID)	// Found the pointer
		{
			drawableObjectsChanged();
			delete (m_vecDisplayableObjects.at(i));
			m_vecDisplayableObjects.erase(m_vecDisplayableObjects.begin() + i);		 // Remove the object from current position
			break; // found then jump out loop
			std::cout << " deleteThisObject m_vecDisplayableObjects size" << m_vecDisplayableObjects.size() << std::endl;
			
		}
		i++;
	}
}

void CW2Engine::deleteAllObject()
{
	while (m_vecDisplayableObjects.size() != 0)
	{
		DisplayableObject* pOb = m_vecDisplayableObjects[0];
		drawableObjectsChanged();
		m_vecDisplayableObjects[0] = nullptr;
		delete pOb;
		m_vecDisplayableObjects.erase(m_vecDisplayableObjects.begin());
		std::cout << "m_vecDisplayableObjects size" << m_vecDisplayableObjects.size() << std::endl;
	}
	std::vector<DisplayableObject*>().swap(m_vecDisplayableObjects);
}




//void CW2Engine::virtBackgroundMouseDown(int iButton, int iRealX, int iRealY, int iVirtualX, int iVirtualY)
//{
//	m_oStateManager->virtBackgroundMouseDown(iButton, iRealX, iRealY, iVirtualX, iVirtualY);
//}

