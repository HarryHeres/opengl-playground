#pragma once

#include <stdint.h>
#include <cstddef>
#include <OpenGL/gl.h>

namespace gl {
const std::size_t GLFW_WINDOW_HEIGHT = 600;
const std::size_t GLFW_WINDOW_WIDTH = 800;

const std::size_t GL_STATUS_INFO_BUFFER_SIZE = 512;

const int32_t GL_INVALID_ID = -1;
}  // namespace gl
