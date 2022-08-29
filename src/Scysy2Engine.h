#pragma once
#include "BaseEngine.h"
#include "Scysy2TileManager.h"

class Scysy2Engine :
    public BaseEngine
{
public:
    void virtSetupBackgroundBuffer() override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;
    void virtDrawStringsOnTop() override;
    int virtInitialiseObjects() override;

private:
    int iLastMouseClickX = -1;
    int iLastMouseClickY = -1;
    unsigned int uiDrawColor = 0xF5B041;

protected:
    Scysy2TileManager o_MyTile;
};

