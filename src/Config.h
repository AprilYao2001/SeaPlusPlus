#pragma once

enum  GameState { INITIAL, MENU, PLAY, GAMEOVER, HIGHSCORE };		// game state


const int TILE_WIDTH = 32;			// each tile size to draw mp is 32px*32px
const int TILE_HEIGHT = 32;

const int MAP_WIDTH = 25* TILE_WIDTH;
const int MAP_HEIGHT = 20* TILE_HEIGHT;

const int START_DRAW_X = 250;		//   = (BaseScreenWidth - MAP_WIDTH) / 2
const int START_DRAW_Y = 80;		//   = (BaseScreenHeight - MAP_HEIGHT)/2

const int VALIDX_START = 266;		//  vaild start coord on map(in the wall)
const int VALIDY_START = 96;

const int VALIDX_END = 1034;		//  vaild end coord on map(in the wall)
const int VALIDY_END= 704;


const unsigned int CRMain = 0x154360;		// main game background colour
const unsigned int CRBlack = 0x000000;
const unsigned int CRString = 0x948E6B;		// String colour on the screen
const unsigned int CRString2 = 0x45B39D;		// String colour on the screen, for highlight

const int SCREENWIDTH = 1300;		// default screen size
const int SCREENHEIGHT = 800;


const int PLAYER_BOTTOM_EMPTY = 18;		// the distance from play's foot to image bottom
const int PLAYER_TOP_EMPTY = 9;		// the distance from play's head to image top
const int PLAYER_LEFT_EMPTY = 5;		// the distance from play's left to image left
const int PLAYER_RIGHT_EMPTY = 14;		// the distance from play's right to image right

const int MONSTER_CREATE_TIME_MAX = 10000;			// between how many times the monster will be create
const int MONSTER_CREATE_TIME_MIN = 6000;
