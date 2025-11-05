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
	PIptr->PI_GlobalPos.w = PlayerAnim->w * PIptr->PI_Scale;
	PIptr->PI_GlobalPos.h = PlayerAnim->h * PIptr->PI_Scale;

	return(TRUE);
}

INT PLAYER_Move(PGAME_INFO GIptr)
{
	FLOAT        VX, VY, DX, DY, Dist;
	PPLAYER_INFO PIptr;

	PIptr = &GIptr->GI_Player;

	DX = GIptr->GI_MouseX - (PIptr->PI_GlobalPos.x + PIptr->PI_GlobalPos.w / 2);
	DY = GIptr->GI_MouseY - (PIptr->PI_GlobalPos.y + PIptr->PI_GlobalPos.h / 2);
	Dist = sqrtf(DX * DX + DY * DY);

	if (Dist > 1.0f) 
	{
		GIptr->GI_SaveDirX = DX / Dist;
		GIptr->GI_SaveDirY = DY / Dist;

		VX = (DX / Dist) * PLAYER_SPEED * GIptr->GI_DeltaTime;
		VY = (DY / Dist) * PLAYER_SPEED * GIptr->GI_DeltaTime;
		PIptr->PI_GlobalPos.x += VX;
		PIptr->PI_GlobalPos.y += VY;
	}

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

	return(TRUE);
}

INT PLAYER_Render(PGAME_INFO GIptr)
{
	INT          I;
	PPLAYER_INFO PIptr;
	PSDL_FRect   Srceptr;

	PIptr = &GIptr->GI_Player;

	Srceptr = &PIptr->PI_SpriteList[PIptr->PI_CurSprite];
	SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_PlayerTexture, Srceptr, &PIptr->PI_GlobalPos);

	UTIL_DrawCollisionBox(GIptr, &PIptr->PI_GlobalPos, {0x00, 0x00, 0xFF, 0x00}, 2);

	return(TRUE);
}



