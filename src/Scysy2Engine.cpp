#include "header.h"
#include "Scysy2Engine.h"
#include "Scysy2Object.h"
#include "Scysy2UserObject.h"

#if 0

/*Draw a background*/
void Scysy2Engine::virtSetupBackgroundBuffer()
{

	unsigned int uiWidthColor = 0xF5EEF8;
	int iHeightChange = getWindowHeight()/10;

	for (int iY = 0; iY < getWindowHeight(); iY++) {
		for (int iX = 0; iX < this->getWindowWidth(); iX++) {
			setBackgroundPixel(iX, iY, uiWidthColor);
		}

		switch (iY/iHeightChange)
		{
		case 1: uiWidthColor = 0xE8DEF0; break;
		case 2: uiWidthColor = 0xD7BDE2; break;
		case 3: uiWidthColor = 0xC39BD3; break;
		case 4: uiWidthColor = 0xAF7AC5; break;
		case 5: uiWidthColor = 0x9B59B6; break;
		case 6: uiWidthColor = 0x884EA0; break;
		case 7: uiWidthColor = 0x76448A; break;
		case 8: uiWidthColor = 0x633974; break;
		case 9: uiWidthColor = 0x512E5F; break;
		case 10:uiWidthColor = 0x000000; break;
		default:break;
		}
	}

	for (int iLine = 3; iLine < 10; iLine++) {
		drawBackgroundString(500, (10 + iLine * iHeightChange), "Background Text", uiDrawColor, NULL);
	}

	SimpleImage image = ImageManager::loadImage("oranges.png", true);
	image.renderImageWithMask(getBackgroundSurface(), 0, 0, 300, 0,
		image.getWidth(), image.getHeight(), 0x000000);

	// Draw tiles using the tile manager
	// Specify how many tiles wide and high
	o_MyTile.setMapSize(6, 9);
	// Specify the screen x,y of top left corner
	o_MyTile.setTopLeftPositionOnScreen(150, 300);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 9; j++)
			o_MyTile.setMapValue(i, j, 0xA2D9CE + j * i);
	}
	o_MyTile.drawAllTiles(this, getBackgroundSurface()); // Draw to background
}


/*Handle the mouse press*/
void Scysy2Engine::virtMouseDown(int iButton, int iX, int iY)
{
	if (iButton == SDL_BUTTON_LEFT) {
		lockBackgroundForDrawing();
		if (iLastMouseClickX == -1 || iLastMouseClickY == -1) {
			// do nothing
		} else {
			drawBackgroundThickLine(iLastMouseClickX, iLastMouseClickY, iX, iY, uiDrawColor, 2);
		}
		iLastMouseClickX = iX;
		iLastMouseClickY = iY;
		unlockBackgroundForDrawing();
		redrawDisplay();
	}
}


/*Handle the key press*/
void Scysy2Engine::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case ' ': uiDrawColor = 0xFFFFFF; 
		lockBackgroundForDrawing();
		drawBackgroundRectangle(iLastMouseClickX + 5, iLastMouseClickY + 5, iLastMouseClickX + 10, iLastMouseClickY + 10, uiDrawColor); 
		unlockBackgroundForDrawing();
		redrawDisplay();
		break;
	case 'r': uiDrawColor = 0xEC7063;
		lockBackgroundForDrawing();
		drawBackgroundRectangle(iLastMouseClickX + 5, iLastMouseClickY + 5, iLastMouseClickX + 10, iLastMouseClickY + 10, uiDrawColor);
		unlockBackgroundForDrawing();
		redrawDisplay();
		break;
	case 'g': uiDrawColor = 0x58D68D;
		lockBackgroundForDrawing();
		drawBackgroundRectangle(iLastMouseClickX + 5, iLastMouseClickY + 5, iLastMouseClickX + 10, iLastMouseClickY + 10, uiDrawColor);
		unlockBackgroundForDrawing();
		redrawDisplay();
		break;
	case 'b': uiDrawColor = 0x3498DB; 
		lockBackgroundForDrawing();
		drawBackgroundRectangle(iLastMouseClickX + 5, iLastMouseClickY + 5, iLastMouseClickX + 10, iLastMouseClickY + 10, uiDrawColor);
		unlockBackgroundForDrawing();
		redrawDisplay();
		break;
	case SDLK_ESCAPE:		// clean the screen
		lockBackgroundForDrawing();
		virtSetupBackgroundBuffer();
		iLastMouseClickX = -1;
		iLastMouseClickY = -1;
		unlockBackgroundForDrawing();
		redrawDisplay();
	default : uiDrawColor = 0xF5B041;
		lockBackgroundForDrawing();
		drawBackgroundRectangle(iLastMouseClickX + 5, iLastMouseClickY + 5, iLastMouseClickX + 10, iLastMouseClickY + 10, uiDrawColor);
		unlockBackgroundForDrawing();
		redrawDisplay();
		break;
	}
}


void Scysy2Engine::virtDrawStringsOnTop()
{
	// Build the string to print
	char buf[128];
	sprintf(buf, "Collision Count for biggest auto move object:  %d", (dynamic_cast <Scysy2Object*>(getDisplayableObject(2))) -> getCount());
	drawForegroundString(270, 20, buf, uiDrawColor, NULL);
}

int Scysy2Engine::virtInitialiseObjects()
{
	// Record the fact that we are about to change the array
	// so it doesn't get used elsewhere without reloading it
	drawableObjectsChanged();

	// Destroy any existing objects
	destroyOldObjects(true);

	// Creates an array big enough for the number of objects that you want.
	createObjectArray(4);

	// You MUST set the array entry after the last one that you create to NULL,
	// so that the system knows when to stop.
	storeObjectInArray(0, new Scysy2Object(this, 50, uiDrawColor, &o_MyTile));
	storeObjectInArray(1, new Scysy2Object(this, 100, 0x6E2C00, &o_MyTile,  3, 4));
	storeObjectInArray(2, new Scysy2Object(this, 150, 0x000000, &o_MyTile, 5, 4, 20, 10));
	storeObjectInArray(3, new Scysy2UserObject(this, 50));
	printf("user object center at % d % d\n", getDisplayableObject(2)-> getXCentre(), getDisplayableObject(2)->getYCentre());

	//int iObjectX = getDisplayableObject(2)->getXCentre();
	//int iObjectY = getDisplayableObject(2)->getYCentre();

	//if (o_MyTile.isValidTilePosition(iObjectX, iObjectY))
	//{
	//	for (int i = 0; i < 6; i++) {
	//		for (int j = 0; j < 9; j++)
	//			o_MyTile.setMapValue(i, j, o_MyTile.getMapValue(i,j)+ j * i);
	//	}
	//	o_MyTile.drawAllTiles(this, getBackgroundSurface()); // Draw to background
	//	redrawDisplay(); // Force background to be redrawn to foreground
	//}

	// NOTE: We also need to destroy the objects, but the method at the
	// top of this function will destroy all objects pointed at by the
	// array elements so we can ignore that here.

	setAllObjectsVisible(true);
	return 0;
}

#endif