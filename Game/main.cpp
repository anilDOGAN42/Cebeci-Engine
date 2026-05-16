#include "Task.hpp"
#include <CebeciEngine.hpp>
#include <vector>
#include <glm/fwd.hpp>

using namespace CebeciEngine;
using namespace CebeciEngine::Core;
using namespace CebeciEngine::Render;

static bool a=false,b=false;

static App::App* app;

static scene* sahne;
static scene* sahne2;

static node* obje1=nullptr;
static node* obje2=nullptr;

static node* sahne2obje1=nullptr;

void startFunction1(double){
    Camera::camera3D* cam= new Camera::camera3D(100.0f,45.0f);

    cam->camPosition={0,0,-3};
    if(obje1==nullptr)
        obje1=new node;
    if(obje2==nullptr)
        obje2=new node;

    obje1->name="obje1";
    obje2->name="obje2";

    cam->calculate();

    Texture::Texture2D* doku= new Texture::Texture2D((char*)"./textures/doku2.png");

    std::vector<vertex> mesh={
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

    Mesh* obje1Mesh = new Mesh(mesh);
    obje1Mesh->changeTexture(doku);

    obje1Mesh->name="mesh";

    obje1->changeMesh(obje1Mesh);
    App::Object::ObjectManager& objectManager=
    App::Object::ObjectManager::instance();

    Mesh* obje2Mesh = new Mesh(mesh);
    obje2Mesh->changeTexture(doku);

    obje2->changeMesh(obje2Mesh);

    obje2->setParent(obje1);

    obje2->getTransform()->Position={3,0,0};

    sahne->addNode(obje1);
    sahne->addNode(obje2);

    sahne->setCamera(cam);
}

void startFunction2(double){
    Camera::camera2D* cam= new Camera::camera2D(1.0f*(app->getScreenRatio()),-1.0f*(app->getScreenRatio()),1.0f,-1.0f,10.0f);

    cam->camPosition={0,0,-3};
    if(sahne2obje1==nullptr)
        sahne2obje1=new node;

    cam->calculate();

    Texture::Texture2D* doku= new Texture::Texture2D((char*)"./textures/doku2.png");

    sahne2obje1->changeMesh(App::Object::ObjectManager::instance().getObject<Mesh>("mesh"));
    sahne2obje1->getMesh()->changeTexture(doku);

    sahne2->addNode(sahne2obje1);

    sahne2->setCamera(cam);
}

void cameraUpdate(double deltaTime) {
    App::Input::Input& input = App::Input::Input::instance();
    Camera::camera* cam = app->getActiveScene()->getActiveCamera();

    float speed = 1.5f;

    glm::vec3 camRotation=cam->camRotation;
    glm::vec3 camPosition=cam->camPosition;

    glm::vec3 forward,right;

    float pitch = glm::radians(camRotation.x);
    float yaw   = glm::radians(camRotation.y);

    forward.x = cos(pitch) * sin(yaw);
    forward.y = sin(pitch);
    forward.z = cos(pitch) * cos(yaw);

    forward = glm::normalize(forward);

    right = glm::normalize(glm::cross(forward, glm::vec3(0,1,0)));

    if(input.isKeyPressed(GLFW_KEY_ESCAPE)){
        if(b){
            b=false;
            input.lockMouse();
        }
        else{
            b=true;
            input.freeMouse();
        }
    }
    if (input.isKeyDown(GLFW_KEY_LEFT_SHIFT)){
        speed*=3;
    } 
    if (input.isKeyDown(GLFW_KEY_W)){
        cam->camPosition += forward * (float)(speed * deltaTime);
    } 
    if (input.isKeyDown(GLFW_KEY_S)){
        cam->camPosition -= forward * (float)(speed * deltaTime);
    }
    if (input.isKeyDown(GLFW_KEY_A)){

        cam->camPosition -= right * (float)(speed * deltaTime);
    }
    if (input.isKeyDown(GLFW_KEY_D)){
        cam->camPosition += right * (float)(speed * deltaTime);
    }

    cam->camRotation.y -= input.getMouseDX() * deltaTime*2;
    cam->camRotation.x -= input.getMouseDY() * deltaTime*2;

    cam->calculate();
}

void updateScene(double deltaTime){
    App::App& app=App::App::instance();
    auto& input = App::Input::Input::instance();
    if(input.isKeyPressed(GLFW_KEY_BACKSPACE))
    {
        if(!a){
            a=true;
            app.setActiveScene(1);

        }
        else{
            a=false;
            app.setActiveScene(0);
        }
    }

}

void updateObje1Rotation(double deltaTime){
    App::Input::Input& input=App::Input::Input::instance();

    if (input.isKeyDown(GLFW_KEY_Z)){
        obje1->getTransform()->Rotation={0,0,0};
        obje2->getTransform()->Rotation={0,0,0};
    }

    if (input.isKeyDown(GLFW_KEY_UP)){
        obje1->getTransform()->Rotation.z+=10*deltaTime;
    }
    if (input.isKeyDown(GLFW_KEY_DOWN)){
        obje1->getTransform()->Rotation.z-=10*deltaTime;
    }
    if (input.isKeyDown(GLFW_KEY_LEFT)){
        obje1->getTransform()->Rotation.y+=10*deltaTime;
    }
    if (input.isKeyDown(GLFW_KEY_RIGHT)){
        obje1->getTransform()->Rotation.y-=10*deltaTime;
    }
    if (input.isKeyDown(GLFW_KEY_Q)){
        obje1->getTransform()->Rotation.x+=10*deltaTime;
    }
    if (input.isKeyDown(GLFW_KEY_E)){
        obje1->getTransform()->Rotation.x-=10*deltaTime;
    }
}

void updateScene2Camera(double deltaTime){
    App::Input::Input& input = App::Input::Input::instance();
    Camera::camera* cam = app->getActiveScene()->getActiveCamera();
    
    float speed = 1.5f;

    float velocity = speed * (float)deltaTime;

    if (input.isKeyDown(GLFW_KEY_LEFT_SHIFT)){
        speed*=3;
    } 
    if (input.isKeyDown(GLFW_KEY_W)){
        cam->camPosition.y += velocity;
    } 
    if (input.isKeyDown(GLFW_KEY_S)){
        cam->camPosition.y -= velocity;
    }
    if (input.isKeyDown(GLFW_KEY_A)){

        cam->camPosition.x += velocity;
    }
    if (input.isKeyDown(GLFW_KEY_D)){
        cam->camPosition.x -= velocity;
    }

    cam->calculate();
}

int main() {
    app=&App::App::instance();

    app->init((char*)"Game", 800, 800);


    startTask* startTask1= new startTask(startFunction1,true);
    startTask* startTask2= new startTask(startFunction2,true);


    updateTask* cameraUpdateTask = new updateTask(cameraUpdate,true);
    updateTask* updateSceneTask = new updateTask(updateScene,true);
    
    updateTask* updateObje1RotationTask=new updateTask(updateObje1Rotation,true);

    updateTask* updateScene2CameraTask=new updateTask(updateScene2Camera,true);

    sahne=new scene;
    sahne2=new scene;

    sahne->addStartTask(startTask1);
    sahne->addUpdateTask(cameraUpdateTask);
    sahne->addUpdateTask(updateSceneTask);
    sahne->addUpdateTask(updateObje1RotationTask);

    sahne2->addStartTask(startTask2);
    sahne2->addUpdateTask(updateScene2CameraTask);
    sahne2->addUpdateTask(updateSceneTask);
    
    app->addScene(sahne);
    app->addScene(sahne2);

    app->run();
    return 0;
}
