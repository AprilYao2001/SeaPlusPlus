#pragma once
#include "SimpleImage.h"
#include <vector>
#include "CW2ImagePixelMapping.h"

/*This is the class to manage the animation used in the game*/

class CW2AnimatedManager : public CW2ImagePixelMapping
{

public:

	// constrctor for one image for one frames 
	/*CW2AnimatedManager(std::vector<SimpleImage> vAnim, int iSpeed = 200, bool bSet = false)
		: CW2ImagePixelMapping()
		,m_vAnim(vAnim)
		,m_iSpeed(iSpeed)
		,m_bSet(bSet)
	{
		m_iFrames = vAnim.size();
		m_iCurrentFrame = 0;
		m_oAnim = m_vAnim[m_iCurrentFrame];
		m_iWidth = m_oAnim.getWidth();
		m_iHeight = m_oAnim.getHeight();
		m_oMapping.setXShift(0);
		m_oMapping.setYShift(0);
	}*/


	// constrctor for if one image contain all the frames
	CW2AnimatedManager(SimpleImage oAnim, int iFrame, int iSpeed = 200, bool bSet=true)
		:CW2ImagePixelMapping()
		,m_iSpeed(iSpeed)
		,m_bSet(bSet)
	{
		m_pAnim = std::make_shared<CW2ImagePixelMapping>(oAnim.getRawImageData());
		m_iFrames = iFrame;
		m_iCurrentFrame = 0;
		m_iWidth = oAnim.getWidth() / iFrame;
		m_iHeight = oAnim.getHeight();
		m_oMapping.setXShift(0);
		m_oMapping.setYShift(0);
	}

	// deconstructor
	~CW2AnimatedManager() 
	{
		std::vector<CW2ImagePixelMapping>().swap(m_vAnim);		// clear the vetor and free memory
		ImageManager::destroyImageManager();
	}

	void drawThisFram(BaseEngine* pEngine, DrawingSurface* pTarget, int iXDrawLocation, int iYDrawLocation)
	{
		if (m_bSet)
		{
			// change the mapping to current frame and render the frame
			m_oMapping.setXShift(m_iWidth * ((pEngine->getRawTime() / m_iSpeed) % m_iFrames));
			m_pAnim->renderImageApplyingMappingAndMask(pEngine, pTarget,
				iXDrawLocation, iYDrawLocation, m_iWidth, m_iHeight, m_pAnim->getPixelColour(0,0), &m_oMapping);
		}
		else
		{
			CW2ImagePixelMapping m_oAnim = m_vAnim[m_iCurrentFrame];

			// change the current frame index and render the frame
			m_iCurrentFrame =(pEngine->getRawTime() / m_iSpeed) % m_iFrames;
			m_oAnim.setTransparencyColour(m_oAnim.getPixelColour(0,0));
			m_oAnim.renderImageBlit(pEngine, pTarget, iXDrawLocation, iYDrawLocation, iXDrawLocation+ m_iWidth, iYDrawLocation+ m_iHeight, 0, 0, m_iWidth, m_iHeight);
		}
	}


	

	

private:
	int m_iFrames;		// total frames
	int m_iSpeed;		// the delay betweeen frames in millisecond
	int m_iCurrentFrame;		// which frame need render now

	int m_iWidth;
	int m_iHeight;

	std::shared_ptr<CW2ImagePixelMapping> m_pAnim;		// use for if one image contain all frames to draw the animation
	CW2ImagePixelMapping m_oMapping;		// which frame need render now

	std::vector<CW2ImagePixelMapping> m_vAnim;		// use for is one image is one m_oAnim
	bool m_bSet;
};
