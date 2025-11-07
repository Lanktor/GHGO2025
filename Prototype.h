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

INT EBI_CheckForCollisionWithOtherObjects(PGAME_INFO GIptr, PENEMY_BASIC_INFO EBIptr);
INT EBI_Clear(PGAME_INFO GIptr);
INT EBI_Initiate(PGAME_INFO GIptr);
INT EBI_Move(PGAME_INFO GIptr, PENEMY_BASIC_INFO EBIptr);
INT EBI_Update(PGAME_INFO GIptr);
INT EBI_Render(PGAME_INFO GIptr);

INT WAI_GetClosestEnemy(PGAME_INFO GIptr, PWEAPON_AUTO_INFO WAIptr);
INT WAI_Initiate(PGAME_INFO GIptr);
INT WAI_Spawn(PGAME_INFO GIptr);
INT WAI_Update(PGAME_INFO GIptr);
INT WAI_Move(PGAME_INFO GIptr);
INT WAI_Render(PGAME_INFO GIptr);

INT FF_Render(PGAME_INFO GIptr);


INT   UTIL_CheckInsideCircle(PGAME_INFO GIptr, PSDL_FRect Objptr, FLOAT CX, FLOAT CY, FLOAT Rad);
FLOAT UTIL_DegreesToRadians(FLOAT Degrees);
INT   UTIL_DrawCollisionBox(PGAME_INFO GIptr, PSDL_FRect SrceBox, SDL_Color Color, INT BorderSize);
FLOAT UTIL_RandomFloatRange(FLOAT Min, FLOAT Max);
INT   UTIL_RandomIntRange(PUINT State, INT Min, INT Max);
FLOAT UTIL_RadiansToDegrees(FLOAT Radians);

INT LEVEL_BuildOne(PGAME_INFO GIptr);

INT TIMER_Update(PGAME_INFO GIptr);
INT TIMER_CheckExpired(PGAME_INFO GIptr);
INT TIMER_UpdateLevelTimer(PGAME_INFO GIptr);
INT TIMER_RenderLevelTimer(PGAME_INFO GIptr);

void SGI_CheckEnemiesInCone(PGAME_INFO GIptr, float coneAngleDeg, float coneDistance);


INT TEST_Initiate(PGAME_INFO GIptr);
INT TEST_Render(PGAME_INFO GIptr);
INT TEST_Update(PGAME_INFO GIptr);


