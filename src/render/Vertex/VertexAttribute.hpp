#pragma once
#include <vector>
#include <glad/glad.h>

namespace CebeciEngine::Render{

class VAO;

namespace Vertex {

class VertexAttribute{
public: 
    VertexAttribute(int totalSize);

    void setAttribute(size_t index,unsigned int type,size_t size,size_t count);

private:
    friend class Render::VAO;

    struct attribute{
        size_t type;
        size_t size;
        size_t count; 
    };

    std::vector<struct attribute> attributes{};
    size_t totalSize;
};


}
}