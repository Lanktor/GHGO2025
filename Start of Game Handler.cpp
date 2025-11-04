#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT StartOfGameHandler(PGAME_INFO GIptr)
{
	const  BOOL *KeyState;
	INT                Quit, Keys;
	INT                ButtonIdent;
	SDL_Event          Event;
	SDL_FRect          Srce, Dest;
	extern BUTTON_INFO StartGameButtons[];

	KeyState = SDL_GetKeyboardState(NULL);
	Mix_PlayMusic(GIptr->GI_BkgMusic, -1);
	Mix_VolumeMusic(80);

	GIptr->GI_TARGET_FPS = 80;
	GIptr->GI_FRAME_DELAY = 1000 / GIptr->GI_TARGET_FPS;

	GIptr->GI_SecondsCounter = GIptr->GI_PrevTime = SDL_GetTicks();
	GIptr->GI_FrameCounter = 0;

	KeyState = SDL_GetKeyboardState(NULL);


	Srce.x = Dest.x = 0;
	Srce.y = Dest.y = 0;
	Srce.w = Dest.w = GIptr->GI_ScreenWidth;
	Srce.h = Dest.h = GIptr->GI_ScreenHeight;

	for (Quit = FALSE; Quit != TRUE; GIptr->GI_FrameCounter++)
	{
		GIptr->GI_FrameStart = SDL_GetTicks();

		SDL_PumpEvents();

		while (SDL_PollEvent(&Event))
		{
			switch (Event.type)
			{

			case SDL_EVENT_KEY_DOWN:
				if (Event.key.scancode == SDL_SCANCODE_ESCAPE) Quit = TRUE;
				if (Event.key.scancode == SDL_SCANCODE_Q)
				{
				}
				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				if (Event.button.button == SDL_BUTTON_LEFT)
				{
					ButtonIdent = BUTTON_ProcessClick(GIptr, StartGameButtons);
					if (ButtonIdent == BUTTON_IDENT_EXIT) EndOfGameHandler(GIptr);
					if (ButtonIdent == BUTTON_IDENT_RULES)
					{
						BUTTON_ResetButtonState(GIptr, StartGameButtons, BUTTON_STATE_UP);
						RulesHandler(GIptr);
					}
					if (ButtonIdent == BUTTON_IDENT_PLAY) Quit = TRUE;
				}
				if (Event.button.button == SDL_BUTTON_RIGHT)
				{
				}
				break;

			case SDL_EVENT_MOUSE_BUTTON_UP:
				if (Event.button.button == SDL_BUTTON_LEFT)
				{
				}
				break;

			}
		}


		if (KeyState[SDL_SCANCODE_SPACE])
		{
		}

		GIptr->GI_MouseState = SDL_GetMouseState(&GIptr->GI_MouseX, &GIptr->GI_MouseY);

		GIptr->GI_CurTime = SDL_GetTicks();
		GIptr->GI_DeltaTime = (GIptr->GI_CurTime - GIptr->GI_PrevTime) / 1000.0f;
		GIptr->GI_PrevTime = GIptr->GI_CurTime;


		SDL_SetRenderDrawColor(GIptr->GI_MainRenderer, 0x00, 0x13, 0x63, 0x00);
		SDL_RenderClear(GIptr->GI_MainRenderer);

		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_StartOfGameTexture, &Srce, &Dest);
		BUTTON_Update(GIptr, StartGameButtons, 212, 424);
		BUTTON_IsButtonHover(GIptr, StartGameButtons);

		SDL_RenderPresent(GIptr->GI_MainRenderer);

		GIptr->GI_FrameTime = SDL_GetTicks() - GIptr->GI_FrameStart;

		if (GIptr->GI_FrameTime < GIptr->GI_FRAME_DELAY) SDL_Delay(GIptr->GI_FRAME_DELAY - GIptr->GI_FrameTime);

		if (SDL_GetTicks() >= GIptr->GI_SecondsCounter + 1000)
		{
			printf("FPS: [%d]\n", GIptr->GI_FrameCounter);
			GIptr->GI_FrameCounter = 0;
			GIptr->GI_SecondsCounter = SDL_GetTicks();
		}
	}
	return(TRUE);
}