#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT TerminateApplication(PGAME_INFO GIptr)
{
  printf("Terminate Application\n");
  Mix_CloseAudio();
  SDL_DestroyRenderer(GIptr->GI_MainRenderer);
  SDL_DestroyWindow(GIptr->GI_MainWindow);
  SDL_Quit();

  return(TRUE);
}