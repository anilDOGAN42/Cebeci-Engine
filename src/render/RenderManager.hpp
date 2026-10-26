#pragma once

namespace CebeciEngine::Render {

class RenderManager{
public:
    static RenderManager& instance();

    

private:
    RenderManager()=default;

};

}