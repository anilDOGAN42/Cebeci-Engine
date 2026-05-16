#pragma once
#include "SSBO.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "node.hpp"
#include "texture.hpp"
#include "vertex.hpp"
#include <vector>
#include <Object.hpp>

namespace CebeciEngine {
namespace Core{class node;}
using Core::node;
namespace Render{
class Mesh:public CebeciEngine::Core::App::Object::Object{
public:
    Mesh(std::vector<vertex> verticies);
    ~Mesh();
    void changeNode(node* Node);

    void draw();

    void changeTexture(Texture::Texture2D* texture);

    void changeVerticies(std::vector<vertex>* verticies);

private:
    VBO vbo;
    VAO vao;
    SSBO *transforms;

    Texture::Texture2D* texture;
    
    node* Node;

    std::vector<vertex> verticies;

    unsigned int shaderProgram;
};
}
}