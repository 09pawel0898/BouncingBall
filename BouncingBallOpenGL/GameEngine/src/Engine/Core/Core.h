#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef EN_DEBUG
#include <iostream>
#define EN_DEBUGMSG(x) std::cout << x << "\n" 
#else
#define EN_DEBUGMSG(x)
#endif

#define EN_ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
    x;\
    GLASSERT(GLLogCall(#x, __FILE__, __LINE__))

inline void GLClearError() {
    while (glGetError() != GL_NO_ERROR) {};
}

bool GLLogCall(const char* func, const char* file, int line);

template <typename DataType>
inline constexpr GLenum GetGLEnumFromType() { GLASSERT(false); }
template <> inline constexpr GLenum GetGLEnumFromType<uint32_t>()       { return GL_UNSIGNED_INT; }
template <> inline constexpr GLenum GetGLEnumFromType<uint16_t>()       { return GL_UNSIGNED_SHORT; }
template <> inline constexpr GLenum GetGLEnumFromType<unsigned char>()  { return GL_UNSIGNED_BYTE; }
template <> inline constexpr GLenum GetGLEnumFromType<float>()          { return GL_FLOAT; }