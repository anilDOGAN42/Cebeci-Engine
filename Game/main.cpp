#include <CebeciEngine.hpp>
#include "Input.hpp"
#include "Mesh.hpp"
#include "Task.hpp"
#include "TaskManager.hpp"
#include "Thread.hpp"
#include "camera.hpp"
#include "node.hpp"
#include "scene.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include <iostream>
#include <vector>
#include <glm/fwd.hpp>

using namespace CebeciEngine;
using namespace CebeciEngine::Core;
using namespace CebeciEngine::Render;
using namespace std::chrono_literals;

static bool a=false,b=false;

static App::App* app;

static Camera::camera3D* cam;

static scene* sahne;

static node* Obje;
static Mesh* objeMesh;

static std::vector<vertex> mesh={
        vertex{{-0.5,-0.5,-0.5},{0,0}},
        vertex{{-0.5,0.5,-0.5},{0,1}},
        vertex{{0.5,-0.5,-0.5},{1,0}},
        vertex{{-0.5,0.5,-0.5},{0,1}},
        vertex{{0.5,0.5,-0.5},{1,1}},
        vertex{{0.5,-0.5,-0.5},{1,0}},

        
        vertex{{-0.5,-0.5,-0.5},{0,0}},
        vertex{{-0.5,0.5,-0.5},{0,1}},
        vertex{{-0.5,-0.5,0.5},{1,0}},
        vertex{{-0.5,0.5,-0.5},{0,1}},
        vertex{{-0.5,0.5,0.5},{1,1}},
        vertex{{-0.5,-0.5,0.5},{1,0}},

        
        vertex{{-0.5,-0.5,-0.5},{0,0}},
        vertex{{-0.5,-0.5,0.5},{0,1}},
        vertex{{0.5,-0.5,-0.5},{1,0}},
        vertex{{-0.5,-0.5,0.5},{0,1}},
        vertex{{0.5,-0.5,0.5},{1,1}},
        vertex{{0.5,-0.5,-0.5},{1,0}},


        vertex{{-0.5,0.5,-0.5},{0,0}},
        vertex{{-0.5,0.5,0.5},{0,1}},
        vertex{{0.5,0.5,-0.5},{1,0}},
        vertex{{-0.5,0.5,0.5},{0,1}},
        vertex{{0.5,0.5,0.5},{1,1}},
        vertex{{0.5,0.5,-0.5},{1,0}},


        vertex{{-0.5,-0.5,0.5},{0,0}},
        vertex{{-0.5,0.5,0.5},{0,1}},
        vertex{{0.5,-0.5,0.5},{1,0}},
        vertex{{-0.5,0.5,0.5},{0,1}},
        vertex{{0.5,0.5,0.5},{1,1}},
        vertex{{0.5,-0.5,0.5},{1,0}},

        
        vertex{{0.5,-0.5,-0.5},{0,0}},
        vertex{{0.5,0.5,-0.5},{0,1}},
        vertex{{0.5,-0.5,0.5},{1,0}},
        vertex{{0.5,0.5,-0.5},{0,1}},
        vertex{{0.5,0.5,0.5},{1,1}},
        vertex{{0.5,-0.5,0.5},{1,0}},

};
class CameraUpdate:public Task{
public:
    void Update(double deltaTime) override{
        App::Input::Input& input = App::Input::Input::instance();

        float speed = 1.5f;

        cam->lock();
        glm::vec3 camRotation=cam->camRotation;
        glm::vec3 camPosition=cam->camPosition;
        cam->unlock();

        glm::vec3 forward,right;

        float pitch = glm::radians(camRotation.x);
        float yaw   = glm::radians(camRotation.y);

        forward.x = cos(pitch) * sin(yaw);
        forward.y = sin(pitch);
        forward.z = cos(pitch) * cos(yaw);

        forward = glm::normalize(forward);

        right = glm::normalize(glm::cross(forward, glm::vec3(0,1,0)));

        if(input.isKeyPressed(KEY_ESCAPE)){
            if(b){
                b=false;
                input.lockMouse();
            }
            else{
                b=true;
                input.freeMouse();
            }
        }
        if (input.isKeyDown(KEY_LEFT_SHIFT)){
            speed*=3;
        } 
        if (input.isKeyDown(KEY_W)){
            cam->lock();
            cam->camPosition += forward * (float)(speed * deltaTime);
            cam->unlock();
        } 
        if (input.isKeyDown(KEY_S)){
            cam->lock();
            cam->camPosition -= forward * (float)(speed * deltaTime);
            cam->unlock();
        }
        if (input.isKeyDown(KEY_A)){
            cam->lock();
            cam->camPosition -= right * (float)(speed * deltaTime);
            cam->unlock();
        }
        if (input.isKeyDown(KEY_D)){
            cam->lock();
            cam->camPosition += right * (float)(speed * deltaTime);
            cam->unlock();
        }

        cam->lock();
        cam->camRotation.y -= input.getMouseDX() * deltaTime*2;
        cam->camRotation.x -= input.getMouseDY() * deltaTime*2;

        cam->calculate();
        cam->unlock();
    }
};

class moveObject:public Task{
private:
    App::Input::Input& input= App::Input::Input::instance();

public:
    void Update(double deltaTime) override{
        node* obje=(node*)this->getParent();
        bool print=false;

        static bool removed=false;

        if (input.isKeyPressed(GLFW_KEY_O)){
            if(removed) {
                ((scene*)(obje->getParent()))->addChild(obje);
                std::cout<<"Added\n";
                removed=false;
            }else{
                ((scene*)(obje->getParent()))->removeChild(obje);
                std::cout<<"Removed\n";    
                removed=true;
            }
        }   

        if (input.isKeyDown(GLFW_KEY_Z)){
            obje->getChildByType<Transform>()->setRotation({0,0,0});
            print=true;
        }
        if (input.isKeyDown(GLFW_KEY_UP)){
            obje->getChildByType<Transform>()->RotateZ(10*deltaTime);
        }
        if (input.isKeyDown(GLFW_KEY_DOWN)){
            obje->getChildByType<Transform>()->RotateZ(-10*deltaTime);
            print=true;
        }
        if (input.isKeyDown(GLFW_KEY_LEFT)){
            obje->getChildByType<Transform>()->RotateY(10*deltaTime);
            print=true;
        }
        if (input.isKeyDown(GLFW_KEY_RIGHT)){
            obje->getChildByType<Transform>()->RotateY(-10*deltaTime);
            print=true;
        }
        if (input.isKeyDown(GLFW_KEY_Q)){
            obje->getChildByType<Transform>()->RotateX(10*deltaTime);
            print=true;
        }
        if (input.isKeyDown(GLFW_KEY_E)){
            obje->getChildByType<Transform>()->RotateX(-10*deltaTime);
            print=true;
        }

    }

};
class initTask:public Task{
public:
    void Init() override{
        Obje=new node();
        objeMesh=new Mesh(mesh);

        Texture::Texture2D* texture=new Texture::Texture2D((char*)"./textures/doku1.png");
        objeMesh->changeTexture(texture);

        Obje->addChild(texture);

        cam=new Camera::camera3D(100.0f,45.0f);

        cam->camPosition={0,0,-3};
        cam->camRotation={0,0,0};

        cam->calculate();

        Obje->addChild(objeMesh);

        moveObject* moveObjectTask=new moveObject;
        Obje->addChild(moveObjectTask);
        
        node* ObjeChild=new node{};
        ObjeChild->addChild(new Mesh(mesh));
        ObjeChild->getChildByType<Mesh>()->changeTexture(texture);

        ObjeChild->getChildByType<Transform>()->setPosition({-3,0,0});
        ObjeChild->getChildByType<Transform>()->setRotation({45,45,45});

        node* childChild=new node{};
        childChild->addChild(new Mesh(mesh));
        childChild->getChildByType<Mesh>()->changeTexture(texture);

        childChild->getChildByType<Transform>()->setPosition({-3,0,0});

        ObjeChild->addChild(childChild);

        Obje->addChild(ObjeChild);
        sahne->addChild(Obje);
        sahne->setCamera(cam);

        sahne->activate();
        
        TaskManager& taskManager=TaskManager::instance();

        CameraUpdate *task=new CameraUpdate;
        task->activate();

        taskManager.addTaskToMainThread(moveObjectTask);
        taskManager.addTaskToMainThread(task);

    }

};

int main() {
    app=&App::App::instance();

    app->init((char*)"Game", 800, 800);

    sahne=new scene();
    app->activateScene(app->addScene(sahne));
    initTask* InitTask=new initTask;
    InitTask->activate();
    TaskManager::instance().addTaskToMainThread(InitTask);
    
    app->run();

    return 0;
}
