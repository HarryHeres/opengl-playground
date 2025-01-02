#include <GLFW/glfw_utils.hpp>

namespace glfw {
void glfwCleanup() {
    glfwTerminate();
}
}  // namespace glfw
