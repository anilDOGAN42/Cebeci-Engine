#include "shader.hpp"
#include <fstream>
#include <iostream>
#include <string>

Shader::Shader(GLenum shaderType, char* sourceFile) {
    id = glCreateShader(shaderType);

    std::ifstream srcFile(sourceFile, std::ios::in | std::ios::binary);
    
    if (!srcFile) {
        throw std::runtime_error("Shader dosyası açılamadı!");
    }

    std::string code((std::istreambuf_iterator<char>(srcFile)),
                      std::istreambuf_iterator<char>());

    srcFile.close();

    source = code;           
    src = source.c_str();      
}

void Shader::createShader(){
    glShaderSource(id,1,&src,nullptr);
}

void Shader::compileShader(){
    glCompileShader(id);

}

Shader::~Shader(){
    if(id!=0)
        glDeleteShader(id);
}

ShaderProgram::ShaderProgram(){
    id=glCreateProgram();
}

void ShaderProgram::attachShader(unsigned int shaderId){
    glAttachShader(id,shaderId);
}

void ShaderProgram::linkProgram(){
    glLinkProgram(id);
}

void ShaderProgram::use(){
    glUseProgram(id);
}

ShaderProgram::~ShaderProgram(){
    if(id!=0)
        glDeleteProgram(id);
}