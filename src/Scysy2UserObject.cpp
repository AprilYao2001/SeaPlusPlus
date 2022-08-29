#if 0

#include "header.h"
#include "Scysy2UserObject.h"
#include "BaseEngine.h"
#include "UtilCollisionDetection.h"
#include "Scysy2Object.h"


Scysy2UserObject::Scysy2UserObject(BaseEngine* pEngine, int iSize, int iLength, int iColour, double dXSpeed, double dYSpeed, double dXPos, double dYPos)
	: DisplayableObject(pEngine)
{
	m_pEngine = pEngine;
	m_dSX = dXSpeed;
	m_dSY = dYSpeed;
	m_dHX = dXPos;		// Starting position on the screen
	m_dHY = dYPos;
	m_iCount = 0;

	// Record the ball size as both height and width
	m_iDrawWidth = iSize;
	m_iDrawHeight = iSize;

	m_iLength = iLength;

	// set the color
	m_iColour = iColour;

	// make it visible
	setVisible(true);
}

Scysy2UserObject::~Scysy2UserObject(void) {}



void Scysy2UserObject::virtDraw()
{
	
	if (m_bLeft) 
	{
		m_dHUpX = m_dHX + m_iDrawWidth;
		m_dHUpY = m_dHY + m_iDrawHeight / 2;
		m_dHDownX = m_dHX + m_iDrawWidth;
		m_dHDownY = m_dHY - m_iDrawHeight / 2;

		getEngine()->drawForegroundTriangle(		// draw the head
			m_dHX, m_dHY,
			m_dHUpX, m_dHUpY,
			m_dHDownX, m_dHDownY,
			0xFFFFFF);

		for (int i = 0; i < m_iLength; i++)
		{
			getEngine()->drawForegroundOval(		// draw the body
				m_dHUpX + m_iDrawWidth * i, m_dHUpY,
				m_dHDownX + m_iDrawWidth * (i + 1) - 1,
				m_dHDownY,
				m_iColour + 20 * i);
		}
	}

	if (m_bRight)
	{
		m_dHUpX = m_dHX - m_iDrawWidth;
		m_dHUpY = m_dHY + m_iDrawHeight / 2;
		m_dHDownX = m_dHX - m_iDrawWidth;
		m_dHDownY = m_dHY - m_iDrawHeight / 2;

		getEngine()->drawForegroundTriangle(		// draw the head
			m_dHX, m_dHY,
			m_dHUpX, m_dHUpY,
			m_dHDownX, m_dHDownY,
			0xFFFFFF);

		for (int i = 0; i < m_iLength; i++)
		{
			getEngine()->drawForegroundOval(		// draw the body
				m_dHUpX - m_iDrawWidth * i, m_dHUpY,
				m_dHDownX - m_iDrawWidth * (i + 1) - 1,
				m_dHDownY,
				m_iColour + 20 * i);
		}
	}

	if (m_bUp)
	{
		m_dHUpX = m_dHX - m_iDrawWidth/2;
		m_dHUpY = m_dHY + m_iDrawHeight;
		m_dHDownX = m_dHX + m_iDrawWidth/2;
		m_dHDownY = m_dHY + m_iDrawHeight;

		getEngine()->drawForegroundTriangle(		// draw the head
			m_dHX, m_dHY,
			m_dHUpX, m_dHUpY,
			m_dHDownX, m_dHDownY,
			0xFFFFFF);

		for (int i = 0; i < m_iLength; i++)
		{
			getEngine()->drawForegroundOval(		// draw the body
				m_dHUpX, m_dHUpY + m_iDrawWidth * i,
				m_dHDownX,
				m_dHDownY + m_iDrawWidth * (i + 1) - 1,
				m_iColour + 20 * i);
		}
	}

	if (m_bDown)
	{
		m_dHUpX = m_dHX - m_iDrawWidth / 2;
		m_dHUpY = m_dHY - m_iDrawHeight;
		m_dHDownX = m_dHX + m_iDrawWidth / 2;
		m_dHDownY = m_dHY - m_iDrawHeight;

		getEngine()->drawForegroundTriangle(		// draw the head
			m_dHX, m_dHY,
			m_dHUpX, m_dHUpY,
			m_dHDownX, m_dHDownY,
			0xFFFFFF);

		for (int i = 0; i < m_iLength; i++)
		{
			getEngine()->drawForegroundOval(		// draw the body
				m_dHUpX, m_dHUpY - m_iDrawWidth * i,
				m_dHDownX,
				m_dHDownY - m_iDrawWidth * (i + 1) - 1,
				m_iColour + 20 * i);
		}
	}
	
	
}

double Scysy2UserObject::getLeftX() const
{
	if (m_bLeft)
	{
		return m_dHX;
	}
	if (m_bRight)
	{
		return m_dHUpX - m_iDrawWidth * m_iLength;
	}
	if (m_bUp || m_bDown)
	{
		return m_dHX + m_iDrawWidth / 2;
	}

}

double Scysy2UserObject::getRightX() const
{
	if (m_bRight)
	{
		return m_dHX;
	}
	if (m_bLeft)
	{
		return m_dHUpX + m_iDrawWidth * m_iLength;
	}
	if (m_bUp || m_bDown)
	{
		return m_dHX + m_iDrawWidth / 2;
	}

}

double Scysy2UserObject::getLeftY() const
{
	if (m_bLeft || m_bRight)
	{
		return m_dHY + m_iDrawHeight / 2;
	}
	if (m_bUp)
	{
		return m_dHY;
	}
	if (m_bDown)
	{
		return m_dHUpY - m_iDrawWidth * m_iLength;
	}

}

double Scysy2UserObject::getRightY() const
{
	if (m_bLeft|| m_bRight)
	{
		return m_dHY - m_iDrawHeight / 2;
	}
	if (m_bUp)
	{
		return  m_dHY + m_iDrawHeight + m_iDrawWidth * m_iLength;
	}
	if (m_bDown)
	{
		return m_dHDownY - m_iDrawWidth * m_iLength;
	}

}




void Scysy2UserObject::virtDoUpdate(int iCurrentTime)
{
	
	if (getEngine()->isKeyPressed(SDLK_a))		// change  the object move method
		m_bAuto = !m_bAuto;


	if (m_bAuto) {
		m_dHX += m_dSX;		// Alter position for speed
		m_dHY += m_dSY;
	}
	else {
		m_dHX = m_pEngine->getCurrentMouseX();		// Change object head direction according to mouse direction
		m_dHY = m_pEngine->getCurrentMouseY();
	}



	// Change object position if player presses a key
	if (getEngine()->isKeyPressed(SDLK_UP))
	{
		m_bUp = true;
		m_bDown = false;
		m_bLeft = false;
		m_bRight = false;
	}
	if (getEngine()->isKeyPressed(SDLK_DOWN))
	{
		m_bUp = false;
		m_bDown = true;
		m_bLeft = false;
		m_bRight = false;
	}
	if (getEngine()->isKeyPressed(SDLK_LEFT))
	{
		m_bUp = false;
		m_bDown = false;
		m_bLeft = true;
		m_bRight = false;
	}

	if (getEngine()->isKeyPressed(SDLK_RIGHT))
	{
		m_bUp = false;
		m_bDown = false;
		m_bLeft = false;
		m_bRight = true;
	}
		

	// Check for bounce off the edge
	if (m_bLeft) {
		if (m_dHX < 0)
		{
			m_dHX = -m_iStartDrawPosX;
			m_iCount++;
			if (m_dSX < 0)
				m_dSX = -m_dSX;
		}

		if ((m_dHDownX + m_iDrawWidth * m_iLength) >= getEngine()->getWindowWidth() - 1)
		{
			m_dHDownX = getEngine()->getWindowWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
			m_iCount++;
			if (m_dSX > 0)
				m_dSX = -m_dSX;
		}

		if (m_dHDownY < 0)
		{
			m_dHDownY = -m_iStartDrawPosY;
			m_iCount++;
			if (m_dSY < 0)
				m_dSY = -m_dSY;
		}

		if (m_dHUpY >= getEngine()->getWindowHeight() - 1)
		{
			m_dHUpY = getEngine()->getWindowHeight() - 1 - m_iStartDrawPosY - m_iDrawHeight;
			m_iCount++;
			if (m_dSY > 0)
				m_dSY = -m_dSY;
		}
	}

	if (m_bRight) {
		if ((m_dHDownX - m_iDrawWidth * m_iLength) < 0)
		{
			m_dHDownX = -m_iStartDrawPosX;
			m_iCount++;
			if (m_dSX < 0)
				m_dSX = -m_dSX;
		}

		if (m_dHX >= getEngine()->getWindowWidth() - 1)
		{
			m_dHX = getEngine()->getWindowWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
			m_iCount++;
			if (m_dSX > 0)
				m_dSX = -m_dSX;
		}

		if (m_dHDownY < 0)
		{
			m_dHDownY = -m_iStartDrawPosY;
			m_iCount++;
			if (m_dSY < 0)
				m_dSY = -m_dSY;
		}

		if (m_dHUpY >= getEngine()->getWindowHeight() - 1)
		{
			m_dHUpY = getEngine()->getWindowHeight() - 1 - m_iStartDrawPosY - m_iDrawHeight;
			m_iCount++;
			if (m_dSY > 0)
				m_dSY = -m_dSY;
		}
	}

	if (m_bUp) {
		if (m_dHUpX < 0)
		{
			m_dHUpX = -m_iStartDrawPosX;
			m_iCount++;
			if (m_dSX < 0)
				m_dSX = -m_dSX;
		}

		if (m_dHDownX >= getEngine()->getWindowWidth() - 1)
		{
			m_dHDownX = getEngine()->getWindowWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
			m_iCount++;
			if (m_dSX > 0)
				m_dSX = -m_dSX;
		}

		if (m_dHY < 0)
		{
			m_dHY = -m_iStartDrawPosY;
			m_iCount++;
			if (m_dSY < 0)
				m_dSY = -m_dSY;
		}

		if (m_dHDownY + m_iDrawWidth * m_iLength >= getEngine()->getWindowHeight() - 1)
		{
			m_dHUpY = getEngine()->getWindowHeight() - 1 - m_iStartDrawPosY - m_iDrawHeight;
			m_iCount++;
			if (m_dSY > 0)
				m_dSY = -m_dSY;
		}
	}

	if (m_bDown) {
		if (m_dHUpX < 0)
		{
			m_dHUpX = -m_iStartDrawPosX;
			m_iCount++;
			if (m_dSX < 0)
				m_dSX = -m_dSX;
		}

		if (m_dHDownX >= getEngine()->getWindowWidth() - 1)
		{
			m_dHDownX = getEngine()->getWindowWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
			m_iCount++;
			if (m_dSX > 0)
				m_dSX = -m_dSX;
		}

		if (m_dHDownY - m_iDrawWidth * m_iLength < 0)
		{
			m_dHDownY = -m_iStartDrawPosY;
			m_iCount++;
			if (m_dSY < 0)
				m_dSY = -m_dSY;
		}

		if (m_dHY >= getEngine()->getWindowHeight() - 1)
		{
			m_dHUpY = getEngine()->getWindowHeight() - 1 - m_iStartDrawPosY - m_iDrawHeight;
			m_iCount++;
			if (m_dSY > 0)
				m_dSY = -m_dSY;
		}
	}
	
	
	// collision detection
	// find the objects
	Scysy2Object* pObject;
	for (int iObjectId = 0;
		(pObject = dynamic_cast <Scysy2Object*>(m_pEngine-> getDisplayableObject(iObjectId))
			) != NULL;
		iObjectId++)
	{
		if (pObject == nullptr) // Object does not exist, skip it
			continue;		// If you need to cast to the sub-class type, you must use dynamic_cast, see lecture 19


		// This code checks for collision detection between rectangles
		if (CollisionDetection::checkRectangles(pObject-> getLeftX(), pObject->getRightX(),
			pObject->getLeftY(), pObject->getRightY(),
			getLeftX(), getRightX(),
			getLeftY(), getRightY()))
		{ // This code is executed if a collision detection was found
			m_iColour += 30;
			// Ensure that the object gets redrawn on the display, if something changed
			redrawDisplay();
			return;
		}
	}

	redrawDisplay();
}

int Scysy2UserObject::getCount() const
{
	return m_iColour;
}

#endif