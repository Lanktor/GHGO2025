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
	extern SDL_FRect  EnemyBasicSprites[];

	EBI_Clear(GIptr);
	GIptr->GI_EBITotalItems = 30;

	for (I = 0; I < GIptr->GI_EBITotalItems; I++)
	{
		EBIptr = GIptr->GI_EBITable[I];

		EBIptr->EBI_ActiveFlag = OBJECT_IS_ACTIVE;
		EBIptr->EBI_CurSprite = 0;
		EBIptr->EBI_FramesInTimer = 8;
		EBIptr->EBI_FrameTimer = 0;
		EBIptr->EBI_MaxSprites = 8;
		EBIptr->EBI_Scale = 1.0;
		EBIptr->EBI_Speed = (PLAYER_SPEED / 2);
		EBIptr->EBI_SpriteList = EnemyBasicSprites;
		EBIptr->EBI_GlobalPos.w = (EnemyBasicSprites->w * EBIptr->EBI_Scale);
		EBIptr->EBI_GlobalPos.h = (EnemyBasicSprites->h * EBIptr->EBI_Scale);


		for( ; ; )
		{
			EBIptr->EBI_GlobalPos.x = UTIL_RandomFloatRange(-40, 2000);
			EBIptr->EBI_GlobalPos.y = UTIL_RandomFloatRange(-40, 1200);
			if ((EBI_CheckForCollisionWithOtherObjects(GIptr, EBIptr)) == NO_COLLISION_DETECTED) break;
		}
	}

	GIptr->GI_EBITable[I]->EBI_ActiveFlag = OBJECT_END_OF_LEVEL_LIST;

	return(TRUE);
}
