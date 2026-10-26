#include "VertexAttribute.hpp"

namespace CebeciEngine::Render::Vertex {

VertexAttribute::VertexAttribute(int totalSize):totalSize(totalSize){}

void VertexAttribute::setAttribute(size_t index,unsigned int type,size_t size,size_t count){
    if(index>=attributes.size()){
        attributes.resize(index+1);
    }

    attributes[index].size=size;
    attributes[index].count=count;

}

}