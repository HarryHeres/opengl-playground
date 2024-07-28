#include <OpenGL/gl.hpp>
#include <fstream>
#include <iostream>
#include <GLAD/glad.h>
#include <constants.hpp>
#include <vector>

namespace gl {

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

    return rv;
}

std::int32_t create_shader(const std::string shader_file_path,
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

    const char* str = kernel_source.c_str();
    glShaderSource(shader_id, 1, &str, NULL);
    glCompileShader(shader_id);

    int compile_status = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == 0) {
        char info_buffer[GL_STATUS_INFO_BUFFER_SIZE];
        glGetShaderInfoLog(shader_id, GL_STATUS_INFO_BUFFER_SIZE * sizeof(char),
                           NULL, info_buffer);
        std::cout << "GL fragment shader compilation failure: " << info_buffer
                  << std::endl;
        return GL_INVALID_ID;
    }

    return shader_id;
}

std::int32_t create_program(const std::vector<std::int32_t>& shaders) noexcept {
    std::int32_t program_id = 0;
    program_id = glCreateProgram();

    for (auto it = shaders.begin(); it != shaders.end(); ++it) {
        glAttachShader(program_id, *it);
    }

    glLinkProgram(program_id);

    int link_status = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
    if (link_status == 0) {
        char info_buffer[GL_STATUS_INFO_BUFFER_SIZE];
        glGetProgramInfoLog(program_id,
                            GL_STATUS_INFO_BUFFER_SIZE * sizeof(char), NULL,
                            info_buffer);
        std::cout << "GL fragment shader compilation failure: " << info_buffer
                  << std::endl;
        return GL_INVALID_ID;
    }

    return program_id;
}

}  // namespace gl
