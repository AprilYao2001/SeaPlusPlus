#pragma once
#include "BaseEngine.h"
#include "CW2StateManager.h"
#include "Config.h"

class CW2Engine :
    public BaseEngine
{
public:
    CW2Engine();
    ~CW2Engine();


    void virtSetupBackgroundBuffer() override;
    int virtInitialiseObjects() override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;
    void virtDrawStringsOnTop() override;

    int virtInitialise() override;

    void virtMainLoopDoBeforeUpdate() override;

    void virtMainLoopDoAfterUpdate() override;

    void copyAllBackgroundBuffer() override;
    
    //void virtMainLoopPostUpdate() override; // After update


	void deleteThisObject(int iObjectID);

    void deleteAllObject();

	// this is a template function to get one object by its type
	template <typename Type> Type* getObjectByType()
	{
		try
		{
			// iterat all objects, if dynamic_cast success then it is the type we are looking for
			for (int i = 0; i < m_vecDisplayableObjects.size(); i++)
			{
				auto thisObject = dynamic_cast<Type*>(m_vecDisplayableObjects.at(i));		// if dynamic cast fall will get a nullptr
				if (thisObject)
					return thisObject;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << "Template function exception: " << e.what() << std::endl;
		}
	}


	// this is a template function to get all objects by there type
	template <typename Type> std::vector<Type*> getAllObjectsByType()
	{
		std::vector<Type*> vObjects;
		try
		{
			// iterat all objects, if dynamic_cast success then it is the type we are looking for
			for (int i = 0; i < m_vecDisplayableObjects.size(); i++)
			{
				auto thisObject = dynamic_cast<Type*>(m_vecDisplayableObjects.at(i));		// if dynamic cast fall will get a nullptr
				if (thisObject)
					vObjects.push_back((Type*)m_vecDisplayableObjects.at(i));
			}

			return vObjects;
		}
		catch (const std::exception& e)
		{
			std::cout << "Template function exception: " << e.what() << std::endl;
		}
	}



private:
    std::unique_ptr<CW2StateManager>m_oStateManager;
};

