#include "VAO.hpp"
#include "vertex.hpp"
#include <cstddef>

VAO::VAO(){
    glGenVertexArrays(1,&id);
}

void VAO::use(){
    glBindVertexArray(id);
}

void VAO::attribute(){
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(vertex),(void*)offsetof(vertex,pos));
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(vertex),(void*)offsetof(vertex,texCoord));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

VAO::~VAO(){
    if(id!=0)
        glDeleteVertexArrays(1,&id);
}