#pragma once
#include <vector>
#include <glad/glad.h>

namespace CebeciEngine::Render{
class SSBO{
public:
    SSBO(unsigned int slot);
    ~SSBO();

    template<typename T,typename ST>
    void changeData(std::vector<T> *Data){
        std::vector<ST> matrices;
        matrices.reserve(Data->size());
        for (auto &t : *Data)
            matrices.push_back((ST)t);

        use();
        glBufferData(GL_SHADER_STORAGE_BUFFER, matrices.size() * sizeof(ST), matrices.data(), GL_DYNAMIC_DRAW);
        bind();
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    }

    void use();
    void bind();

    unsigned int id;
    unsigned int slot;
};
}