#pragma once
#include "DisplayableObject.h"
class MyObjectB :
    public DisplayableObject
{
public:
    /*The base class constructor needs a pointer to the
    main program class (BaseEngine subclass).To handle this problem we need to accept this pointer in
    our own constructorand pass it on to the base class constructor manually.*/
    MyObjectB(BaseEngine* pEngine);

   // or you can do the constructor inline, it doesn't do anything so is safe to inline
   /* MyObjectB(BaseEngine* pEngine)
        : DisplayableObject(100, 200, pEngine, 100, 200, true)      // (starting x coordinates, starting y coordinates, pointer, width, hight, target at topleft), if faluse = center
    {}*/           

    void virtDraw();
    void virtDoUpdate(int iCurrentTime);
};

