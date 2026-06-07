#include "node.hpp"
#include "Mesh.hpp"
#include "transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "application.hpp"
#include <Object.hpp>

static CebeciEngine::Core::App::App& app=CebeciEngine::Core::App::App::instance();
namespace CebeciEngine::Core {

node::node(){
    transform* Transform = new transform;
    this->addComponent(Transform);
}

}