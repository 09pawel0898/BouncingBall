#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#ifdef EN_DEBUG
#define EN_DEBUGMSG(f_, ...) printf("%s", "[Engine] ");\
printf((f_),__VA_ARGS__);\
printf("%s", "\n");
#else
#define EN_DEBUGMSG(f_, ...)
#endif

#define EN_ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
    x;\
    GLASSERT(GLLogCall(#x, __FILE__, __LINE__))

#define BIND_EVENT_FN(x) std::bind(&Application::x, this,std::placeholders::_1)

inline void GLClearError() {
    while (glGetError() != GL_NO_ERROR) {};
}

bool GLLogCall(const char* func, const char* file, int line);

template <typename DataType>
inline constexpr GLenum GetGLEnumFromType() { EN_ASSERT(false); }
template <> inline constexpr GLenum GetGLEnumFromType<uint32_t>()       { return GL_UNSIGNED_INT; }
template <> inline constexpr GLenum GetGLEnumFromType<uint16_t>()       { return GL_UNSIGNED_SHORT; }
template <> inline constexpr GLenum GetGLEnumFromType<unsigned char>()  { return GL_UNSIGNED_BYTE; }
template <> inline constexpr GLenum GetGLEnumFromType<float>()          { return GL_FLOAT; }