#pragma once
#include <Object.hpp>
#include "transform.hpp"
#include <vector>

class Mesh;

class node: public Object{
public:
    node()=default;
    ~node();

    void changeMesh(Mesh* mesh);
    Mesh* getMesh();

    node* getParent();
    void setParent(node* Parent);

    void addChild(node* Child);
    
    transform* getTransform();  

private:

    node* Parent = nullptr;
    std::vector<node*> childs;

    transform Transform;
    Mesh* mesh;
};