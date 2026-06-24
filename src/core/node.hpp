#pragma once
#include <Object.hpp>
#include "Mesh.hpp"
namespace CebeciEngine {
namespace Render {class Mesh;}
using Render::Mesh;
using Core::App::Object::Object;
namespace Core {
class node: public App::Object::Object{
public:
    node();
    ~node()=default;

    
};
}
}