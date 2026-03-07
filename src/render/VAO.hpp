#pragma once
#include <glad/glad.h>

class VAO{
public:
    VAO();
    void use();
    void attribute();
    ~VAO();

    unsigned int id;
};