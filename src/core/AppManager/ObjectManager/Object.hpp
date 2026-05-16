#pragma once
#include <string>
#include <vector>

namespace CebeciEngine::Core::App::Object {
class Object{
public:
    unsigned long int id;
    std::string name;

    Object();
    virtual ~Object();

    std::vector<std::string> tags;

    void addTag(std::string tagName);

    bool removeTag(std::string name);

    
};
}