#include <GLFW/glfw3.h>

namespace utils {

void glfwFramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void glfwCleanup() { glfwTerminate(); }
} // namespace utils
