#if 0

#include "header.h"
#include "Scysy2Object.h"
#include "BaseEngine.h"
#include "UtilCollisionDetection.h"


Scysy2Object::Scysy2Object(BaseEngine* pEngine, int iSizeR, int iColor, Scysy2TileManager* pTileManager, double dXSpeed, double dYSpeed, int dXPos, int dYPos)
	: DisplayableObject(pEngine)
{
	m_pEngine = pEngine;
	m_dSX = dXSpeed;
	m_dSY = dYSpeed;
	m_dX = dXPos;// Starting position on the screen
	m_dY = dYPos;
	m_iCount = 0;

	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	/*m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;*/

	// Record the ball size as both height and width
	m_iDrawWidth = iSizeR;
	m_iDrawHeight = iSizeR;

	// set the color
	m_iColour = iColor;
	m_pTileManager = pTileManager;

	// make it visible
	setVisible(true);
}





Scysy2Object::~Scysy2Object(void) {}


void Scysy2Object::virtDraw()
{
	if ((m_iCount % 10) < 5)
	{
		getEngine()->drawForegroundOval(		// draw the moving objects to the foreground
			m_dX, m_dY,
			m_dX + m_iDrawWidth - 1,
			m_dY + m_iDrawHeight - 1,
			m_iColour);
		m_bIsOval = true;
	}
	else {
		getEngine()->drawForegroundTriangle(		// draw the moving objects to the foreground
			m_dX, m_dY,
			m_dX + m_iDrawWidth/2-1,
			m_dY + m_iDrawHeight - 1,
			m_dX - m_iDrawWidth/2-1,
			m_dY + m_iDrawHeight - 1,
			m_iColour);
		m_bIsOval = false;
	}


}

double Scysy2Object::getLeftX() const
{
	if (m_bIsOval)
		return  m_dX;
	else
		return m_dX - m_iDrawWidth / 2;
}

double Scysy2Object::getLeftY() const
{
	if (m_bIsOval)
		return  m_dY;
	else
		return m_dY + m_iDrawHeight;
}

double Scysy2Object::getRightX() const
{
	if (m_bIsOval)
		return m_dX + m_iDrawWidth;
	else
		return m_dX + m_iDrawWidth / 2;
}

double Scysy2Object::getRightY() const
{
	/*if (m_bIsOval)
		return  m_dY + m_iDrawHeight;
	else*/
		return m_dY + m_iDrawHeight;
}

void Scysy2Object::virtDoUpdate(int iCurrentTime)
{
	
	// Alter position for speed
	m_dX += m_dSX;
	m_dY += m_dSY;
	
	
	// Check for bounce off the edge
	if (m_dX + m_iStartDrawPosX < 0)
	{
		m_dX = -m_iStartDrawPosX;
		m_iColour += 40;
		m_iCount++;
		if (m_dSX < 0)
			m_dSX = -m_dSX;
	}

	if (m_dX + m_iStartDrawPosX + m_iDrawWidth >= getEngine()->getWindowWidth() - 1)
	{
		m_dX = getEngine()->getWindowWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
		m_iColour += 40;
		m_iCount++;
		if (m_dSX > 0)
			m_dSX = -m_dSX;
	}
		
	if (m_dY + m_iStartDrawPosY < 0)
	{
		m_dY = -m_iStartDrawPosY;
		m_iColour += 40;
		m_iCount++;
		if (m_dSY < 0)
			m_dSY = -m_dSY;
	}
	
	if (m_dY + m_iStartDrawPosY + m_iDrawHeight >= getEngine()->getWindowHeight() - 1)
	{
		m_dY = getEngine()->getWindowHeight() - 1 - m_iStartDrawPosY - m_iDrawHeight;
		m_iColour += 40;
		m_iCount++;
		if (m_dSY > 0)
			m_dSY = -m_dSY;
	}

	if (m_pTileManager->isValidTilePosition(m_dX, m_dY))
	{
		//if (iCurrentTime > m_iLastUpdatedTime + 60)
		{ // Max undates once per 60ms - prevents a lot of updates at once, helping to reduce load
			int iTileX = m_pTileManager->getMapXForScreenX(m_dX);
			int iTileY = m_pTileManager->getMapYForScreenY(m_dY);
			int iCurrentTile = m_pTileManager->getMapValue(iTileX, iTileY);
			m_pTileManager->setAndRedrawMapValueAt(iTileX, iTileY, iCurrentTile + 10, getEngine(), getEngine()->getBackgroundSurface());
		}
	}

	redrawDisplay();
}


//void Scysy2Object2::virtDoUpdate(int iCurrentTime)
//{
//
//	// Work out current position
//	m_oMovement.calculate(iCurrentTime);
//	m_iCurrentScreenX = m_oMovement.getX();
//	m_iCurrentScreenY = m_oMovement.getY();
//
//	if (m_pTileManager->isValidTilePosition(m_iCurrentScreenX, m_iCurrentScreenY))
//	{
//		//if (iCurrentTime > m_iLastUpdatedTime + 60)
//		{ // Max undates once per 60ms - prevents a lot of updates at once, helping to reduce load
//			int iTileX = m_pTileManager->getMapXForScreenX(m_iCurrentScreenX);
//			int iTileY = m_pTileManager->getMapYForScreenY(m_iCurrentScreenY);
//			int iCurrentTile = m_pTileManager->getMapValue(iTileX, iTileY);
//			m_pTileManager->setAndRedrawMapValueAt(iTileX, iTileY, iCurrentTile + 1, getEngine(), getEngine()->getBackgroundSurface());
//		}
//	}
//
//	// Ensure that the object gets redrawn on the display, if something changed
//	redrawDisplay();
//}

#endif