#pragma once
#include <glad/glad.h>
#include <string>

namespace CebeciEngine::Render{
class Shader {
public:
    Shader(GLenum shaderType, char* sourceFile);
    void createShader();
    void compileShader();
    ~Shader();

    unsigned int id;

private:
    std::string source;  
    const char* src;     
};


class ShaderProgram{
public:
    ShaderProgram();
    void attachShader(unsigned int id);
    void linkProgram();
    void use();
    unsigned int id;
    ~ShaderProgram();
};
}