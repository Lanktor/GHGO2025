#pragma once

#include <SDL3/SDL.h>
#include <SDL_mixer.h>

typedef FILE *PFILE, **PPFILE;

typedef char CHAR, *PCHAR, **PPCHAR;
typedef const unsigned char UCHAR, *PUCHAR, **PPUCHAR;
typedef const char CCHAR, *PCCHAR, **PPCCHAR;
typedef int INT, *PINT, **PPINT;
typedef unsigned int UINT, *PUINT, **PPUINT;
typedef float FLOAT, *PFLOAT, **PPFLOAT;
typedef double DOUBLE, *PDOUBLE, **PPDOUBLE;
typedef void VOID, *PVOID, **PPVOID;
typedef bool BOOL;
typedef Uint64 UINT64, *PUINT64, **PPUINT64;

typedef SDL_Window *PSDL_Window, **PPSDL_Window;
typedef SDL_Rect *PSDL_Rect, **PPSDL_Rect;
typedef SDL_FRect *PSDL_FRect, **PPSDL_FRect;
#define SZ_SDL_FRECT sizeof(SDL_FRect)
typedef SDL_Renderer *PSDL_Renderer, **PPSDL_Renderer;
typedef SDL_Surface *PSDL_Surface, **PPSDL_Surface;
typedef SDL_Texture *PSDL_Texture, **PPSDL_Texture;
typedef Mix_Music *PMix_Music, **PPMix_Music;
typedef Mix_Chunk *PMix_Chunk, **PPMix_Chunk;

#define TRUE  true
#define FALSE false
#define RANDOM_SEED 3556830853
#define END_OF_LIST 65535

#define MAX_NAME_LENGTH        12
#define MAX_NAMES               5

#define GAME_IS_ACTIVE        5000
#define GAME_IS_INACTIVE      5001
#define OBJECT_IS_ACTIVE      5002
#define OBJECT_IS_NOT_ACTIVE  5003
#define LEVEL_IS_ACTIVE       5004
#define LEVEL_IS_COMPLETE     5005

#define GAME_VERSION          100
#define GAME_BASE_SCORE       5000
#define GAME_MAX_LEVEL_TIME   300 // Seconds

#define TOTAL_STARS        2000
#define RAIN_DROPS         2000
#define STAR_SCROLL_SPEED  50
#define RAIN_SCROLL_SPEED  500

#define FONT_SMALL        100
#define FONT_LARGE        101
#define FONT_MEDIUM_BLACK 102
#define FONT_MEDIUM_WHITE 103
#define FONT_MEDIUM_RED   104

#define LEVEL_ONE   1
#define LEVEL_TWO   2
#define LEVEL_THREE 3
#define LEVEL_FOUR  4
#define LEVEL_FIVE  5
#define LEVEL_SIX   6
#define LEVEL_SEVEN 7
#define LEVEL_EIGHT 8
#define LEVEL_NINE  9
#define LEVEL_TEN   10

#define BUTTON_STATE_UP        1000
#define BUTTON_STATE_DOWN      1001
#define BUTTON_STATE_HOVER     1002
#define BUTTON_IDENT_START     1003
#define BUTTON_IDENT_ROLL      1004
#define BUTTON_IDENT_EXIT      1005
#define BUTTON_IDENT_HELP      1006
#define BUTTON_IDENT_DIAG      1007
#define BUTTON_IDENT_CONTINUE  1008
#define BUTTON_IDENT_HINT      1009
#define BUTTON_IDENT_PLAY      1010
#define BUTTON_IDENT_SKIP      1011
#define BUTTON_IDENT_RULES     1012
#define BUTTON_IDENT_HISCORE   1113
#define BUTTON_IDENT_REPLAY    1114
#define BUTTON_IDENT_NEXT      1115
#define BUTTON_IDENT_NONE      1100


#define BACKGROUND_TEXTURE   "Resources//Background Texture.png"
#define RULESSCREEN_TEXTURE  "Resources//RulesScreen.png"
#define STARTSCREEN_TEXTURE  "Resources//StartofGameScreen.png"
#define ENDSCREEN_TEXTURE    "Resources//EndOfGameScreen.png"
#define PLAYER_TEXTURE       "Resources//Player TileSheet.png"
#define TEXT_TEXTURE         "Resources//Text Sprites.png"
#define MAIN_TEXTURE         "Resources//Main Tile Sheet.png"
#define BACKGROUND_MUSIC     "Resources//Endless-Cyber-Runner-2.mp3"
#define HI_SCORE_FILE        "Resources//HiScore.txt"


