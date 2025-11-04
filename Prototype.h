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

INT PLAYER_Initiate(PGAME_INFO GIptr);
INT PLAYER_Move(PGAME_INFO GIptr);
INT PLAYER_Render(PGAME_INFO GIptr);
INT PLAYER_Update(PGAME_INFO GIptr);

INT OBJ_BuildWAVEOne(PGAME_INFO GIptr);
INT OBJ_Clear(PGAME_INFO GIptr);
INT OBJ_Initiate(PGAME_INFO GIptr);
INT OBJ_Move(PGAME_INFO GIptr, POBJ_INFO OIptr);
INT OBJ_Update(PGAME_INFO GIptr);
INT OBJ_Render(PGAME_INFO GIptr);

FLOAT UTIL_DegreesToRadians(FLOAT Degrees);
INT   UTIL_DrawCollisionBox(PGAME_INFO GIptr, PSDL_FRect SrceBox, SDL_Color Color, INT BorderSize);
FLOAT UTIL_RandomFloatRange(FLOAT Min, FLOAT Max);
INT   UTIL_RandomIntRange(PUINT State, INT Min, INT Max);
FLOAT UTIL_RadiansToDegrees(FLOAT Radians);

INT TEST_Initiate(PGAME_INFO GIptr);
INT TEST_Render(PGAME_INFO GIptr);
INT TEST_Update(PGAME_INFO GIptr);


