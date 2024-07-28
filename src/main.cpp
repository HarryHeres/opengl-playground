#include <iostream>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glfw_utils.hpp>
#include <constants.hpp>
#include <vector>
#include <OpenGL/gl.hpp>

void render_triangle(GLFWwindow* window) {
    // {X, Y, Z} per point
    std::float_t vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                               0.0f,  0.0f,  0.5f, 0.0f};
    std::uint32_t buffer_id = 0;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const std::int32_t vertex_shader_id =
        gl::create_shader("src/Shaders/vertex_shared.glsl", GL_VERTEX_SHADER);

    const std::int32_t fragment_shader_id = gl::create_shader(
        "src/Shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);

    const std::vector<std::int32_t> shaders(vertex_shader_id,
                                            fragment_shader_id);

    const std::int32_t program_id = gl::create_program(shaders);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main() {
    if (glfwInit() == GLFW_FALSE) {
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // For MacOS

    GLFWwindow* window =
        glfwCreateWindow(gl::GLFW_WINDOW_WIDTH, gl::GLFW_WINDOW_HEIGHT,
                         "Hello World", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfw::glfwCleanup();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfw::glfwCleanup();
        return EXIT_FAILURE;
    }

    glViewport(0, 0, gl::GLFW_WINDOW_WIDTH,
               gl::GLFW_WINDOW_HEIGHT);  // Set window viewport size

    /* glfwSetFramebufferSizeCallback(window, glfw::glfwFramebufferSizeCallback); */

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (glfwWindowShouldClose(window) != GLFW_TRUE) {
        glClear(GL_COLOR_BUFFER_BIT);

        process_input(window);

        render_triangle(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfw::glfwCleanup();
    return EXIT_SUCCESS;
}
