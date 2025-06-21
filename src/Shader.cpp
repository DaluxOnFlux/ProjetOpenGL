#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::ifstream vFile(vertexPath);
    std::ifstream fFile(fragmentPath);
    std::stringstream vStream, fStream;
    vStream << vFile.rdbuf();
    fStream << fFile.rdbuf();
    std::string vCode = vStream.str();
    std::string fCode = fStream.str();
    const char* vSrc = vCode.c_str();
    const char* fSrc = fCode.c_str();

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vSrc, nullptr);
    glCompileShader(vShader);

    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fSrc, nullptr);
    glCompileShader(fShader);

    id = glCreateProgram();
    glAttachShader(id, vShader);
    glAttachShader(id, fShader);
    glLinkProgram(id);

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::use() const { glUseProgram(id); }

void Shader::setMat4(const std::string &name, const float* value) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, value);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
