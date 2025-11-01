#include <Defines.h>
#include <Structs.h>
#include <Prototype.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

PSDL_Texture TEXTURE_Load(PGAME_INFO GIptr, PCCHAR FName)
{
	INT          ImageWidth, ImageHeight, Channels;
	PSDL_Surface Surface;
	PSDL_Texture Texture;
	stbi_uc *PixelData;

	if ((PixelData = stbi_load(FName, &ImageWidth, &ImageHeight, &Channels, 4)) == NULL)
	{
		SDL_Log("stbi_load ERROR: %s", FName);
		return(NULL);
	}

	if ((Surface = SDL_CreateSurfaceFrom(ImageWidth, ImageHeight, SDL_PIXELFORMAT_RGBA32, PixelData, ImageWidth * 4)) == NULL)
	{
		SDL_Log("SDL_CreateSurfaceFrom: %s %s", FName, SDL_GetError());
		stbi_image_free(PixelData);
		return(NULL);
	}

	if ((Texture = SDL_CreateTextureFromSurface(GIptr->GI_MainRenderer, Surface)) == NULL)
	{
		SDL_Log("SDL_CreateTextureFromSurface: %s %s", FName, SDL_GetError());
		SDL_DestroySurface(Surface);
		stbi_image_free(PixelData);
		return(NULL);
	}
	SDL_SetTextureScaleMode(Texture, SDL_SCALEMODE_NEAREST);

	SDL_DestroySurface(Surface);
	stbi_image_free(PixelData);

	return(Texture);
}