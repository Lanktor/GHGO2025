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
