#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>

#define GLCall(x) GLClearError(); x; GLLogCall(#x, __FILE__, __LINE__);

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif // defined(RENDERER_H)