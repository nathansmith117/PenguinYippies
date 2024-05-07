#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <raylib.h>
#include <raymath.h>

//#define PLATFORM_WEB

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

// Memory management.
#define YP_MALLOC(size) malloc(size)
#define YP_CALLOC(nmemb, size) calloc(nmemb, size)
#define YP_REALLOC(ptr, size) realloc(ptr, size)
//#define YP_REALLOCARRAY(ptr, nmemb, size) reallocarray(ptr, nmemb, size)
#define YP_REALLOCARRAY(ptr, nmemb, size) realloc(ptr, nmemb * size)
#define YP_FREE(ptr) free(ptr)

#define ALLOCATION_ERROR TraceLog(LOG_ERROR, "Allocation error in %s:%d", __FILE__, __LINE__)

#ifndef GAME_COMMON_H
#define GAME_COMMON_H

typedef struct Game Game;

#endif
