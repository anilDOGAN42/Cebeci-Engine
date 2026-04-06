#pragma once
#include "SSBO.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "texture.hpp"
#include "vertex.hpp"
#include <vector>
#include <Object.hpp>

class node;

class Mesh:public Object{
public:
    Mesh(std::vector<vertex> verticies);
    void changeNode(node* Node);

    void draw();

    void changeTexture(Texture2D* texture);

    void changeVerticies(std::vector<vertex>* verticies);

private:
    VBO vbo;
    VAO vao;
    SSBO *transforms;

    Texture2D* texture;
    
    node* Node;

    std::vector<vertex> verticies;

    unsigned int shaderProgram;
};