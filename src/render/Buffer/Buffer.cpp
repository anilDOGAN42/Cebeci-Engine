#include "Buffer.hpp"
#include "VBO.hpp"

namespace CebeciEngine::Render{

Buffer::Buffer(int type,void* data,unsigned int length,int usage)
:type(type),data(data),length(length),usage(usage)
{
    glGenBuffers(1,&id);
}

Buffer::~Buffer(){
    if(id!=0)
        glDeleteBuffers(1,&id);
}

void Buffer::bind(){
    glBindBuffer(type,id);
}
void Buffer::syncronize(){
    this->bind();
    glBufferData(type,length,data,usage);
}

unsigned int Buffer::getID(){
    return id;
}

}