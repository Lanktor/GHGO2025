#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT CheckForLevelCompletion(PGAME_INFO GIptr);


INT GameLoop(PGAME_INFO GIptr)
{
	const  BOOL *KeyState;
	CHAR         Text[1024];
	INT          Quit, Keys, TestCounter, RetVal;
	INT          I, ButtonIdent;
	SDL_Event    Event;
	SDL_FRect    Srce, Dest;

	GIptr->GI_TARGET_FPS = 80;
	GIptr->GI_FRAME_DELAY = 1000 / GIptr->GI_TARGET_FPS;

	GIptr->GI_SecondsCounter = GIptr->GI_PrevTime = SDL_GetTicks();
	GIptr->GI_FrameCounter = 0;


	KeyState = SDL_GetKeyboardState(NULL);
	TestCounter = 0;

	Dest.x = 100;
	Dest.y = 100;
	for (Quit = FALSE; Quit != TRUE; GIptr->GI_FrameCounter++)
	{
		GIptr->GI_FrameStart = SDL_GetTicks();

		SDL_PumpEvents();

		while (SDL_PollEvent(&Event))
		{
			switch (Event.type)
			{
			case SDL_EVENT_KEY_DOWN:
				if (Event.key.scancode == SDL_SCANCODE_ESCAPE)
				{
					RulesHandler(GIptr);
				}
				if (Event.key.scancode == SDL_SCANCODE_Q)
				{
				}
				if ((Event.key.scancode == SDL_SCANCODE_A) || (Event.key.scancode == SDL_SCANCODE_LEFT))
				{
				}
				if ((Event.key.scancode == SDL_SCANCODE_D) || (Event.key.scancode == SDL_SCANCODE_RIGHT))
				{
				}
				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				if (Event.button.button == SDL_BUTTON_LEFT)
				{
					GIptr->GI_MouseDownFlag = TRUE;
				}
				if (Event.button.button == SDL_BUTTON_RIGHT)
				{
				}
				break;

			case SDL_EVENT_MOUSE_BUTTON_UP:
				if (Event.button.button == SDL_BUTTON_LEFT)
				{
					GIptr->GI_MouseDownFlag = FALSE;
				}
				break;

			}
		}

		if (KeyState[SDL_SCANCODE_A] || KeyState[SDL_SCANCODE_LEFT])
		{
		}
		if (KeyState[SDL_SCANCODE_D] || KeyState[SDL_SCANCODE_RIGHT])
		{
		}
		if (KeyState[SDL_SCANCODE_W] || KeyState[SDL_SCANCODE_UP])
		{
		}
		else
		{
		}

		if (GIptr->GI_MouseDownFlag == TRUE)
		{
			PLAYER_Move(GIptr);
		}
		GIptr->GI_MouseState = SDL_GetMouseState(&GIptr->GI_MouseX, &GIptr->GI_MouseY);

		GIptr->GI_CurTime = SDL_GetTicks();
		GIptr->GI_DeltaTime = (GIptr->GI_CurTime - GIptr->GI_PrevTime) / 1000.0f;
		GIptr->GI_PrevTime = GIptr->GI_CurTime;

		TIMER_Update(GIptr);
		TIMER_CheckExpired(GIptr);

		PLAYER_Update(GIptr);
		EBI_Update(GIptr);

		WAI_Move(GIptr);

		SDL_SetRenderDrawColor(GIptr->GI_MainRenderer, 0x80, 0x80, 0x80, 0x00);
		SDL_RenderClear(GIptr->GI_MainRenderer);

		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_BackgroundTexture, NULL, NULL);
		PLAYER_Render(GIptr);
		EBI_Render(GIptr);
		WAI_Render(GIptr);
//		FF_Render(GIptr);
		TIMER_RenderLevelTimer(GIptr);

		SDL_RenderPresent(GIptr->GI_MainRenderer);

		GIptr->GI_FrameTime = SDL_GetTicks() - GIptr->GI_FrameStart;

		if (GIptr->GI_FrameTime < GIptr->GI_FRAME_DELAY) SDL_Delay(GIptr->GI_FRAME_DELAY - GIptr->GI_FrameTime);

		if (SDL_GetTicks() >= GIptr->GI_SecondsCounter + 1000)
		{
printf("FPS: [%d] Delay = [%d]\n", GIptr->GI_FrameCounter, GIptr->GI_FRAME_DELAY - GIptr->GI_FrameTime);
			GIptr->GI_FrameCounter = 0;
			GIptr->GI_SecondsCounter = SDL_GetTicks();
			TIMER_UpdateLevelTimer(GIptr);
		}
	}

	EndOfGameHandler(GIptr);
	return(TRUE);
}
