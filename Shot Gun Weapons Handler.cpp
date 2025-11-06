#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

bool IsEnemyInCone(const SDL_FRect *enemy, float originX, float originY, float dirX, float dirY, float coneAngleDeg, float coneDistance);


void SGI_CheckEnemiesInCone(PGAME_INFO GIptr,  float coneAngleDeg, float coneDistance)
{
  INT               I;
  FLOAT             EndPointX, EndPointY;
  PENEMY_BASIC_INFO EBIptr;
  PPLAYER_INFO      PIptr;

  PIptr = &GIptr->GI_Player;

  // Normalize the base direction
  float baseLen = sqrtf(GIptr->GI_SaveDirX * GIptr->GI_SaveDirX + GIptr->GI_SaveDirY * GIptr->GI_SaveDirY);
  if (baseLen < 0.0001f)
  {
    GIptr->GI_SaveDirX = 0.0f;
    GIptr->GI_SaveDirY = -1.0f;
    baseLen = 1.0f;
  }
  GIptr->GI_SaveDirX /= baseLen;
  GIptr->GI_SaveDirY /= baseLen;

  // Precompute boundary vectors for visualization
  float halfAngle = coneAngleDeg * 0.5f * DEG2RAD;
  float cosA = cosf(halfAngle);
  float sinA = sinf(halfAngle);

  // Rotate direction vector by ±halfAngle to get cone edges
  float leftX = GIptr->GI_SaveDirX * cosA - GIptr->GI_SaveDirY * sinA;
  float leftY = GIptr->GI_SaveDirX * sinA + GIptr->GI_SaveDirY * cosA;
  float rightX = GIptr->GI_SaveDirX * cosA + GIptr->GI_SaveDirY * sinA;
  float rightY = -GIptr->GI_SaveDirX * sinA + GIptr->GI_SaveDirY * cosA;

  // Endpoints of the cone edges
  float leftEndX = PIptr->PI_GlobalPos.x + leftX * coneDistance;
  float leftEndY = PIptr->PI_GlobalPos.y + leftY * coneDistance;
  float rightEndX = PIptr->PI_GlobalPos.x + rightX * coneDistance;
  float rightEndY = PIptr->PI_GlobalPos.y + rightY * coneDistance;

  // ---------- Debug Draw (visualize cone) ----------
  SDL_SetRenderDrawColor(GIptr->GI_MainRenderer, 0, 255, 0, 255); // Green for cone
//  SDL_RenderLine(GIptr->GI_MainRenderer, PIptr->PI_GlobalPos.x, PIptr->PI_GlobalPos.y, leftEndX, leftEndY);
//  SDL_RenderLine(GIptr->GI_MainRenderer, PIptr->PI_GlobalPos.x, PIptr->PI_GlobalPos.y, rightEndX, rightEndY);

  // Optional: draw a faint line down the center
  SDL_SetRenderDrawColor(GIptr->GI_MainRenderer, 0, 200, 200, 100);
  EndPointX = PIptr->PI_GlobalPos.x + GIptr->GI_SaveDirX + coneDistance;
  EndPointY = PIptr->PI_GlobalPos.y + GIptr->GI_SaveDirY + coneDistance;

//  SDL_RenderLine(GIptr->GI_MainRenderer, PIptr->PI_GlobalPos.x, PIptr->PI_GlobalPos.y, EndPointX, EndPointY);
  // -----------------------------------------------

  // Enemy detection

  for (I = 0; I < GIptr->GI_EBITotalItems; I++)
  {
    EBIptr = GIptr->GI_EBITable[I];
    if(EBIptr->EBI_ActiveFlag == OBJECT_IS_NOT_ACTIVE) continue;

    bool hit = IsEnemyInCone(&EBIptr->EBI_GlobalPos, PIptr->PI_GlobalPos.x, PIptr->PI_GlobalPos.y, GIptr->GI_SaveDirX, GIptr->GI_SaveDirY, coneAngleDeg,coneDistance);

    if (hit)
    {
      SDL_SetRenderDrawColor(GIptr->GI_MainRenderer, 255, 255, 255, 255); // White box if in cone
      EBIptr->EBI_ActiveFlag = OBJECT_IS_NOT_ACTIVE;
    }
    else
    {
      SDL_SetRenderDrawColor(GIptr->GI_MainRenderer, 0, 0, 0, 255); // Black otherwise
    }

    SDL_RenderRect(GIptr->GI_MainRenderer, &EBIptr->EBI_GlobalPos);
  }
}

bool IsEnemyInCone(const SDL_FRect *enemy, float originX, float originY, float dirX, float dirY, float coneAngleDeg, float coneDistance)
{
  float ex = enemy->x + enemy->w * 0.5f;
  float ey = enemy->y + enemy->h * 0.5f;

  float vx = ex - originX;
  float vy = ey - originY;
  float dist = sqrtf(vx * vx + vy * vy);
  if (dist > coneDistance)
    return false;

  if (dist > 0.0001f)
  {
    vx /= dist;
    vy /= dist;
  }

  float dot = (vx * dirX) + (vy * dirY);
  float cosThreshold = cosf((coneAngleDeg * 0.5f) * DEG2RAD);

  return dot >= cosThreshold;
}
