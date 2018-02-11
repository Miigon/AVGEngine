#pragma once
#include "Platform.h"

#ifdef AVG_DESKTOP
#include <GL/glew.h>
#ifdef AVG_APPLE
#undef glGenVertexArrays
#undef glBindVertexArray
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#endif
#else
#include <SDL_opengles2.h>
#define GL_GLEXT_PROTOTYPES
#include <SDL_opengles2_gl2ext.h>
extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES;
extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES;
extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES;
extern PFNGLISVERTEXARRAYOESPROC glIsVertexArrayOES;
#define glGenVertexArrays glGenVertexArraysOES
#define glBindVertexArray glBindVertexArrayOES
#endif