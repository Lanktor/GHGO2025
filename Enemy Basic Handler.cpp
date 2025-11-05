#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT EBI_Initiate(PGAME_INFO GIptr)
{
	INT I;

	for (I = 0; I < MAX_EBI_OBJECTS; I++)
	{
		GIptr->GI_EBITable[I] = (PENEMY_BASIC_INFO)SDL_calloc(1, SZ_ENEMY_BASIC_INFO);
	}
	return(TRUE);
}

INT EBI_Update(PGAME_INFO GIptr)
{
	INT               I;
	PENEMY_BASIC_INFO EBIptr;

	for (I = 0; I < GIptr->GI_EBITotalItems; I++)
	{
		EBIptr = GIptr->GI_EBITable[I];
		if(EBIptr->EBI_ActiveFlag == OBJECT_IS_NOT_ACTIVE) continue;

		EBIptr->EBI_FrameTimer++;
		if (EBIptr->EBI_FrameTimer >= EBIptr->EBI_FramesInTimer)
		{
			EBIptr->EBI_FrameTimer = 0;
			EBIptr->EBI_CurSprite++;
			if (EBIptr->EBI_CurSprite >= EBIptr->EBI_MaxSprites)
			{
				EBIptr->EBI_CurSprite = 0;
			}
		}
		EBI_Move(GIptr, EBIptr);
	}
	return(TRUE);
}

INT EBI_Move(PGAME_INFO GIptr, PENEMY_BASIC_INFO EBIptr)
{
	FLOAT        VX, VY, DX, DY, Dist;
	PPLAYER_INFO PIptr;

	PIptr = &GIptr->GI_Player;

	DX = PIptr->PI_GlobalPos.x - (EBIptr->EBI_GlobalPos.x + EBIptr->EBI_GlobalPos.w / 2);
	DY = PIptr->PI_GlobalPos.y - (EBIptr->EBI_GlobalPos.y + EBIptr->EBI_GlobalPos.h / 2);
	Dist = sqrtf(DX * DX + DY * DY);

	if (Dist > 1.0f)
	{
		VX = (DX / Dist) * EBIptr->EBI_Speed * GIptr->GI_DeltaTime;
		VY = (DY / Dist) * EBIptr->EBI_Speed * GIptr->GI_DeltaTime;
		EBIptr->EBI_GlobalPos.x += VX;
		EBIptr->EBI_GlobalPos.y += VY;

		if ((EBI_CheckForCollisionWithOtherObjects(GIptr, EBIptr)) == COLLISION_DETECTED)
		{
			EBIptr->EBI_GlobalPos.x -= VX;
			EBIptr->EBI_GlobalPos.y -= VY;
		}

	}

	return(TRUE);
}

INT EBI_CheckForCollisionWithOtherObjects(PGAME_INFO GIptr, PENEMY_BASIC_INFO EBIptr)
{
	INT               I;
	PENEMY_BASIC_INFO LocalEBIptr;

	for (I = 0; I < GIptr->GI_EBITotalItems; I++)
	{
		LocalEBIptr = GIptr->GI_EBITable[I];
		if (LocalEBIptr->EBI_ActiveFlag == OBJECT_IS_NOT_ACTIVE) continue;
		if (LocalEBIptr == EBIptr) continue;

		if ((SDL_HasRectIntersectionFloat(&EBIptr->EBI_GlobalPos, &LocalEBIptr->EBI_GlobalPos)) == true) return(COLLISION_DETECTED);
	}


	return(NO_COLLISION_DETECTED);
}

INT EBI_Render(PGAME_INFO GIptr)
{
	INT               I;
	PENEMY_BASIC_INFO EBIptr;

	for (I = 0; I < GIptr->GI_EBITotalItems; I++)
	{
		EBIptr = GIptr->GI_EBITable[I];
		if(EBIptr->EBI_ActiveFlag == OBJECT_IS_NOT_ACTIVE) continue;
		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_PlayerTexture, &EBIptr->EBI_SpriteList[EBIptr->EBI_CurSprite], &EBIptr->EBI_GlobalPos);
	}
	return(TRUE);
}

INT EBI_Clear(PGAME_INFO GIptr)
{
	INT               I;
	PENEMY_BASIC_INFO EBIptr;

	for (I = 0; I < MAX_EBI_OBJECTS; I++)
	{
		EBIptr = GIptr->GI_EBITable[I];

		EBIptr->EBI_ActiveFlag = OBJECT_IS_NOT_ACTIVE;
		EBIptr->EBI_CurSprite = 0;
		EBIptr->EBI_FramesInTimer = 0;
		EBIptr->EBI_FrameTimer = 0;
		EBIptr->EBI_MaxSprites = 0;
		EBIptr->EBI_Scale = 1.0f;
		EBIptr->EBI_Speed = 0;
		EBIptr->EBI_SpriteList = NULL;
		memset(&EBIptr->EBI_GlobalPos, 0, SZ_SDL_FRECT);
		memset(&EBIptr->EBI_LocalPos, 0, SZ_SDL_FRECT);
	}
	return(TRUE);
}
