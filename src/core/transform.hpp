#pragma once
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector.hpp>

class transform{
public:
    transform();

    vec3 Position;
    vec3 Rotation;
    vec3 Scale;


    operator glm::mat4() const {
        glm::mat4 mat(1.0f); 

        mat = glm::translate(mat, (glm::vec3)(vec3)Position); 
        
        mat = glm::rotate(mat, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
        mat = glm::rotate(mat, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
        mat = glm::rotate(mat, glm::radians(Rotation.x), glm::vec3(1, 0, 0));

        
        mat = glm::scale(mat, (glm::vec3)(vec3)Scale);
        return mat;
    }
};//Buna iyi bir ayar çekmek lazım
// Quaternion kullanmamız lazım