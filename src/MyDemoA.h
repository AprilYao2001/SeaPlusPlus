#pragma once
#include "BaseEngine.h"
#include "MyTileManager.h"  // insert this line to define the class

class MyDemoA :
    public BaseEngine
{
public:
    void virtSetupBackgroundBuffer();
    void virtMouseDown(int iButton, int iX, int iY);
    void virtKeyDown(int iKeyCode);


protected:
    MyTileManager tm;   // insert this line for composition as a member variable
public:
    int virtInitialiseObjects();
};

