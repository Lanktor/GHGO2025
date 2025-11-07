#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT TIMER_Update(PGAME_INFO GIptr)
{
	GIptr->GI_EBICurSpawnCoolDown++;
	GIptr->GI_WAICurSpawnCoolDown++;
	GIptr->GI_SGICurSpawnCoolDown++;

	return(TRUE);
}

INT TIMER_CheckExpired(PGAME_INFO GIptr)
{
	if(GIptr->GI_EBICurSpawnCoolDown >= GIptr->GI_EBISpawnCoolDown)
	{
		GIptr->GI_EBICurSpawnCoolDown = 0.0f;
		printf("Enemy Basic Cool Down Goes off\n");
	}

	if (GIptr->GI_WAICurSpawnCoolDown >= GIptr->GI_WAISpawnCoolDown)
	{
		GIptr->GI_WAICurSpawnCoolDown = 0.0f;
		WAI_Spawn(GIptr);
	}

	if (GIptr->GI_SGICurSpawnCoolDown >= GIptr->GI_SGISpawnCoolDown)
	{
		GIptr->GI_SGICurSpawnCoolDown = 0.0f;
		SGI_CheckEnemiesInCone(GIptr, 45.0f, 200.0f);
	}

	return(TRUE);
}

INT TIMER_UpdateLevelTimer(PGAME_INFO GIptr)
{

	GIptr->GI_LevelCurCoolDown++;

	return(TRUE);

}

INT TIMER_RenderLevelTimer(PGAME_INFO GIptr)
{
	CHAR      Text[1024];
	INT       Minutes, Seconds;
	SDL_Color Color;
	SDL_FRect Dest;

	Minutes = GIptr->GI_LevelCurCoolDown / 60;
	Seconds = (INT)GIptr->GI_LevelCurCoolDown % 60;
	Color.r = 0;
	Color.g = 0;
	Color.b = 0;
	Color.a = 255;
	sprintf_s(Text, sizeof(Text), "WAVE: %02d MIN: %02d SEC: %02d", 0, Minutes, Seconds);

	Dest.x = 1400;
	Dest.y = 40;
	TEXT_WriteText(GIptr, Color, &Dest, Text, 1.0f);
	printf("%s\n", Text);
	return(TRUE);
}