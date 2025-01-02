#pragma once

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <stdint.h>
#include <cstddef>

namespace gl {
const std::size_t GLFW_WINDOW_HEIGHT = 600;
const std::size_t GLFW_WINDOW_WIDTH = 800;

const std::size_t GL_STATUS_INFO_BUFFER_SIZE = 512;

const uint32_t GL_INVALID_ID = 0;
}  // namespace gl
