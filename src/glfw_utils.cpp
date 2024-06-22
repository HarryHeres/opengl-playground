#include <GLFW/glfw3.h>

namespace glfw_utils {
void glfwCleanup() {
  glfwTerminate();
}
}  // namespace glfw_utils
