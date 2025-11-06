#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT FF_Render(PGAME_INFO GIptr)
{
	PPLAYER_INFO     PIptr;
	SDL_FRect        Dest;
	extern SDL_FRect ForceFieldSprite[];

	PIptr = &GIptr->GI_Player;

	Dest.x = PIptr->PI_GlobalPos.x - (GIptr->GI_ForceFieldSize / 2.0f) + (PIptr->PI_GlobalPos.w / 2);
	Dest.y = PIptr->PI_GlobalPos.y - (GIptr->GI_ForceFieldSize / 2.0f) + (PIptr->PI_GlobalPos.h / 2);
	Dest.w = GIptr->GI_ForceFieldSize;
	Dest.h = GIptr->GI_ForceFieldSize;

	SDL_RenderTextureRotated(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, &ForceFieldSprite[0], &Dest, GIptr->GI_ForceFieldAngle, NULL, SDL_FLIP_NONE);
	GIptr->GI_ForceFieldAngle++;
	if(GIptr->GI_ForceFieldAngle >= 360) GIptr->GI_ForceFieldAngle = 0;

	return(TRUE);
}