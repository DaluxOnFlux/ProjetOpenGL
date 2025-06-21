#pragma once
#include <string>
#include <glad/glad.h>

class Shader {
public:
    GLuint id;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use() const;
    void setMat4(const std::string &name, const float* value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setFloat(const std::string &name, float value) const;
};
