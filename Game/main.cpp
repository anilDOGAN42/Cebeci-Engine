#include "Mesh.hpp"
#include "TaskManager.hpp"
#include "Thread.hpp"
#include "camera.hpp"
#include "node.hpp"
#include "scene.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include <CebeciEngine.hpp>
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
static transform* ObjeTransform;

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

class AThreadTask:public Task{
    void Update(double deltaTime) override{
        cam->lock();
        cam->camPosition.z+=1*deltaTime;
        cam->calculate();
        cam->unlock();
    }
};

class initTask:public Task{
public:
    void Init() override{
        Obje=new node();
        objeMesh=new Mesh(mesh);

        Texture::Texture2D* texture=new Texture::Texture2D((char*)"./textures/doku1.png");
        objeMesh->changeTexture(texture);

        ObjeTransform=new transform();
        Obje->addComponent(texture);

        ObjeTransform->Position={0,0,0};
        ObjeTransform->Rotation={0,0,0};
        ObjeTransform->Scale={1,1,1};

        cam=new Camera::camera3D(100.0f,45.0f);

        cam->camPosition={0,0,-3};
        cam->camRotation={0,0,0};

        cam->calculate();

        Obje->addComponent(objeMesh);
        Obje->addComponent(ObjeTransform);

        sahne->addNode(Obje);
        sahne->setCamera(cam);
        
        TaskManager& taskManager=TaskManager::instance();

        AThreadTask *task=new AThreadTask;
        task->activate();

        Threading::Thread* thread=taskManager.createThread("A");
        taskManager.addTaskToThread(task,thread->getId());

    }

    void Update(double deltaTime) override{
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
