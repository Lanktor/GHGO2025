#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT WAI_CheckForCollisions(PGAME_INFO GIptr, PWEAPON_AUTO_INFO WAIptr);


INT WAI_Initiate(PGAME_INFO GIptr)
{
	INT               I;
	PWEAPON_AUTO_INFO WAIptr;
	extern SDL_FRect  WeaponAutoSprites[];

	for(I = 0; I < MAX_WAI_OBJECTS; I++)
	{	
		WAIptr = (PWEAPON_AUTO_INFO)SDL_calloc(1, SZ_WEAPON_AUTO_INFO);
		GIptr->GI_WAITable[I] = WAIptr;

		WAIptr->WAI_ActiveFlag = OBJECT_IS_NOT_ACTIVE;
		WAIptr->WAI_FramesInTimer = 8;
		WAIptr->WAI_MaxSprites = 8;
		WAIptr->WAI_Scale = 1.0;
		WAIptr->WAI_Speed = WAI_SPEED;
		WAIptr->WAI_SpriteList = WeaponAutoSprites;

		WAIptr->WAI_GlobalPos.w = (WeaponAutoSprites->w * WAIptr->WAI_Scale);
		WAIptr->WAI_GlobalPos.h = (WeaponAutoSprites->h * WAIptr->WAI_Scale);
	}

	GIptr->GI_WAICurSpawnCoolDown = 0.0f;
	GIptr->GI_WAISpawnCoolDown = WAI_COOL_DOWN_FRAMES;
	return(TRUE);
}

INT WAI_Spawn(PGAME_INFO GIptr)
{
	INT               I;
	PPLAYER_INFO      PIptr;
	PWEAPON_AUTO_INFO WAIptr;

PIptr = &GIptr->GI_Player;

for (I = 0; I < MAX_WAI_OBJECTS; I++)
{
	WAIptr = GIptr->GI_WAITable[I];
	if (WAIptr->WAI_ActiveFlag == OBJECT_IS_NOT_ACTIVE)
	{
		WAIptr->WAI_ActiveFlag = OBJECT_IS_ACTIVE;
		WAIptr->WAI_CurSprite = 0;
		WAIptr->WAI_FrameTimer = 0;
		WAIptr->WAI_GlobalPos.x = PIptr->PI_GlobalPos.x;
		WAIptr->WAI_GlobalPos.y = PIptr->PI_GlobalPos.y;
		WAI_GetClosestEnemy(GIptr, WAIptr);
		printf("WAI_Spawn\n");
		break;
	}
}

return(TRUE);
}

INT WAI_GetClosestEnemy(PGAME_INFO GIptr, PWEAPON_AUTO_INFO WAIptr)
{
	INT               I;
	FLOAT             DX, DY, MaxDX, MaxDY, MaxDist, Dist;
	PENEMY_BASIC_INFO EBIptr;

	MaxDist = 3000;
	MaxDX = MaxDY = 0.0f;

	for (I = 0; I < GIptr->GI_EBITotalItems; I++)
	{
		EBIptr = GIptr->GI_EBITable[I];

		if (EBIptr->EBI_ActiveFlag == OBJECT_IS_ACTIVE)
		{
			DX = EBIptr->EBI_GlobalPos.x - (WAIptr->WAI_GlobalPos.x + WAIptr->WAI_GlobalPos.w / 2);
			DY = EBIptr->EBI_GlobalPos.y - (WAIptr->WAI_GlobalPos.y + WAIptr->WAI_GlobalPos.h / 2);
			Dist = sqrtf(DX * DX + DY * DY);

			if (Dist < MaxDist)
			{
				MaxDist = Dist;
				MaxDX = DX;
				MaxDY = DY;
			}
		}
	}

	if (MaxDist != 3000)
	{
		WAIptr->WAI_VX = (MaxDX / MaxDist) * WAIptr->WAI_Speed * GIptr->GI_DeltaTime;
		WAIptr->WAI_VY = (MaxDY / MaxDist) * WAIptr->WAI_Speed * GIptr->GI_DeltaTime;
	}

	return(TRUE);
}

INT WAI_Update(PGAME_INFO GIptr)
{
	return(TRUE);
}

INT WAI_Move(PGAME_INFO GIptr)
{
	INT               I;
	PWEAPON_AUTO_INFO WAIptr;

	for (I = 0; I < MAX_WAI_OBJECTS; I++)
	{
		WAIptr = GIptr->GI_WAITable[I];
		if (WAIptr->WAI_ActiveFlag == OBJECT_IS_ACTIVE)
		{
			WAIptr->WAI_GlobalPos.x += WAIptr->WAI_VX;
			WAIptr->WAI_GlobalPos.y += WAIptr->WAI_VY;
			WAI_CheckForCollisions(GIptr, WAIptr);
		}
	}

	return(TRUE);
}

INT WAI_CheckForCollisions(PGAME_INFO GIptr, PWEAPON_AUTO_INFO WAIptr)
{
	INT               I;
	PENEMY_BASIC_INFO EBIptr;

	for (I = 0; I < GIptr->GI_EBITotalItems; I++)
	{
		EBIptr = GIptr->GI_EBITable[I];

		if(EBIptr->EBI_ActiveFlag == OBJECT_IS_ACTIVE)
		{
			if ((SDL_HasRectIntersectionFloat(&EBIptr->EBI_GlobalPos, &WAIptr->WAI_GlobalPos)) == TRUE)
			{
				EBIptr->EBI_ActiveFlag = OBJECT_IS_NOT_ACTIVE;
				WAIptr->WAI_ActiveFlag = OBJECT_IS_NOT_ACTIVE;
				return(TRUE);
			}
		}
	}

	return(TRUE);
}

INT WAI_Render(PGAME_INFO GIptr)
{
	INT               I;
	PPLAYER_INFO      PIptr;
	PWEAPON_AUTO_INFO WAIptr;

	PIptr = &GIptr->GI_Player;

	for (I = 0; I < MAX_WAI_OBJECTS; I++)
	{
		WAIptr = GIptr->GI_WAITable[I];
		if (WAIptr->WAI_ActiveFlag == OBJECT_IS_ACTIVE)
		{
			SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, &WAIptr->WAI_SpriteList[WAIptr->WAI_CurSprite], &WAIptr->WAI_GlobalPos);
		}
	}
	return(TRUE);
}

