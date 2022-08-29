#pragma once
#include "DisplayableObject.h"
#include "UtilCollisionDetection.h"
#include "Scysy2TileManager.h"



class Scysy2Object :
    public DisplayableObject
{
public:
    Scysy2Object(BaseEngine* pEngine, int iSizeR, int iColour, Scysy2TileManager* m_pTileManager = NULL, double dXSpeed = 3, double dYSpeed = 2.5, int dXPos = 100, int dYPos = 30);
    ~Scysy2Object(void);
    
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    int getCount() const { return m_iCount; }
    double getLeftX() const;
    double getRightX() const;
    double getLeftY() const;
    double getRightY() const;
    bool getShapeIsOval() const { return m_bIsOval; }

private:
    BaseEngine* m_pEngine;
    Scysy2TileManager* m_pTileManager;
    double m_dSX;       // speed
    double m_dSY;

    double m_dX;       // object position
    double m_dY;

    int m_iCount;       // collision count

    bool m_bIsOval = true;      // if the object is Oval
};
