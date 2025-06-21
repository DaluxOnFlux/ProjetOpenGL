#pragma once

#include <string>
#include <glad/glad.h>
#include <tiny_obj_loader.h>

class ObjModel {
public:
    explicit ObjModel(const std::string& path);
    void draw() const;
    void loadTexture(const std::string& path);

    GLuint textureID = 0;

private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    GLsizei indicesCount = 0;
};
