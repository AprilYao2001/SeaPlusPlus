#pragma once
#include"header.h"
#include "CW2Object.h"
#include "UtilCollisionDetection.h"
#include "CW2Creature.h"
#include<vector>


/*This is the base class for spirte's magic power, each spirte have magic power to interact with different tile*/
class CW2Magic : 
	public CW2Object
{

public:
	CW2Magic(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iLevel, double dAngle, int iWidth = 0, int iHeight = 0)
		: CW2Object(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight)
		, m_iLevel(iLevel)
		, m_dAngle(dAngle)
	{
		if (m_iLevel == 1)		// basic magic
		{
			m_iPower = 20;
			m_dSpeed = 20;
			m_dRange = 300;
			m_oImage = ImageManager::loadImage("images\\magic_31x31px_1.png");
		}
		else		// power magic
		{
			m_iPower = 30;
			m_dSpeed = 25;
			m_dRange = 400;
			m_oImage = ImageManager::loadImage("images\\magic_31x31px_2.png");
		}

		setSize(m_oImage.getWidth(), m_oImage.getHeight());
		setVisible(true);
		std::cout << "magic created, ID: " << m_iObjectID << std::endl;
	}

	~CW2Magic()
	{
		ImageManager::destroyImageManager();
		std::cout << "magic destroied" << std::endl;
	}

	void virtDraw() override
	{
		//std::cout << "magic draw" << std::endl;
		if (!isVisible() || isPause())
			return;

		//m_pEngine->lockForegroundForDrawing();
		m_oImage.renderImageWithMask(m_pEngine->getForegroundSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_oImage.getWidth(), m_oImage.getHeight(), m_oImage.getPixelColour(0, 0));
		//m_pEngine->unlockForegroundForDrawing();
		//redrawDisplay();
	}


	void virtDoUpdate(int iCurrentTime) override
	{
		if (!isVisible() || isPause())
			return;

		//update the position using the angel
		int targetX = cos(m_dAngle) * -m_dSpeed;
		int targetY = sin(m_dAngle) * -m_dSpeed;


		m_iCurrentScreenX += targetX;
		m_iCurrentScreenY += targetY;

		m_dRange -= abs(targetX) + abs(targetY);
		std::cout << "magic m_dRange: "<< m_dRange << std::endl;


		// check if new pos is valid on the tile, if not delete the object, if is check collosions
		if (m_dRange < 0)
		{
			setVisible(false);
			//m_pEngine->deleteThisObject(m_iObjectID);
			std::cout << "magic delete m_dRange: " << m_dRange << std::endl;
		}
		// reach the max range
			

	// todo: hit certain tile magic will return to player and hurt the player

		checkCollisions();
	}


	void checkCollisions()
	{
		//check collosions for each monster
		std::vector<Monster*> vMonster = m_pEngine->getAllObjectsByType<Monster>();

		for (int i = 0; i < vMonster.size(); i++)
		{
			// using rectangles collision detection, cause magic and monsters are renctangle images
			if (CollisionDetection::checkRectangles(
				m_iCurrentScreenX, m_iCurrentScreenX + m_iDrawWidth,
				m_iCurrentScreenY, m_iCurrentScreenY + m_iDrawHeight,
				vMonster.at(i)->getDrawingRegionLeft(), vMonster.at(i)->getDrawingRegionTop() + vMonster.at(i)->getDrawWidth(),
				vMonster.at(i)->getDrawingRegionLeft(), vMonster.at(i)->getDrawingRegionTop() + vMonster.at(i)->getDrawHeight()))
			{
				vMonster.at(i)->beHurt(m_iPower);		// hurt the monster
				if (m_iLevel == 1)		// basic magic only hurt one monster at a time
					break;
				// power magic continue find monster and hurt monster on the way
			}

		}
		m_pEngine->deleteThisObject(m_iObjectID);
	}


	std::vector<std::string> getState() override
	{
		std::vector<std::string> currentState{ "Magic",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_iLevel), std::to_string(m_dAngle) };
		return currentState;
	}


protected:
	int m_iPower;	// how much damage it can do
	
	double m_dSpeed;       // speed
	double m_dSpeedY;
	double m_dRange;
	int m_iLevel;		// which level the magic is
	double m_dAngle;		//magic directin angle
	SimpleImage m_oImage;
};
