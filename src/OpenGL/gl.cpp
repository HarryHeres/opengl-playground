#include <OpenGL/gl.hpp>
#include <fstream>
#include <iostream>
#include <GLAD/glad.h>
#include <constants.hpp>
#include <vector>

namespace gl {

void print_gl_shader_error(const std::uint32_t SHADER_ID) noexcept {
    char info_buffer[GL_STATUS_INFO_BUFFER_SIZE];
    glGetShaderInfoLog(SHADER_ID, GL_STATUS_INFO_BUFFER_SIZE * sizeof(char),
                       NULL, info_buffer);

    std::cout << "GL error for object: " << SHADER_ID << ": " << info_buffer
              << std::endl;
}

void print_gl_program_error(const std::uint32_t PROGRAM_ID) noexcept {
    char info_buffer[GL_STATUS_INFO_BUFFER_SIZE];
    glGetProgramInfoLog(PROGRAM_ID, GL_STATUS_INFO_BUFFER_SIZE * sizeof(char),
                        NULL, info_buffer);

    std::cout << "GL error for object: " << PROGRAM_ID << ": " << info_buffer
              << std::endl;
}

const std::optional<const std::string> load_kernel_from_file(
    const std::string& file_path) noexcept {
    std::string rv;

    if (file_path.empty()) {
        return {};
    }

    if (file_path.find(KERNEL_FILE_EXTENSION) == std::string::npos) {
        std::cout << "File " << file_path << " must be in a "
                  << KERNEL_FILE_EXTENSION << " format" << std::endl;
        return {};
    }

    std::ifstream file_stream;
    file_stream.open(file_path, std::ios::in);

    if (!file_stream.is_open()) {
        std::cout << "File " << file_path
                  << " could not have been opened. Make sure the file exists "
                     "and that read permissions are set."
                  << std::endl;
        return {};
    }

    std::string curr_line;
    while (std::getline(file_stream, curr_line)) {
        curr_line.append("\n");
        rv.append(curr_line);
    }
    rv.append("\0");

    return rv;
}

std::uint32_t create_shader(const std::string shader_file_path,
                            const GLenum shader_type) noexcept {
    std::optional<const std::string> rv =
        gl::load_kernel_from_file(shader_file_path);

    if (!rv.has_value()) {
        return GL_INVALID_ID;
    }

    const std::string& kernel_source = rv.value();
    if (kernel_source.empty()) {
        std::cout << "GL kernel source cannot be empty" << std::endl;
        return GL_INVALID_ID;
    }

    uint32_t shader_id = 0;
    shader_id = glCreateShader(shader_type);

    /* const char* str = kernel_source.c_str(); */

    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    const char* shaderSource = shader_type == GL_VERTEX_SHADER
                                   ? vertexShaderSource
                                   : fragmentShaderSource;

    glShaderSource(shader_id, 1, &shaderSource, NULL);
    glCompileShader(shader_id);

    int compile_status = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == 0) {
        print_gl_shader_error(shader_id);
        return GL_INVALID_ID;
    }

    return shader_id;
}

std::uint32_t create_and_link_program(
    const std::vector<std::uint32_t>& shaders) noexcept {
    if (shaders.size() == 0) {
        std::cout << "Cannot make program with no shaders" << std::endl;
        return GL_INVALID_ID;
    }

    std::uint32_t program_id = 0;
    program_id = glCreateProgram();

    if (program_id == GL_INVALID_ID) {
        std::cout << "Could not create program" << std::endl;
        return GL_INVALID_ID;
    }

    glAttachShader(program_id, shaders[0]);
    glAttachShader(program_id, shaders[1]);

    /* for (auto it = shaders.begin(); it != shaders.end(); ++it) { */
    /*     glAttachShader(program_id, *it); */
    /* } */

    glLinkProgram(program_id);

    std::int32_t link_status = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
    if (link_status == GL_INVALID_ID) {
        print_gl_program_error(program_id);
        return GL_INVALID_ID;
    }

    return program_id;
}

}  // namespace gl
