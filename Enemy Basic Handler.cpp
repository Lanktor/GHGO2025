#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

void ApplyForceFieldPush(PGAME_INFO GIptr, PLAYER_INFO *PIptr, ENEMY_BASIC_INFO *EBIptr);
void ResolveEnemyOverlaps(PGAME_INFO GIptr);


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
	PPLAYER_INFO      PIptr;
	PENEMY_BASIC_INFO EBIptr;
	SDL_Color         Color;

	PIptr = &GIptr->GI_Player;
	Color.r = UTIL_RandomIntRange(&GIptr->GI_RNGState, 0, 255);
	Color.g = UTIL_RandomIntRange(&GIptr->GI_RNGState, 0, 255);
	Color.b = UTIL_RandomIntRange(&GIptr->GI_RNGState, 0, 255);
	Color.a = 255;

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

	ResolveEnemyOverlaps(GIptr);
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

//		if((UTIL_CheckInsideCircle(GIptr, &EBIptr->EBI_GlobalPos, PIptr->PI_GlobalPos.x, PIptr->PI_GlobalPos.y, GIptr->GI_ForceFieldSize / 2.0f)) == true)
//		{
//			ApplyForceFieldPush(GIptr, PIptr, EBIptr);
//		}
	}

	return(TRUE);
}

void ResolveEnemyOverlaps(PGAME_INFO GIptr)
{
	for (int i = 0; i < GIptr->GI_EBITotalItems; ++i)
	{
		if(GIptr->GI_EBITable[i]->EBI_ActiveFlag == OBJECT_IS_NOT_ACTIVE) continue;

		for (int j = i + 1; j < GIptr->GI_EBITotalItems; ++j)
		{
			if (GIptr->GI_EBITable[j]->EBI_ActiveFlag == OBJECT_IS_NOT_ACTIVE) continue;

			float ex1 = GIptr->GI_EBITable[i]->EBI_GlobalPos.x + GIptr->GI_EBITable[i]->EBI_GlobalPos.w * 0.5f;
			float ey1 = GIptr->GI_EBITable[i]->EBI_GlobalPos.y + GIptr->GI_EBITable[i]->EBI_GlobalPos.h * 0.5f;

			float ex2 = GIptr->GI_EBITable[j]->EBI_GlobalPos.x + GIptr->GI_EBITable[j]->EBI_GlobalPos.w * 0.5f;
			float ey2 = GIptr->GI_EBITable[j]->EBI_GlobalPos.y + GIptr->GI_EBITable[j]->EBI_GlobalPos.h * 0.5f;

			float dx = ex2 - ex1;
			float dy = ey2 - ey1;
			float dist2 = dx * dx + dy * dy;

			// Rough "collision radius" for each enemy
			float radius1 = (GIptr->GI_EBITable[i]->EBI_GlobalPos.w + GIptr->GI_EBITable[i]->EBI_GlobalPos.h) * 0.25f;
			float radius2 = (GIptr->GI_EBITable[j]->EBI_GlobalPos.w + GIptr->GI_EBITable[j]->EBI_GlobalPos.h) * 0.25f;
			float minDist = radius1 + radius2;

			if (dist2 < minDist * minDist && dist2 > 0.0001f)
			{
				float dist = sqrtf(dist2);
				float overlap = (minDist - dist);

				// Normalize
				float nx = dx / dist;
				float ny = dy / dist;

				// Push each enemy apart by half the overlap
				float push = overlap * 0.5f;

				GIptr->GI_EBITable[i]->EBI_GlobalPos.x -= nx * push;
				GIptr->GI_EBITable[i]->EBI_GlobalPos.y -= ny * push;

				GIptr->GI_EBITable[j]->EBI_GlobalPos.x += nx * push;
				GIptr->GI_EBITable[j]->EBI_GlobalPos.y += ny * push;
			}
		}
	}
}


void ApplyForceFieldPush(PGAME_INFO GIptr, PLAYER_INFO *PIptr, PENEMY_BASIC_INFO EBIptr)
{
	float px = PIptr->PI_GlobalPos.x + PIptr->PI_GlobalPos.w * 0.5f;
	float py = PIptr->PI_GlobalPos.y + PIptr->PI_GlobalPos.h * 0.5f;

	float ex = EBIptr->EBI_GlobalPos.x + EBIptr->EBI_GlobalPos.w * 0.5f;
	float ey = EBIptr->EBI_GlobalPos.y + EBIptr->EBI_GlobalPos.h * 0.5f;

	float dx = ex - px;
	float dy = ey - py;
	float dist = sqrtf(dx * dx + dy * dy);
	float radius = GIptr->GI_ForceFieldSize * 0.5f;

	// Skip if outside field
	if (dist >= radius || dist < 0.0001f)
		return;

	// Normalize
	dx /= dist;
	dy /= dist;

	// Depth = how far inside the field the enemy is
	float penetration = radius - dist;

	// Base push force proportional to depth
//	float basePush = penetration * 4.0f * GIptr->GI_DeltaTime;  // tweak multiplier
	float basePush = (penetration + 200.0f) * 4.0f * GIptr->GI_DeltaTime;
	// Add dynamic impulse based on player’s movement direction (bonus push)
	float moveDirX = GIptr->GI_SaveDirX;
	float moveDirY = GIptr->GI_SaveDirY;

	float directionalBoost = (dx * moveDirX + dy * moveDirY); // dot product
	if (directionalBoost < 0) directionalBoost = 0; // only push forward

	float totalPush = basePush + directionalBoost * 50.0f * GIptr->GI_DeltaTime;

	// Move enemy outwards
	EBIptr->EBI_GlobalPos.x += dx * totalPush;
	EBIptr->EBI_GlobalPos.y += dy * totalPush;
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
		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, &EBIptr->EBI_SpriteList[EBIptr->EBI_CurSprite], &EBIptr->EBI_GlobalPos);
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
