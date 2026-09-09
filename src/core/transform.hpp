#pragma once
#include "Matrix.hpp"
#include "Object.hpp"
#include "Quaternion.hpp"
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector.hpp>

using namespace CebeciEngine::Core::Math;

namespace CebeciEngine::Core {
class Transform:public App::Object::Object{
public:
    Mat4 getLocalMatrix();
    Mat4 getWorldMatrix();

    void setPosition(Vec3 v);
    void setRotation(Vec3 v);
    void setScale(Vec3 v);

    Vec3 getPosition() const;
    Vec3 getRotation() const;
    Vec3 getScale   () const;

    void Rotate(Vec3 v);
    void RotateX(float degrees);
    void RotateY(float degrees);
    void RotateZ(float degrees);

private:
    vec3 Position={0,0,0};
    Quaternion Rotation;
    vec3 Scale={1,1,1};

    void calculateWorldMatrix();
    void calculateLocalMatrix();
    
    Mat4 calculatePositionMatrix() const;
    Mat4 calculateRotationMatrix() const;
    Mat4 calculateScaleMatrix() const;

    mutable bool isWorldMatrixDirty=true;
    mutable Mat4 worldMatrix;
    
    mutable bool isLocalMatrixDirty=true;
    mutable Mat4 localMatrix;

    void markDirty();

};

}

