#pragma once
#include "Vertex/VertexAttribute.hpp"
#include <glad/glad.h>

namespace CebeciEngine::Render{
class VAO{
public:
    VAO(Vertex::VertexAttribute* atrr);
    void use();
    void setAttributes();
    ~VAO();

    unsigned int getID();
private:
    unsigned int id;

    Vertex::VertexAttribute* attr;

};
}