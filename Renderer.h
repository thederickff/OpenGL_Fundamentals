#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>

//#define ASSERT(x) if (!(x)) _debugbreak;
#ifdef DEBUG
    #define GLCall(x) GLClearError(); x; GLLogCall(#x, __FILE__, __LINE__);
#else   
    #define GLCall(x) x;
#endif

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif /* RENDERER_H */

