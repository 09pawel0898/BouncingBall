#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <vector>
#include <type_traits>
#include <string>
#include <unordered_map>

#define EN_ASSERT(x) if(!(x)) __debugbreak()

#define GLCall(x) GLClearError();\
    x;\
    EN_ASSERT(GLLogCall(#x, __FILE__, __LINE__))

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