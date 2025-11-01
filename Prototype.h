#pragma once

INT InitializeApplication(PGAME_INFO GIptr);


PSDL_Texture TEXTURE_Load(PGAME_INFO GIptr, PCCHAR FName);

INT TEXT_WriteText(PGAME_INFO GIptr, SDL_Color Color, PSDL_FRect Dest, const char *Text, INT Scale);
