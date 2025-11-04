#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT TEST_Initiate(PGAME_INFO GIptr)
{
	INT          I, Dir;
	PPLAYER_INFO PIptr;
	extern SDL_FRect PlayerAnim[];

	for (I = 0; I < MAX_TEST_PLAYERS; I++)
	{
		PIptr = GIptr->GI_TestPlayerTable[I] = (PPLAYER_INFO)SDL_calloc(1, SZ_PLAYER_INFO);

		PIptr->PI_SpriteList = PlayerAnim;
		PIptr->PI_FramesInTimer = 8;
		PIptr->PI_FrameTimer = 0;
		PIptr->PI_MaxSprites = 5;
		PIptr->PI_CurSprite = 0;
		PIptr->PI_Scale = .5f;
		PIptr->PI_GlobalPos.x = UTIL_RandomFloatRange(20, 1900);
		PIptr->PI_GlobalPos.y = UTIL_RandomFloatRange(20, 1060);

		Dir = UTIL_RandomIntRange(&GIptr->GI_RNGState, 0, 1);
		PIptr->PI_DirectionX = (Dir == 0) ? -1.0f : 1.0f;

		Dir = UTIL_RandomIntRange(&GIptr->GI_RNGState, 0, 1);
		PIptr->PI_DirectionY = (Dir == 0) ? -1.0f : 1.0f;
	}
	return(TRUE);
}

INT TEST_Update(PGAME_INFO GIptr)
{
	INT          I;
	PPLAYER_INFO PIptr;

	for (I = 0; I < MAX_TEST_PLAYERS; I++)
	{
		PIptr = GIptr->GI_TestPlayerTable[I];
		PIptr->PI_FrameTimer++;
		if (PIptr->PI_FrameTimer >= PIptr->PI_FramesInTimer)
		{
			PIptr->PI_FrameTimer = 0;
			PIptr->PI_CurSprite++;
			if (PIptr->PI_CurSprite >= PIptr->PI_MaxSprites)
			{
				PIptr->PI_CurSprite = 0;
			}
		}

		PIptr->PI_GlobalPos.x += (PLAYER_SPEED * PIptr->PI_DirectionX) * GIptr->GI_DeltaTime;
		PIptr->PI_GlobalPos.y += (PLAYER_SPEED * PIptr->PI_DirectionY) * GIptr->GI_DeltaTime;

		if ((PIptr->PI_GlobalPos.x >= 1920) || (PIptr->PI_GlobalPos.x <= 0)) PIptr->PI_DirectionX *= -1.0f;
		if ((PIptr->PI_GlobalPos.y >= 1080) || (PIptr->PI_GlobalPos.y <= 0)) PIptr->PI_DirectionY *= -1.0f;
	}
	return(TRUE);
}

INT TEST_Render(PGAME_INFO GIptr)
{
	INT          I;
	PPLAYER_INFO PIptr;
	PSDL_FRect   Srceptr;

	for (I = 0; I < MAX_TEST_PLAYERS; I++)
	{
		PIptr = GIptr->GI_TestPlayerTable[I];

		Srceptr = &PIptr->PI_SpriteList[PIptr->PI_CurSprite];
		PIptr->PI_GlobalPos.w = Srceptr->w * PIptr->PI_Scale;
		PIptr->PI_GlobalPos.h = Srceptr->h * PIptr->PI_Scale;
		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_PlayerTexture, Srceptr, &PIptr->PI_GlobalPos);
	}
	return(TRUE);
}

 