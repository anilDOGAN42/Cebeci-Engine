#pragma once
#include <Object.hpp>
class Texture2D:public Object{
public:
    Texture2D(char* pathToFile);
    void bind();
    unsigned int getId();

private:
    int width, height, channels;
    unsigned int id;
};