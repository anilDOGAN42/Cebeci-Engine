#include "SSBO.hpp"
#include <glad/glad.h>

SSBO::SSBO(unsigned int slot){
    this->slot=slot;

    glGenBuffers(1, &id);   
}

void SSBO::use(){
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, id);
}

void SSBO::bind(){
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, slot, id);
}