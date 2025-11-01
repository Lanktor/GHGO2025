#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL_mixer.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT InitializeApplication(PGAME_INFO GIptr)
{
	INT                    I;
	const SDL_DisplayMode *Disp;

	SDL_srand(time(NULL));
	memset(GIptr, 0, SZ_GAME_INFO);

	Disp = SDL_GetDesktopDisplayMode(0);
	GIptr->GI_GameVersion = GAME_VERSION;
	GIptr->GI_MouseDownFlag = FALSE;
	GIptr->GI_MouseUpFlag = TRUE;
	GIptr->GI_RNGState = SDL_rand_bits();
	GIptr->GI_CurrentLevel = LEVEL_ONE;
	GIptr->GI_ShowPathFlag = FALSE;

	sprintf_s(GIptr->GI_PlayerName, MAX_NAME_LENGTH, "%s", "GUEST");

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return FALSE;
	}

	Disp = SDL_GetCurrentDisplayMode(1);
	GIptr->GI_ScreenHeight = Disp->h;
	GIptr->GI_ScreenWidth = Disp->w;

	GIptr->GI_ScreenWidth = 1920;
	GIptr->GI_ScreenHeight = 1080;

	printf("Height = %d Width %d\n", GIptr->GI_ScreenHeight, GIptr->GI_ScreenWidth);
	GIptr->GI_Active = GAME_IS_INACTIVE;
	GIptr->GI_CurrentScore = 0;

	if (!SDL_CreateWindowAndRenderer(NULL, Disp->w, Disp->h, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS, &GIptr->GI_MainWindow, &GIptr->GI_MainRenderer))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Test Error", NULL);
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return FALSE;
	}

	if ((GIptr->GI_MainTexture = TEXTURE_Load(GIptr, MAIN_TEXTURE)) == NULL)
	{
		SDL_Log("Couldn't create/load texture: %s", SDL_GetError());
		return FALSE;
	}
	if ((GIptr->GI_BackgroundTexture = TEXTURE_Load(GIptr, BACKGROUND_TEXTURE)) == NULL)
	{
		SDL_Log("Couldn't create.load texture: %s", SDL_GetError());
		return FALSE;
	}

	if ((GIptr->GI_EndOfGameTexture = TEXTURE_Load(GIptr, ENDSCREEN_TEXTURE)) == NULL)
	{
		SDL_Log("Couldn't create.load texture: %s", SDL_GetError());
		return FALSE;
	}
	if ((GIptr->GI_StartOfGameTexture = TEXTURE_Load(GIptr, STARTSCREEN_TEXTURE)) == NULL)
	{
		SDL_Log("Couldn't create.load texture: %s", SDL_GetError());
		return FALSE;
	}
	if ((GIptr->GI_RulesTexture = TEXTURE_Load(GIptr, RULESSCREEN_TEXTURE)) == NULL)
	{
		SDL_Log("Couldn't create.load texture: %s", SDL_GetError());
		return FALSE;
	}

	if ((GIptr->GI_TextTexture = TEXTURE_Load(GIptr, TEXT_TEXTURE)) == NULL)
	{
		SDL_Log("Couldn't create.load texture: %s", SDL_GetError());
		return FALSE;
	}

	if ((GIptr->GI_PlayerTexture = TEXTURE_Load(GIptr, PLAYER_TEXTURE)) == NULL)
	{
		SDL_Log("Couldn't create.load texture: [%s] -- ERROR: [%s]", PLAYER_TEXTURE, SDL_GetError());
		return FALSE;
	}

	if ((Mix_OpenAudio(0, NULL)) == FALSE)
	{
		printf("***** SDL Mixer FAILED *****\nSDL could not initialize SDL Mixer! SDL Error: %s", SDL_GetError());
		return FALSE;
	}

	if ((GIptr->GI_BkgMusic = Mix_LoadMUS(BACKGROUND_MUSIC)) == NULL)
	{
		printf("***** Music Load FAILED *****\nSDL could not Load Music! SDL Error: %s", SDL_GetError());
		return(FALSE);
	}

	return(TRUE);
}