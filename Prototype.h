#pragma once

INT EndOfGameHandler(PGAME_INFO GIptr);
INT GameLoop(PGAME_INFO GIptr);
INT InitializeApplication(PGAME_INFO GIptr);
INT RulesHandler(PGAME_INFO GIptr);
INT StartOfGameHandler(PGAME_INFO GIptr);
INT TerminateApplication(PGAME_INFO GIptr);


PSDL_Texture TEXTURE_Load(PGAME_INFO GIptr, PCCHAR FName);

INT TEXT_CalculateCenterText(PGAME_INFO GIptr, const char *Text, INT Scale);
INT TEXT_RenderScore(PGAME_INFO GIptr);
INT TEXT_WriteText(PGAME_INFO GIptr, SDL_Color Color, PSDL_FRect Dest, const char *Text, INT Scale);
INT TEXT_WriteTextRaised(PGAME_INFO GIptr, SDL_Color TopColor, SDL_Color BotColor, PSDL_FRect Dest, const char *Text, INT Scale, INT Offset);

INT BUTTON_IsButtonHover(PGAME_INFO GIptr, PBUTTON_INFO BIptr);
INT BUTTON_ProcessClick(PGAME_INFO GIptr, PBUTTON_INFO BIptr);
INT BUTTON_ResetButtonState(PGAME_INFO GIptr, PBUTTON_INFO BIptr, INT ButtonState);
INT BUTTON_Update(PGAME_INFO GIptr, PBUTTON_INFO BIptr, INT DownOffset, INT HoverOffset);
