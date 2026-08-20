#pragma once
#include <Object.hpp>
#include "Mesh.hpp"
#include "scene.hpp"
namespace CebeciEngine {
namespace Render {class Mesh;}
using Render::Mesh;
using Core::App::Object::Object;
namespace Core {
class scene;
class node: public App::Object::Object{
public:
    node();
    ~node()=default;

    bool addChild(Object* component);

private:
    friend class CebeciEngine::Core::scene;
    bool addedToScene=false;
};
}
}