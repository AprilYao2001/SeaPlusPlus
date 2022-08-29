#pragma once
#include "header.h"
#include "CW2Object.h"
#include "CW2Magic.h"


/*This is the base class for spirte's wand, wand is the container for magic*/
class CW2Wand :
    public CW2Object
{
public:
	CW2Wand(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iLevel, int iWidth = 0, int iHeight = 0)
		:CW2Object(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight)
		,m_iLevel(iLevel)
	{
		if (m_iLevel == 1)
			m_oImage = ImageManager::loadImage("images\\wand1_32x32px.png", true);		// basic wand
		else
			m_oImage = ImageManager::loadImage("images\\wand2_32x32px.png", true);		//power wand

		setSize(m_oImage.getWidth(), m_oImage.getHeight());
		std::cout << "wand created" << std::endl;
		setVisible(true);
	};

	~CW2Wand()
	{
		ImageManager::destroyImageManager();
		std::cout << "wand destroied" << std::endl;
	}


public:
	void draw()
	{
		m_pEngine->lockForegroundForDrawing();
		if (isVisible()||!isPause())
			m_oImage.renderImageWithMask(m_pEngine->getForegroundSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_oImage.getWidth(), m_oImage.getHeight(), m_oImage.getPixelColour(0, 0));
		m_pEngine->unlockForegroundForDrawing();
		redrawDisplay();
	}
	
	void updatePos(int x, int y)
	{
		m_iCurrentScreenX = x;
		m_iCurrentScreenY = y;
	}


	virtual void useMagic()
	{
		if (!isVisible() || isPause())
			return;

		int targetX = m_pEngine->getCurrentMouseX();
		int targetY = m_pEngine->getCurrentMouseY();

		double clickAngle = atan2(getYCentre() - targetY, getXCentre() - targetX);

		m_pEngine->lockForegroundForDrawing();
		m_pEngine->drawableObjectsChanged();
		m_pEngine->appendObjectToArray(new CW2Magic(getXCentre(), getYCentre(), m_pEngine, m_iLevel, clickAngle));
		std::cout << "add succ" << std::endl;
		m_pEngine->unlockForegroundForDrawing();
		redrawDisplay();
	}

	void setLevel(int level) { m_iLevel = level; }


	std::vector<std::string> getState() override
	{
		std::vector<std::string> currentState{ "Wand",std::to_string(m_iCurrentScreenX), std::to_string(m_iCurrentScreenY), std::to_string(m_iLevel) };
		return currentState;
	}

protected:

    double m_dAngle;
	SimpleImage m_oImage;

	int m_iLevel;		// which level the wand is
};