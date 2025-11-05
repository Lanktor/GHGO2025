#pragma once

typedef struct _GAME_INFO GAME_INFO, *PGAME_INFO, **PPGAME_INFO;
#define SZ_GAME_INFO sizeof(_GAME_INFO)
#define GAME_INFO_NULL (PGAME_INFO)0

typedef struct _VEC2 VEC2, *PVEC2, **PPVEC2;
#define SZ_VEC2 sizeof(_VEC2)
#define VEC2_NULL (PVEC2)0

typedef struct _BUTTON_INFO BUTTON_INFO, *PBUTTON_INFO, **PPBUTTON_INFO;
#define SZ_BUTTON_INFO sizeof(_BUTTON_INFO)
#define BUTTON_INFO_NULL (PBUTTON_INFO)0

typedef struct _HI_SCORE HI_SCORE, *PHI_SCORE, **PPHI_SCORE;
#define SZ_HI_SCORE sizeof(_HI_SCORE)
#define HI_SCORE_NULL (PHI_SCORE)0


typedef struct _PLAYER_INFO PLAYER_INFO, *PPLAYER_INFO, **PPPLAYER_INFO;
#define SZ_PLAYER_INFO sizeof(_PLAYER_INFO)
#define PLAYER_INFO_NULL (PPLAYER_INFO)0

typedef struct _ENEMY_BASIC_INFO ENEMY_BASIC_INFO, *PENEMY_BASIC_INFO, **PPENEMY_BASIC_INFO;
#define SZ_ENEMY_BASIC_INFO sizeof(_ENEMY_BASIC_INFO)
#define ENEMY_BASIC_INFO_NULL (PENEMY_BASIC_INFO)0

typedef struct _WEAPON_AUTO_INFO WEAPON_AUTO_INFO, *PWEAPON_AUTO_INFO, **PPWEAPON_AUTO_INFO;
#define SZ_WEAPON_AUTO_INFO sizeof(_WEAPON_AUTO_INFO)
#define WEAPON_AUTO_INFO_NULL (PWEAPON_AUTO_INFO)0

typedef struct _ANIM_INFO ANIM_INFO, *PANIM_INFO, **PPANIM_INFO;
#define SZ_ANIM_INFO sizeof(_ANIM_INFO)
#define ANIM_INFO_NULL (PANIM_INFO)0


struct _ANIM_INFO
{
	INT        AI_ActiveFlag;    // Is the Animation Active
	INT        AI_Ident;         // Ident of the Animation
	INT        AI_Type;          // Do animation once, Loop Animation

	INT        AI_MaxSprites;    // This is for sprite List
	INT        AI_CurSprite;     // This is current sprite rendered

	INT        AI_FramesInTimer; // This is for time between switching frames
	INT        AI_FrameTimer;    // Incremented Every Frame and checked against MaxFrames

	//	SDL_FRect  AI_Pos;           // Where we want the animation;
	PSDL_FRect AI_SpriteList;    // Where the Sprites are in the Tile Set 
};


struct _PLAYER_INFO
{
	FLOAT       PI_Scale;

	SDL_FRect   PI_GlobalPos;
	SDL_FRect   PI_LocalPos;

	INT         PI_MaxSprites;    // This is for sprite List
	INT         PI_CurSprite;     // This is current sprite rendered
	INT         PI_FramesInTimer; // This is for time between switching frames
	INT         PI_FrameTimer;    // Incremented Every Frame and checked against MaxFrames

	FLOAT       PI_DirectionX;
	FLOAT       PI_DirectionY;

	PSDL_FRect  PI_SpriteList;    // Where the sprites are located
};

struct _WEAPON_AUTO_INFO
{
	INT         WAI_ActiveFlag;

	FLOAT       WAI_VX;
	FLOAT       WAI_VY;
	FLOAT       WAI_Scale;
	FLOAT       WAI_Speed;
	SDL_FRect   WAI_GlobalPos;
	SDL_FRect   WAI_TargetPos;

	INT         WAI_MaxSprites;    // This is for sprite List
	INT         WAI_CurSprite;     // This is current sprite rendered
	INT         WAI_FramesInTimer; // This is for time between switching frames
	INT         WAI_FrameTimer;    // Incremented Every Frame and checked against MaxFrames

	PSDL_FRect  WAI_SpriteList;    // Where the sprites are located
};

struct _ENEMY_BASIC_INFO
{
	INT         EBI_ActiveFlag;

	FLOAT       EBI_Scale;
	FLOAT       EBI_Speed;
	SDL_FRect   EBI_GlobalPos;
	SDL_FRect   EBI_LocalPos;

	INT         EBI_MaxSprites;    // This is for sprite List
	INT         EBI_CurSprite;     // This is current sprite rendered
	INT         EBI_FramesInTimer; // This is for time between switching frames
	INT         EBI_FrameTimer;    // Incremented Every Frame and checked against MaxFrames

	PSDL_FRect  EBI_SpriteList;    // Where the sprites are located
};


struct _BUTTON_INFO
{
	INT       BI_Ident;
	INT       BI_State;
	INT       BI_TextXOffset;
	INT       BI_TextYOffset;
	SDL_FRect BI_Srce;
	SDL_FRect BI_Dest;
	char      BI_Text[64];
};

struct _HI_SCORE
{
	CHAR HS_Name[MAX_NAME_LENGTH + 1];
	INT  HS_Score;
};


struct _GAME_INFO
{
	INT             GI_CurrentScore;
	INT             GI_CurrentLevel;
	INT             GI_ScreenWidth;
	INT             GI_ScreenHeight;
	INT             GI_GameVersion;
	INT             GI_Active;
	INT             GI_WinLoseFlag;

	INT             GI_TARGET_FPS;
	INT             GI_FRAME_DELAY;
	FLOAT           GI_DeltaTime;
	UINT64          GI_CurTime;
	UINT64          GI_PrevTime;
	UINT64          GI_FrameStart;
	UINT64          GI_FrameTime;
	UINT64          GI_SecondsCounter;
	UINT64          GI_FrameCounter;
	UINT            GI_RNGState;

	FLOAT           GI_MouseX;
	FLOAT           GI_MouseY;
	INT             GI_MouseState;
	INT             GI_MouseDownFlag;
	INT             GI_MouseUpFlag;

	PSDL_FRect      GI_StarField;

	INT             GI_ShowPathFlag;

	PSDL_Window     GI_MainWindow;
	PSDL_Renderer   GI_MainRenderer;
	PMix_Music      GI_BkgMusic;

	FLOAT              GI_AddObjectsCooldown;

	FLOAT              GI_MaxPower;
	FLOAT              GI_CurrentPower;

	PLAYER_INFO        GI_Player;
	CHAR               GI_PlayerName[MAX_NAME_LENGTH + 1];
	HI_SCORE           GI_HiScoreList[MAX_NAMES];

	PENEMY_BASIC_INFO  GI_EBITable[MAX_EBI_OBJECTS];
	INT                GI_EBITotalItems;
	FLOAT              GI_EBISpawnCoolDown;
	FLOAT              GI_EBICurSpawnCoolDown;

	FLOAT              GI_WAISpawnCoolDown;
	FLOAT              GI_WAICurSpawnCoolDown;
	PWEAPON_AUTO_INFO  GI_WAITable[MAX_WAI_OBJECTS];

	PSDL_Texture    GI_MainTexture;
	PSDL_Texture    GI_TextTexture;
	PSDL_Texture    GI_RulesTexture;
	PSDL_Texture    GI_EndOfGameTexture;
	PSDL_Texture    GI_StartOfGameTexture;
	PSDL_Texture    GI_GameBoardTexture;
	PSDL_Texture    GI_BackgroundTexture;
	PSDL_Texture    GI_PlayerTexture;

	PPLAYER_INFO    GI_TestPlayerTable[MAX_TEST_PLAYERS];

};

