#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT PLAYER_Initiate(PGAME_INFO GIptr)
{
	PPLAYER_INFO PIptr;
	extern SDL_FRect PlayerAnim[];

	PIptr = &GIptr->GI_Player;

	PIptr->PI_SpriteList = PlayerAnim;
	PIptr->PI_FramesInTimer = 8;
	PIptr->PI_FrameTimer = 0;
	PIptr->PI_MaxSprites = 5;
	PIptr->PI_CurSprite = 0;
	PIptr->PI_Scale = 1.0f;
	PIptr->PI_GlobalPos.x = (1920 / 2);
	PIptr->PI_GlobalPos.y = (1080 / 2);

	return(TRUE);
}

INT PLAYER_Update(PGAME_INFO GIptr)
{
	PPLAYER_INFO PIptr;

	PIptr = &GIptr->GI_Player;

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

	PIptr->PI_GlobalPos.x += PLAYER_SPEED * GIptr->GI_DeltaTime;
	PIptr->PI_GlobalPos.y += PLAYER_SPEED * GIptr->GI_DeltaTime;

	return(TRUE);
}

INT PLAYER_Render(PGAME_INFO GIptr)
{
	PPLAYER_INFO PIptr;
	PSDL_FRect   Srceptr;

	PIptr = &GIptr->GI_Player;

	Srceptr = &PIptr->PI_SpriteList[PIptr->PI_CurSprite];
	PIptr->PI_GlobalPos.w = Srceptr->w * PIptr->PI_Scale;
	PIptr->PI_GlobalPos.h = Srceptr->h * PIptr->PI_Scale;
	SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_PlayerTexture, Srceptr, &PIptr->PI_GlobalPos);
	return(TRUE);
}



