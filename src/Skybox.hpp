#pragma once

#include <array>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.hpp"

class Skybox {
public:
    explicit Skybox(const std::array<std::string,6>& faces);
    void draw(const glm::mat4& view, const glm::mat4& proj) const;

private:
    GLuint cubemapTex = 0;
    GLuint vao = 0, vbo = 0;
    Shader shader;
};
