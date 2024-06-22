#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glfw_utils.hpp>
#include <constants.hpp>

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // For MacOS

    GLFWwindow* window = glfwCreateWindow(GLFW_WINDOW_WIDTH, GLFW_WINDOW_HEIGHT,
                                          "Hello World", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfw_utils::glfwCleanup();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfw_utils::glfwCleanup();
        return EXIT_FAILURE;
    }

    /* glfwSetFramebufferSizeCallback(window, glfw_utils::glfwFramebufferSizeCallback); */

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfw_utils::glfwCleanup();
    return EXIT_SUCCESS;
}
