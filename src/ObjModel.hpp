#pragma once
#include <tiny_obj_loader.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class ObjModel {
public:
    GLuint vao, vbo, ebo;
    int indicesCount;
    ObjModel(const std::string& path);
    void draw() const;
};
