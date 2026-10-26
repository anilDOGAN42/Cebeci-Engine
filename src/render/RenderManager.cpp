#include "RenderManager.hpp"

namespace CebeciEngine::Render {

RenderManager& RenderManager::instance(){
    static RenderManager instance;
    return instance;
}

}