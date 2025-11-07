#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT LEVEL_BuildOne(PGAME_INFO GIptr)
{
	INT               I;
	PENEMY_BASIC_INFO EBIptr;
	PPLAYER_INFO      PIptr;
	extern SDL_FRect  GingerBreadmanSprites[];

	PIptr = &GIptr->GI_Player;
	EBI_Clear(GIptr);
	GIptr->GI_EBITotalItems = 30;

	for (I = 0; I < GIptr->GI_EBITotalItems; I++)
	{
		EBIptr = GIptr->GI_EBITable[I];

		EBIptr->EBI_ActiveFlag = OBJECT_IS_ACTIVE;
		EBIptr->EBI_CurSprite = 0;
		EBIptr->EBI_FramesInTimer = 12;
		EBIptr->EBI_FrameTimer = 0;
		EBIptr->EBI_MaxSprites = 3;
		EBIptr->EBI_Scale = 1.0f;
		EBIptr->EBI_Speed = (PLAYER_SPEED / 2);
		EBIptr->EBI_SpriteList = GingerBreadmanSprites;

		EBIptr->EBI_GlobalPos.w = (GingerBreadmanSprites->w * EBIptr->EBI_Scale);
		EBIptr->EBI_GlobalPos.h = (GingerBreadmanSprites->h * EBIptr->EBI_Scale);


		for( ; ; )
		{
			EBIptr->EBI_GlobalPos.x = UTIL_RandomFloatRange(-40, 500);
			EBIptr->EBI_GlobalPos.y = UTIL_RandomFloatRange(-40, 500);

			if((UTIL_CheckInsideCircle(GIptr, &EBIptr->EBI_GlobalPos, PIptr->PI_GlobalPos.x, PIptr->PI_GlobalPos.y, 200.0f)) == true) continue;

			if ((EBI_CheckForCollisionWithOtherObjects(GIptr, EBIptr)) == NO_COLLISION_DETECTED) break;
		}
	}

	GIptr->GI_EBITable[I]->EBI_ActiveFlag = OBJECT_END_OF_LEVEL_LIST;
	GIptr->GI_LevelCurCoolDown = 0;
	return(TRUE);
}
