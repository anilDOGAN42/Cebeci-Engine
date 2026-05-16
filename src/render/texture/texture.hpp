#pragma once
#include <Object.hpp>

namespace CebeciEngine::Render::Texture{
class Texture2D:public CebeciEngine::Core::App::Object::Object{
public:
    Texture2D(char* pathToFile);
    ~Texture2D();
    void bind();
    unsigned int getId();

private:
    int width, height, channels;
    unsigned int id;
};
}