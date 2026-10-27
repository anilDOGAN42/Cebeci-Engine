#include "VAO.hpp"
#include "Vertex/VertexAttribute.hpp"
#include "vertex.hpp"
#include <cstddef>

using CebeciEngine::Render::Vertex::VertexAttribute;
namespace CebeciEngine::Render{
VAO::VAO(VertexAttribute* atrr){
    this->attr=atrr;
    glGenVertexArrays(1,&id);

}

void VAO::use(){
    glBindVertexArray(id);
}

void VAO::setAttributes(){
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(vertex),(void*)offsetof(vertex,pos));
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(vertex),(void*)offsetof(vertex,texCoord));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    return;


    for(size_t i=0,j=0;i<attr->attributes.size();i++){
        struct VertexAttribute::attribute attribute=attr->attributes.at(i);

        glVertexAttribPointer(i,attribute.count,GL_FLOAT,GL_FALSE,attr->totalSize,(void*)j);
        
        glEnableVertexAttribArray(i);

        glBindVertexArray(i);

        j += attribute.size * attribute.count;
    }

}

unsigned int VAO::getID(){
    return id;
}

VAO::~VAO(){
    if(id!=0)
        glDeleteVertexArrays(1,&id);
}
}