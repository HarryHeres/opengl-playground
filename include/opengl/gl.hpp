#pragma once

#include <glad/glad.h>
#include <optional>
#include <string>
#include <cstdint>
#include <vector>

namespace gl {

const std::string KERNEL_FILE_EXTENSION = ".glsl";

void print_gl_shader_error(const std::uint32_t SHADER_ID) noexcept;

void print_gl_program_error(const std::uint32_t PROGRAM_ID) noexcept;

const std::optional<const std::string> load_kernel_from_file(
    const std::string& file_path) noexcept;

std::uint32_t create_shader(const std::string shader_file_path,
                            const GLenum shader_type) noexcept;

std::uint32_t create_and_link_program(
    const std::vector<std::uint32_t>& shaders) noexcept;

}  // namespace gl
