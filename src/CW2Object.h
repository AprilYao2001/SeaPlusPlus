#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "CW2Engine.h"
#include "DisplayableObjectContainer.h"

static int m_iObjectNumber = 0;

/*This is the intermediate class for all of the objects in the Engine, it doesnot have complex function so I just write as header file,
it is a subclass of DisplayableObject, all the objects in the Engine is the subclass of CW2Object
since all my member object is created by sharted_ptr*/

class CW2Object :
    public DisplayableObject, public DisplayableObjectContainer
{

protected:

	// Constructor, using top-left as (0,0) to draw the current position coordinate
	// make the constructor protected, will not accidently creat a object of this class
	// it's actuactly an abstract class but make it more safe
	CW2Object(int iStartXCoord, int iStartYCoord, BaseEngine* pEngine, int iWidth, int iHeight)
		: DisplayableObject(iStartXCoord, iStartYCoord, pEngine, iWidth, iHeight)
		,m_pEngine(dynamic_cast<CW2Engine*>(pEngine))
	{
		m_iObjectID = ++m_iObjectNumber;
		setVisible(true);
	}

	~CW2Object() {}


public:

	//CW2Object* getObject() { return this; }


	
	virtual std::vector<std::string> getState() { return std::vector<std::string>(); }		//subclass can override this to save state to file

	//// Getter and Setter
	int getObjectNumber() const	{ return m_iObjectNumber; }
	int getObjectID() const { return m_iObjectID; }
	void setPause(bool bPause)	{ m_bPause = bPause; }
	bool isPause() const		{ return m_bPause; }

protected:
		// the cuntor for how many objects are created now
	int m_iObjectID = 0;			// the unique ID that each object has
	bool m_bPause = false;
	CW2Engine* m_pEngine;
};

