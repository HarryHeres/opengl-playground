#include <GLFW/glfw3.h>

namespace glfw {
void glfwCleanup() {
    glfwTerminate();
}
}  // namespace glfw
