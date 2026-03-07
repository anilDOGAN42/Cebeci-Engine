#include "VBO.hpp"
#include "vertex.hpp"

VBO::VBO(){
    glGenBuffers(1,&id);

}

VBO::~VBO(){
    if(id!=0)
        glDeleteBuffers(1,&id);
}

void VBO::use(){
    glBindBuffer(GL_ARRAY_BUFFER,id);
}

void VBO::changeData(vertex* Data,size_t length){
    this->use();
    this->length=length;
    glBufferData(GL_ARRAY_BUFFER,length *sizeof(vertex),Data, GL_STATIC_DRAW);
}

void VBO::draw(){
    glDrawArrays(GL_TRIANGLES,0,length);
}