#include <iostream>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glfw_utils.hpp>
#include <constants.hpp>
#include <vector>
#include <OpenGL/gl.hpp>

std::uint32_t create_triangle_gl_program() {
    const std::uint32_t vertex_shader_id =
        gl::create_shader("src/Shaders/vertex_shared.glsl", GL_VERTEX_SHADER);

    const std::uint32_t fragment_shader_id = gl::create_shader(
        "src/Shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);

    const std::vector<std::uint32_t> shaders{vertex_shader_id,
                                             fragment_shader_id};

    const std::uint32_t program_id = gl::create_and_link_program(shaders);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}

std::vector<std::uint32_t> init_gl_objects() {
    std::vector<std::uint32_t> object_ids(2);

    // {X, Y, Z} per vertex
    std::float_t vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                               0.0f,  0.0f,  0.5f, 0.0f};

    std::uint32_t vao_id = 0;  // Vertex array object
    std::uint32_t vbo_id = 0;  // Vertex buffer object
    glGenVertexArrays(1, &vao_id);
    glGenBuffers(1, &vbo_id);

    if (vao_id == gl::GL_INVALID_ID || vbo_id == gl::GL_INVALID_ID) {
        std::cout << "Could not generate the vertex buffers" << std::endl;
        return {};
    }

    glBindVertexArray(vao_id);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float_t),
                          (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, gl::GL_INVALID_ID);
    glBindVertexArray(gl::GL_INVALID_ID);

    object_ids[0] = vao_id;
    object_ids[1] = vbo_id;

    return object_ids;
}

void render_triangle(const std::uint32_t PROGRAM_ID,
                     const std::uint32_t VAO_ID) {
    glUseProgram(PROGRAM_ID);
    glBindVertexArray(VAO_ID);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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

    const std::int32_t PROGRAM_ID = create_triangle_gl_program();
    if (PROGRAM_ID == gl::GL_INVALID_ID) {
        std::cout << "GL Program could not have been created. Exiting..."
                  << std::endl;
        return EXIT_FAILURE;
    }

    const std::vector<std::uint32_t> OBJECT_IDS = init_gl_objects();
    if (OBJECT_IDS.size() != 2) {
        return EXIT_FAILURE;
    }

    while (glfwWindowShouldClose(window) != GLFW_TRUE) {
        process_input(window);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        render_triangle(PROGRAM_ID, OBJECT_IDS[0]);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &OBJECT_IDS[0]);
    glDeleteBuffers(1, &OBJECT_IDS[1]);
    glDeleteProgram(PROGRAM_ID);

    glfw::glfwCleanup();
    return EXIT_SUCCESS;
}
