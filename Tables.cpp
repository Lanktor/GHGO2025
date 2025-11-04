#include <stdio.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

GAME_INFO Gamebuffer;
PGAME_INFO Gameptr = &Gamebuffer;

BUTTON_INFO RulesButtons[] =
{
	{BUTTON_IDENT_CONTINUE, BUTTON_STATE_UP,   48, 18, 0, 750, 211,  61,    30,   40, 211,  61, "RETURN"},
	{BUTTON_IDENT_EXIT,     BUTTON_STATE_UP,   70, 18, 0, 750, 211,  61,    30,  110, 211,  61, "EXIT"},
	{-1,  -1,   -1, -1, -1,  -1, -1, -1, -1,  -1},
};


BUTTON_INFO StartGameButtons[] =
{
	{BUTTON_IDENT_RULES,    BUTTON_STATE_UP,   62, 18, 0, 750, 211,  61,  20, 830, 211,  61, "RULES"},
	{BUTTON_IDENT_PLAY,     BUTTON_STATE_UP,   72, 18, 0, 750, 211,  61,  20, 900, 211,  61, "PLAY"},
	{BUTTON_IDENT_EXIT,     BUTTON_STATE_UP,   70, 18, 0, 750, 211,  61,  20, 970, 211,  61, "EXIT"},
	{-1,  -1,   -1, -1, -1,  -1, -1, -1, -1,  -1},
};

BUTTON_INFO EndGameButtons[] =
{
	{BUTTON_IDENT_REPLAY,  BUTTON_STATE_UP,   48, 18, 0, 750, 211,  61,    30,   40, 211,  61, "REPLAY"},
	{BUTTON_IDENT_EXIT,    BUTTON_STATE_UP,   70, 18, 0, 750, 211,  61,    30,  110, 211,  61, "EXIT"},
	{-1,  -1,   -1, -1, -1,  -1, -1, -1, -1,  -1},
};

SDL_FRect HiScoreBox[] =
{
	{ 215,  140, 700, 400},
};

SDL_FRect OBJSquareStandard[] = 
{
	{   0,  32,  32,  32},
	{  32,  32,  32,  32},
	{  64,  32,  32,  32},
	{  96,  32,  32,  32},
	{ 128,  32,  32,  32},
	{  96,  32,  32,  32},
	{  64,  32,  32,  32},
	{  32,  32,  32,  32},
};

SDL_FRect PlayerAnim[] =
{
	{   0,    0,  32,  32},
	{  32,    0,  32,  32},
	{  64,    0,  32,  32},
	{  32,    0,  32,  32},
	{   0,    0,  32,  32},
};

SDL_FRect FontAlphaWhite[] =
{
	{   0,  45, 21, 20}, // A
	{  23,  45, 17, 20}, // B
	{  43,  45, 18, 20}, // C
	{  65,  45, 17, 20}, // D
	{  86,  45, 16, 20}, // E
	{ 106,  45, 14, 20}, // F
	{ 123,  45, 19, 20}, // G
	{ 146,  45, 17, 20}, // H
	{ 168,  45,  6, 20}, // I
	{ 177,  45, 15, 20}, // J
	{ 197,  45, 20, 20}, // K
	{ 219,  45, 14, 20}, // L
	{ 237,  45, 20, 20}, // M
	{ 262,  45, 17, 20}, // N
	{ 283,  45, 19, 20}, // O
	{ 306,  45, 16, 20}, // P
	{ 325,  45, 20, 22}, // Q
	{ 348,  45, 19, 20}, // R
	{ 367,  45, 18, 20}, // S
	{ 388,  45, 18, 20}, // T
	{ 409,  45, 17, 20}, // U
	{ 429,  45, 21, 20}, // V
	{ 450,  45, 27, 20}, // W
	{ 477,  45, 21, 20}, // X
	{ 498,  45, 22, 20}, // Y
	{ 521,  45, 17, 20}, // Z

};

SDL_FRect FontNumericWhite[] =
{
	{   0,  69, 15, 20}, // 0
	{  19,  69, 11, 20}, // 1
	{  36,  69, 15, 20}, // 2
	{  54,  69, 15, 20}, // 3
	{  72,  69, 17, 20}, // 4
	{  90,  69, 15, 20}, // 5
	{ 108,  69, 15, 20}, // 6
	{ 126,  69, 15, 20}, // 7
	{ 145,  69, 15, 20}, // 8
	{ 162,  69, 15, 20}, // 9
	{ 179,  69, 15, 20}, // 10 Minus sign
	{ 195,  69, 15, 20}, // 11 Full Colon
};

