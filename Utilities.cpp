#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

FLOAT UTIL_RandomFloatRange(FLOAT Min, FLOAT Max)
{
  FLOAT Random = SDL_randf();

  Random = SDL_randf();
  return Min + Random * (Max - Min);
}

INT UTIL_RandomIntRange(PUINT State, INT Min, INT Max)
{
  UINT x = *State;

  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;

  *State = x;

  INT Result = (x % (Max - Min + 1)) + Min;
  return Result;

}

FLOAT UTIL_RadiansToDegrees(FLOAT Radians)
{
  return Radians * (180.0f / M_PI);
}

FLOAT UTIL_DegreesToRadians(FLOAT Degrees)
{
  return Degrees * (M_PI / 180.0);
}

INT UTIL_DrawCollisionBox(PGAME_INFO GIptr, PSDL_FRect SrceBox, SDL_Color Color, INT BorderSize)
{
  INT I;
  SDL_FRect DestBox;

  memcpy(&DestBox, SrceBox, SZ_SDL_FRECT);
  SDL_SetRenderDrawColor(GIptr->GI_MainRenderer, Color.r, Color.g, Color.b, Color.a);

  for (I = 0; I < BorderSize; I++)
  {
    SDL_RenderRect(GIptr->GI_MainRenderer, &DestBox);
    DestBox.x -= 1;
    DestBox.y -= 1;
    DestBox.w += 2;
    DestBox.h += 2;
  }

  return(TRUE);
}

INT UTIL_CheckInsideCircle(PGAME_INFO GIptr, PSDL_FRect Objptr, FLOAT CX, FLOAT CY, FLOAT Rad)
{
  FLOAT EX, EY, EnemyRadius;
  FLOAT DX, DY, Dist;
  FLOAT TotalRadius;

  EX = Objptr->x + (Objptr->w * .5f);
  EY = Objptr->y + (Objptr->h * .5f);

  EnemyRadius = (Objptr->w + Objptr->h) * .25f;

  DX = (EX - CX - 16);
  DY = (EY - CY - 16);

  Dist = DX * DX + DY * DY;

  TotalRadius = Rad + EnemyRadius;

  return(Dist <= (TotalRadius * TotalRadius));

}

