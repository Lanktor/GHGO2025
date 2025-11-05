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

	return(TRUE);
}