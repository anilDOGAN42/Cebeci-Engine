#include "transform.hpp"
#include "Matrix.hpp"
#include "Object.hpp"
#include "Quaternion.hpp"
#include "node.hpp"

namespace CebeciEngine::Core {
Mat4 Transform::getLocalMatrix(){
    if(isLocalMatrixDirty){
        calculateLocalMatrix();
    }
    return localMatrix;
}
Mat4 Transform::getWorldMatrix(){
    if(isWorldMatrixDirty){
        calculateWorldMatrix();
    }
    return worldMatrix;
}

void Transform::setPosition(Vec3 v){
    Position=v;
    markDirty();
}
void Transform::setRotation(Vec3 v){
    Rotation=Quaternion::FromEuler(v);
    markDirty();
}
void Transform::setScale(Vec3 v){
    Scale=v;
    markDirty();
}

Vec3 Transform::getPosition() const{
    return {Position.x,Position.y,Position.z};
}
Vec3 Transform::getRotation() const{
    return Rotation.toEuler();
}
Vec3 Transform::getScale() const{
    return {Scale.x,Scale.y,Scale.z};
}

void Transform::Rotate(Vec3 v) {
    Rotation = Rotation * Quaternion::FromEuler(v);
    Rotation.normalize();
    markDirty();
}

void Transform::RotateX(float degrees) {
    Rotation = Rotation * Quaternion::FromEuler({degrees, 0.0f, 0.0f});
    Rotation.normalize();
    markDirty();
}

void Transform::RotateY(float degrees) {
    Rotation = Rotation * Quaternion::FromEuler({0.0f, degrees, 0.0f});
    Rotation.normalize();
    markDirty();
}

void Transform::RotateZ(float degrees) {
    Rotation = Rotation * Quaternion::FromEuler({0.0f, 0.0f, degrees});
    Rotation.normalize();
    markDirty();
}

void Transform::calculateWorldMatrix() {
    Mat4 localMat = getLocalMatrix();

    App::Object::Object* Grandparent=this->getParent()->getParent();

    if(Grandparent){
        Transform* parentTransform = Grandparent->getChildByType<Transform>();

        if (parentTransform) {
            worldMatrix = parentTransform->getWorldMatrix() * localMat;

            isWorldMatrixDirty = false;
            return;
        }
    }
    worldMatrix = localMat;
    
    isWorldMatrixDirty = false;
}

void Transform::calculateLocalMatrix(){

    Mat4 T = calculatePositionMatrix();
    Mat4 R = calculateRotationMatrix();
    Mat4 S = calculateScaleMatrix();

    localMatrix = T * R * S;
    isLocalMatrixDirty = false;

}

Mat4 Transform::calculatePositionMatrix() const{
    Mat4 mat{};

    mat[0][0]=1;
    mat[1][1]=1;
    mat[2][2]=1;
    mat[3][3]=1;

    mat[0][3]=Position.x;
    mat[1][3]=Position.y;
    mat[2][3]=Position.z;

    return mat;
}
    
Mat4 Transform::calculateRotationMatrix() const {
    Quaternion normalized = Rotation.normalized();

    float x = normalized.v.x;
    float y = normalized.v.y;
    float z = normalized.v.z;
    float w = normalized.v.w;

    float xx = x * x, yy = y * y, zz = z * z;
    float xy = x * y, xz = x * z, yz = y * z;
    float wx = w * x, wy = w * y, wz = w * z;

    Mat4 mat{}; 

 
    mat[0][0] = 1.0f - 2.0f * (yy + zz);
    mat[0][1] = 2.0f * (xy - wz);  
    mat[0][2] = 2.0f * (xz + wy);
    mat[0][3] = 0.0f;

    mat[1][0] = 2.0f * (xy + wz);
    mat[1][1] = 1.0f - 2.0f * (xx + zz);
    mat[1][2] = 2.0f * (yz - wx);
    mat[1][3] = 0.0f;

    mat[2][0] = 2.0f * (xz - wy);
    mat[2][1] = 2.0f * (yz + wx);
    mat[2][2] = 1.0f - 2.0f * (xx + yy);
    mat[2][3] = 0.0f;

    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;

    return mat;
}

Mat4 Transform::calculateScaleMatrix() const{
    Mat4 mat{};

    mat[0][0]=Scale.x;
    mat[1][1]=Scale.y;
    mat[2][2]=Scale.z;
    mat[3][3]=1;

    return mat;
}

void Transform::markDirty(){
    isLocalMatrixDirty = true;
    isWorldMatrixDirty = true;

    for(node* c:this->getParent()->getChildsByType<node>()){
        Transform* t=c->getChildByType<Transform>();
        if(t!=nullptr && t!=this){
            t->markDirty();
        }
    }
}

}