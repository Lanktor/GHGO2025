#include <stdio.h>
#include <SDL3/SDL.h>
#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>

INT TEXT_WriteText(PGAME_INFO GIptr, SDL_Color Color, PSDL_FRect Dest, const char *Text, INT Scale)
{
	INT              I, Len, Value;
	PSDL_FRect       TIptr, AlphaFont, NumericFont;
	SDL_FRect        SaveDest;
	extern SDL_FRect FontAlphaWhite[];
	extern SDL_FRect FontNumericWhite[];

	Len = strlen(Text);
	memcpy(&SaveDest, Dest, sizeof(SDL_Rect));

	AlphaFont = FontAlphaWhite;
	NumericFont = FontNumericWhite;


	TIptr = NULL;
	for (I = 0; I < Len; I++)
	{
		Value = (INT)Text[I];
		if (Value == 32)
		{
			Dest->x += 8 * Scale;
			continue;
		}

		if ((Value >= 48) && (Value <= 57))
		{
			Value -= 48;
			TIptr = &NumericFont[Value];
		}
		else if ((Value >= 65) && (Value <= 90))
		{
			Value -= 65;
			TIptr = &AlphaFont[Value];
		}
		else
		{
			if (Value == 45) //Minus Sign
			{
				TIptr = &NumericFont[10];
			}

			if (Value == 58) // Full Colon
			{
				TIptr = &NumericFont[11];
			}
		}

		if (TIptr == NULL)
		{
			Dest->x += 20;
			continue;
		}

		Dest->w = TIptr->w * Scale;
		Dest->h = TIptr->h * Scale;
		SDL_SetTextureColorMod(GIptr->GI_TextTexture, Color.r, Color.g, Color.b);
		SDL_RenderTexture(GIptr->GI_MainRenderer, GIptr->GI_TextTexture, TIptr, Dest);
		Dest->x += TIptr->w * Scale + 2;
	}

	memcpy(Dest, &SaveDest, sizeof(SDL_Rect));

	return(TRUE);
}

INT TEXT_WriteTextRaised(PGAME_INFO GIptr, SDL_Color TopColor, SDL_Color BotColor, PSDL_FRect Dest, const char *Text, INT Scale, INT Offset)
{
	TEXT_WriteText(GIptr, BotColor, Dest, Text, Scale);
	Dest->x -= Offset;
	Dest->y -= Offset;
	TEXT_WriteText(GIptr, TopColor, Dest, Text, Scale);
	Dest->x += Offset;
	Dest->y += Offset;
	return(TRUE);
}

INT TEXT_RenderScore(PGAME_INFO GIptr)
{
	CHAR      Text[1024];
	SDL_FRect Dest;
	FLOAT     HitRatioCalc;
	INT       HitRatioDisplay;
	SDL_Color Color = { 0, 0, 0 };
	SDL_Color Color_RED = { 255, 0, 0 };
	extern SDL_FRect FontAlphaRed[];
	extern SDL_FRect FontNumericRed[];

	return(TRUE);
}

INT TEXT_CalculateCenterText(PGAME_INFO GIptr, const char *Text, INT Scale)
{
	INT              I, Len, Value, Width, XOffset;
	PSDL_FRect       TIptr, AlphaFont, NumericFont;
	extern SDL_FRect FontAlphaWhite[];
	extern SDL_FRect FontNumericWhite[];


	AlphaFont = FontAlphaWhite;
	NumericFont = FontNumericWhite;

	TIptr = NULL;
	Len = strlen(Text);

	for (Width = 0, I = 0; I < Len; I++)
	{
		Value = (INT)Text[I];
		if (Value == 32)
		{
			Width += 8 * Scale;
			continue;
		}

		if ((Value >= 48) && (Value <= 57))
		{
			Value -= 48;
			TIptr = &NumericFont[Value];
		}
		else if ((Value >= 65) && (Value <= 90))
		{
			Value -= 65;
			TIptr = &AlphaFont[Value];
		}
		else
		{
			if (Value == 40)
			{
				TIptr = &AlphaFont[26];
			}
			if (Value == 41)
			{
				TIptr = &AlphaFont[27];

			}
			if (Value == 43)
			{
				TIptr = &AlphaFont[28];

			}
			if (Value == 33)
			{
				TIptr = &AlphaFont[29];

			}

			if (Value == 45) //Minus Sign
			{
				TIptr = &NumericFont[10];
			}

			if (Value == 58) // Full Colon
			{
				TIptr = &NumericFont[11];
			}
		}

		if (TIptr == NULL)
		{
			Width += 20 * Scale;
			continue;
		}

		Width += (TIptr->w * Scale) + 2;
	}

	XOffset = (GIptr->GI_ScreenWidth - Width) / 2;
	return(XOffset);
}