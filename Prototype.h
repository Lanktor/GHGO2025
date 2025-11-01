
#include <SDL3/SDL.h>
#include <SDL_mixer.h>

typedef FILE *PFILE, **PPFILE;

typedef char CHAR, *PCHAR, **PPCHAR;
typedef const unsigned char UCHAR, *PUCHAR, **PPUCHAR;
typedef const char CCHAR, *PCCHAR, **PPCCHAR;
typedef int INT, *PINT, **PPINT;
typedef unsigned int UINT, *PUINT, **PPUINT;
typedef float FLOAT, *PFLOAT, **PPFLOAT;
typedef double DOUBLE, *PDOUBLE, **PPDOUBLE;
typedef void VOID, *PVOID, **PPVOID;
typedef bool BOOL;
typedef Uint64 UINT64, *PUINT64, **PPUINT64;

typedef SDL_Window *PSDL_Window, **PPSDL_Window;
typedef SDL_Rect *PSDL_Rect, **PPSDL_Rect;
typedef SDL_FRect *PSDL_FRect, **PPSDL_FRect;
#define SZ_SDL_FRECT sizeof(SDL_FRect)
typedef SDL_Renderer *PSDL_Renderer, **PPSDL_Renderer;
typedef SDL_Surface *PSDL_Surface, **PPSDL_Surface;
typedef SDL_Texture *PSDL_Texture, **PPSDL_Texture;
typedef Mix_Music *PMix_Music, **PPMix_Music;
typedef Mix_Chunk *PMix_Chunk, **PPMix_Chunk;

#define TRUE  true
#define FALSE false
#define RANDOM_SEED 3556830853
#define END_OF_LIST 65535

#define MAX_NAME_LENGTH        12
#define MAX_NAMES               5

#define GAME_IS_ACTIVE        5000
#define GAME_IS_INACTIVE      5001
#define OBJECT_IS_ACTIVE      5002
#define OBJECT_IS_NOT_ACTIVE  5003
#define LEVEL_IS_ACTIVE       5004
#define LEVEL_IS_COMPLETE     5005

#define GAME_VERSION          100
#define GAME_BASE_SCORE       5000
#define GAME_MAX_LEVEL_TIME   300 // Seconds

