#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT BUTTON_Update(PGAME_INFO GIptr, PBUTTON_INFO BIptr, INT DownOffset, INT HoverOffset)
{
	INT       FontId;
	SDL_FRect Srce, Dest;
	SDL_Color Color_TEXT = { 51, 27, 26 };

	for (; BIptr->BI_Ident != -1; BIptr++)
	{
		Srce.w = BIptr->BI_Srce.w;
		Srce.h = BIptr->BI_Srce.h;
		Srce.y = BIptr->BI_Srce.y;

		switch (BIptr->BI_State)
		{
		case BUTTON_STATE_UP:
			Srce.x = BIptr->BI_Srce.x;
			FontId = FONT_MEDIUM_BLACK;
			break;

		case BUTTON_STATE_DOWN:
			Srce.x = DownOffset;
			FontId = FONT_MEDIUM_WHITE;
			break;

		case BUTTON_STATE_HOVER:
			Srce.x = HoverOffset;
			FontId = FONT_MEDIUM_BLACK;
			break;

		default:
			break;
		}
		//printf("Button Text [%s]\n", BIptr->BI_Text);
		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_MainTexture, &Srce, &BIptr->BI_Dest);

		Dest.x = BIptr->BI_Dest.x + BIptr->BI_TextXOffset;
		Dest.y = BIptr->BI_Dest.y + BIptr->BI_TextYOffset;

		TEXT_WriteText(GIptr, Color_TEXT, &Dest, BIptr->BI_Text, 1);
	}
	return(TRUE);
}

INT BUTTON_IsButtonHover(PGAME_INFO GIptr, PBUTTON_INFO BIptr)
{
	INT      I;
	SDL_FRect MouseRect;

	MouseRect.x = GIptr->GI_MouseX;
	MouseRect.y = GIptr->GI_MouseY;
	MouseRect.w = 1;
	MouseRect.h = 1;
	for (; BIptr->BI_Ident != -1; BIptr++)
	{
		if (BIptr->BI_State != BUTTON_STATE_DOWN)
		{
			BIptr->BI_State = BUTTON_STATE_UP;
			if ((SDL_HasRectIntersectionFloat(&MouseRect, &BIptr->BI_Dest)) == TRUE)
			{
				BIptr->BI_State = BUTTON_STATE_HOVER;
			}
		}
	}

	return(TRUE);
}

INT BUTTON_ProcessClick(PGAME_INFO GIptr, PBUTTON_INFO BIptr)
{
	INT       I, Ident;
	SDL_FRect MouseRect;

	MouseRect.x = GIptr->GI_MouseX;
	MouseRect.y = GIptr->GI_MouseY;
	MouseRect.w = MouseRect.h = 1;

	Ident = BUTTON_IDENT_NONE;
	for (; BIptr->BI_Ident != -1; BIptr++)
	{
		if ((SDL_HasRectIntersectionFloat(&MouseRect, &BIptr->BI_Dest)) == TRUE)
		{
			BIptr->BI_State = BUTTON_STATE_DOWN;

			switch (BIptr->BI_Ident)
			{
			case BUTTON_IDENT_PLAY:
				Ident = BUTTON_IDENT_PLAY;
				break;

			case BUTTON_IDENT_RULES:
				Ident = BUTTON_IDENT_RULES;
				break;

			case BUTTON_IDENT_SKIP:
				Ident = BUTTON_IDENT_SKIP;
				break;

			case BUTTON_IDENT_HELP:
				break;

			case BUTTON_IDENT_CONTINUE:
				Ident = BUTTON_IDENT_CONTINUE;
				break;

			case BUTTON_IDENT_ROLL:
				break;

			case BUTTON_IDENT_HINT:
				Ident = BUTTON_IDENT_HINT;
				break;

			case BUTTON_IDENT_EXIT:
				Ident = BUTTON_IDENT_EXIT;
				break;

			case BUTTON_IDENT_HISCORE:
				Ident = BUTTON_IDENT_HISCORE;
				break;

			case BUTTON_IDENT_REPLAY:
				Ident = BUTTON_IDENT_REPLAY;
				break;

			case BUTTON_IDENT_NEXT:
				Ident = BUTTON_IDENT_NEXT;
				break;

			default:
				break;
			}
		}
	}

	return(Ident);
}

INT BUTTON_ResetButtonState(PGAME_INFO GIptr, PBUTTON_INFO BIptr, INT ButtonState)
{
	for (; BIptr->BI_Ident != -1; BIptr++) BIptr->BI_State = ButtonState;

	return(TRUE);
}
