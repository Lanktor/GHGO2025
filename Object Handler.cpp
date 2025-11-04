#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT OBJ_Initiate(PGAME_INFO GIptr)
{
	INT I;

	for (I = 0; I < MAX_OBJECTS; I++)
	{
		GIptr->GI_OBJTable[I] = (POBJ_INFO)SDL_calloc(1, SZ_OBJ_INFO);
	}
	return(TRUE);
}

INT OBJ_Update(PGAME_INFO GIptr)
{
	INT       I;
	POBJ_INFO OIptr;

	for (I = 0; I < GIptr->GI_ObjectLevelItems; I++)
	{
		OIptr = GIptr->GI_OBJTable[I];

		OIptr->OI_FrameTimer++;
		if (OIptr->OI_FrameTimer >= OIptr->OI_FramesInTimer)
		{
			OIptr->OI_FrameTimer = 0;
			OIptr->OI_CurSprite++;
			if (OIptr->OI_CurSprite >= OIptr->OI_MaxSprites)
			{
				OIptr->OI_CurSprite = 0;
			}
		}
		OBJ_Move(GIptr, OIptr);
	}
	return(TRUE);
}

INT OBJ_Move(PGAME_INFO GIptr, POBJ_INFO OIptr)
{
	FLOAT        VX, VY, DX, DY, Dist;
	PPLAYER_INFO PIptr;

	PIptr = &GIptr->GI_Player;

	DX = PIptr->PI_GlobalPos.x - (OIptr->OI_GlobalPos.x + OIptr->OI_GlobalPos.w / 2);
	DY = PIptr->PI_GlobalPos.y - (OIptr->OI_GlobalPos.y + OIptr->OI_GlobalPos.h / 2);
	Dist = sqrtf(DX * DX + DY * DY);

	if (Dist > 1.0f)
	{
		VX = (DX / Dist) * OIptr->OI_Speed * GIptr->GI_DeltaTime;
		VY = (DY / Dist) * OIptr->OI_Speed * GIptr->GI_DeltaTime;
		OIptr->OI_GlobalPos.x += VX;
		OIptr->OI_GlobalPos.y += VY;
	}

	return(TRUE);
}

INT OBJ_Render(PGAME_INFO GIptr)
{
	INT       I;
	SDL_FRect Dest;
	POBJ_INFO OIptr;

	for (I = 0; I < GIptr->GI_ObjectLevelItems; I++)
	{
		OIptr = GIptr->GI_OBJTable[I];
		memcpy(&Dest, &OIptr->OI_GlobalPos, SZ_SDL_FRECT);
		Dest.w = (OIptr->OI_SpriteList[OIptr->OI_CurSprite].w * OIptr->OI_Scale);
		Dest.h = (OIptr->OI_SpriteList[OIptr->OI_CurSprite].h * OIptr->OI_Scale);
		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_PlayerTexture, &OIptr->OI_SpriteList[OIptr->OI_CurSprite], &Dest);
	}
	return(TRUE);
}

INT OBJ_BuildWAVEOne(PGAME_INFO GIptr)
{
	INT              I;
	POBJ_INFO        OIptr;
	extern SDL_FRect OBJSquareStandard[];

	OBJ_Clear(GIptr);
	GIptr->GI_ObjectLevelItems = 100;

	for (I = 0; I < GIptr->GI_ObjectLevelItems; I++)
	{
		OIptr = GIptr->GI_OBJTable[I];

		OIptr->OI_ActiveFlag = OBJECT_IS_ACTIVE;
		OIptr->OI_CurSprite = 0;
		OIptr->OI_FramesInTimer = 8;
		OIptr->OI_FrameTimer = 0;
		OIptr->OI_MaxSprites = 8;
		OIptr->OI_Scale = 1.0;
		OIptr->OI_Speed = (PLAYER_SPEED / 2);
		OIptr->OI_Type = TYPE_OBJ_SQUARE_GRADE0;
		OIptr->OI_SpriteList = OBJSquareStandard;
		OIptr->OI_Type = TYPE_OBJ_SQUARE_GRADE0;

		OIptr->OI_GlobalPos.x = UTIL_RandomFloatRange(-40, 300);
		OIptr->OI_GlobalPos.y = UTIL_RandomFloatRange(-40, 1200);
	}

	GIptr->GI_OBJTable[I]->OI_ActiveFlag = OBJECT_END_OF_LEVEL_LIST;

	return(TRUE);
}

INT OBJ_Clear(PGAME_INFO GIptr)
{
	INT       I;
	POBJ_INFO OIptr;

	for (I = 0; I < MAX_OBJECTS; I++)
	{
		OIptr = GIptr->GI_OBJTable[I];

		OIptr->OI_ActiveFlag = OBJECT_IS_NOT_ACTIVE;
		OIptr->OI_CurSprite = 0;
		OIptr->OI_FramesInTimer = 0;
		OIptr->OI_FrameTimer = 0;
		OIptr->OI_MaxSprites = 0;
		OIptr->OI_Scale = 1.0f;
		OIptr->OI_Speed = 0;
		OIptr->OI_SpriteList = NULL;
		OIptr->OI_Type = TYPE_OBJ_NONE;
		memset(&OIptr->OI_GlobalPos, 0, SZ_SDL_FRECT);
		memset(&OIptr->OI_LocalPos, 0, SZ_SDL_FRECT);
	}
	return(TRUE);
}

