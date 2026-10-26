#pragma once

namespace CebeciEngine::Render{

class Buffer{
public:
    Buffer(int type,void* data,unsigned int length,int usage);
    ~Buffer();

    void bind();
    void syncronize();

    unsigned int getID();

private:
    unsigned int id;

    int type;
    int usage;

    void* data;
    unsigned int length;

};

}