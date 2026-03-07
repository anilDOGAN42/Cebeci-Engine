#pragma once
#include "vertex.hpp"
#include <glad/glad.h>

class VBO{
public:
    VBO();
    void changeData(vertex* Data,size_t length);
    void use();
    void draw();
    ~VBO();
    unsigned int id;
private:
    size_t length;
};