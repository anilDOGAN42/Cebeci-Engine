#pragma once
#include <glad/glad.h>

namespace CebeciEngine::Render{
class VAO{
public:
    VAO();
    void use();
    void attribute();
    ~VAO();

    unsigned int id;
};
}