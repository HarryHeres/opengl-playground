#pragma once

#include <GLFW/glfw3.h>

namespace utils {
void glfwFramebufferSizeCallback(GLFWwindow *window, int width, int height);
void glfwCleanup();
} // namespace utils
