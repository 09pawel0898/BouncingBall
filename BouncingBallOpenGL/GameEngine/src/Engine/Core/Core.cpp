#include "Core.h"

bool GLLogCall(const char* func, const char* file, int line)
{
    GLenum error;
    while ((error = glGetError() != GL_NO_ERROR))
    {
        std::cerr << "[OpenGL Error] (" << error << ") at " << func << " in " << file << " line " << line;
        return false;
    }
    return true;
}