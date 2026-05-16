#pragma once
#include <Object.hpp>
//#include "application.hpp"
#include "Mesh.hpp"
#include "transform.hpp"
#include <vector>

namespace CebeciEngine {
namespace Render {class Mesh;}
using Render::Mesh;
namespace Core {
class node: public App::Object::Object{
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
}
}