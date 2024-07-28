#pragma once

#include <OpenGL/OpenGL.h>
#include <optional>
#include <string>

namespace gl {

const std::string KERNEL_FILE_EXTENSION = ".glsl";

const std::optional<const std::string> load_kernel_from_file(
    const std::string& file_path) noexcept;

std::int32_t create_shader(const std::string shader_file_path,
                           const GLenum shader_type) noexcept;

std::int32_t create_program(const std::vector<std::int32_t>& shaders) noexcept;
}  // namespace gl
