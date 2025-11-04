#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT RULESHANDLER_DisplayData(PGAME_INFO GIptr);

INT RulesHandler(PGAME_INFO GIptr)
{
	const  BOOL *KeyState;
	INT                Quit, Keys;
	INT                ButtonIdent;
	SDL_Event          Event;
	SDL_FRect          Srce, Dest;
	extern BUTTON_INFO RulesButtons[];

	GIptr->GI_TARGET_FPS = 80;
	GIptr->GI_FRAME_DELAY = 1000 / GIptr->GI_TARGET_FPS;

	GIptr->GI_SecondsCounter = GIptr->GI_PrevTime = SDL_GetTicks();
	GIptr->GI_FrameCounter = 0;

	KeyState = SDL_GetKeyboardState(NULL);


	Srce.x = Dest.x = 0;
	Srce.y = Dest.y = 0;
	Srce.w = Dest.w = GIptr->GI_ScreenWidth;
	Srce.h = Dest.h = GIptr->GI_ScreenHeight;

	BUTTON_ResetButtonState(GIptr, RulesButtons, BUTTON_STATE_UP);

	for (Quit = FALSE; Quit != TRUE; GIptr->GI_FrameCounter++)
	{
		GIptr->GI_FrameStart = SDL_GetTicks();

		SDL_PumpEvents();

		while (SDL_PollEvent(&Event))
		{
			switch (Event.type)
			{
			case SDL_EVENT_QUIT:
				Quit = TRUE;
				break;

			case SDL_EVENT_KEY_DOWN:
				if (Event.key.scancode == SDL_SCANCODE_ESCAPE) Quit = TRUE;
				if (Event.key.scancode == SDL_SCANCODE_Q)
				{
				}
				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				if (Event.button.button == SDL_BUTTON_LEFT)
				{
					ButtonIdent = BUTTON_ProcessClick(GIptr, RulesButtons);
					if (ButtonIdent == BUTTON_IDENT_CONTINUE)
					{
						Quit = TRUE;
					}

					if (ButtonIdent == BUTTON_IDENT_EXIT)
					{
						EndOfGameHandler(GIptr);
					}
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

		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_RulesTexture, &Srce, &Dest);
		BUTTON_Update(GIptr, RulesButtons, 212, 424);
		BUTTON_IsButtonHover(GIptr, RulesButtons);
		RULESHANDLER_DisplayData(GIptr);

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

INT RULESHANDLER_DisplayData(PGAME_INFO GIptr)
{
	CHAR      Text[1024];
	SDL_FRect Dest;
	SDL_Color TopTextColor = { 216, 207, 169 };
	SDL_Color BlackTextColor = { 0,   0,   0 };

	Dest.y = 60;
	sprintf_s(Text, sizeof(Text), "RULES", GIptr->GI_CurrentLevel);
	Dest.x = TEXT_CalculateCenterText(GIptr, Text, 4);

	TEXT_WriteTextRaised(GIptr, TopTextColor, BlackTextColor, &Dest, Text, 4, 4);

	return(TRUE);
}