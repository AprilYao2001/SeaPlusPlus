#pragma once
#include "DisplayableObject.h"


class Scysy2UserObject :
    public DisplayableObject
{
public:
    Scysy2UserObject(BaseEngine* pEngine, int iSize = 2, int iLength = 7, int iColour = 0x641E16, double dXSpeed = 3, double dYSpeed = 3, double dXPos = 500, double dYPos = 200);
    ~Scysy2UserObject(void);

    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    int getCount() const;

    double getLeftX() const;
    double getRightX() const;
    double getLeftY() const;
    double getRightY() const;

private:
    BaseEngine* m_pEngine;
    int m_iLength;      // length of the body

    double m_dSX;       // speed
    double m_dSY;

    double m_dHX;       // head position 
    double m_dHY;
    double m_dHUpX = 0;
    double m_dHUpY = 0;
    double m_dHDownX = 0;
    double m_dHDownY = 0;

    bool m_bLeft = false;       // head derection
    bool m_bRight = false;
    bool m_bUp = true;
    bool m_bDown = false;

    int m_iCount;       // collision count

    bool m_bAuto = true;      // how the object move, auto or user mouse control    
};

