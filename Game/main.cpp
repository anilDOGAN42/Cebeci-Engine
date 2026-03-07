#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Mesh.hpp"
#include "TaskManager/Task.hpp"
#include "camera.hpp"
#include "glm/fwd.hpp"
#include "texture.hpp"
#include "vertex.hpp"
#include "node.hpp"
#include "scene.hpp"
#include "application.hpp"
#include "Input.hpp"
#include "texture.hpp"

static bool a=false,b=false;

static App& app=App::instance();

static scene* sahne=new scene;
static scene* sahne2=new scene;

static node* obje1=nullptr;
static node* obje2=nullptr;

static node* sahne2obje1=nullptr;

void startFunction1(double){
    camera3D* cam= new camera3D(100.0f);

    cam->camPosition={0,0,-3};
    if(obje1==nullptr)
        obje1=new node;
    if(obje2==nullptr)
        obje2=new node;

    cam->calculate();

    Texture2D* doku= new Texture2D((char*)"./textures/doku2.png");

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

    obje1->changeMesh(obje1Mesh);

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
    camera3D* cam= new camera3D(100.0f);

    cam->camPosition={0,0,-3};
    if(sahne2obje1==nullptr)
        sahne2obje1=new node;

    cam->calculate();

    Texture2D* doku= new Texture2D((char*)"./textures/doku2.png");

    std::vector<vertex> mesh={
        vertex{{-0.5,-0.5,-0.5},{0,0}},
        vertex{{-0.5,0.5,-0.5},{0,1}},
        vertex{{0.5,-0.5,-0.5},{1,0}},
        vertex{{-0.5,0.5,-0.5},{0,1}},
        vertex{{0.5,0.5,-0.5},{1,1}},
        vertex{{0.5,-0.5,-0.5},{1,0}},

        
        vertex{{0,0,0},{0,0}},
        vertex{{0,1,0},{0,1}},
        vertex{{0,0,1},{1,0}},
        vertex{{0,1,0},{0,1}},
        vertex{{0,1,1},{1,1}},
        vertex{{0,0,1},{1,0}},

        
        vertex{{0,0,0},{0,0}},
        vertex{{0,0,1},{0,1}},
        vertex{{1,0,0},{1,0}},
        vertex{{0,0,1},{0,1}},
        vertex{{1,0,1},{1,1}},
        vertex{{1,0,0},{1,0}},


        vertex{{0,1,0},{0,0}},
        vertex{{0,1,1},{0,1}},
        vertex{{1,1,0},{1,0}},
        vertex{{0,1,1},{0,1}},
        vertex{{1,1,1},{1,1}},
        vertex{{1,1,0},{1,0}},


        vertex{{0,0,1},{0,0}},
        vertex{{0,1,1},{0,1}},
        vertex{{1,0,1},{1,0}},
        vertex{{0,1,1},{0,1}},
        vertex{{1,1,1},{1,1}},
        vertex{{1,0,1},{1,0}},

        
        vertex{{1,0,0},{0,0}},
        vertex{{1,1,0},{0,1}},
        vertex{{1,0,1},{1,0}},
        vertex{{1,1,0},{0,1}},
        vertex{{1,1,1},{1,1}},
        vertex{{1,0,1},{1,0}},

    };

    sahne2obje1->changeMesh(new Mesh(mesh));
    sahne2obje1->getMesh()->changeTexture(doku);

    sahne2->addNode(sahne2obje1);

    sahne2->setCamera(cam);
}

void cameraUpdate(double deltaTime) {
    Input& input = Input::instance();
    camera* cam = app.getActiveScene().getActiveCamera();

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
    App& app=App::instance();
    auto& input = Input::instance();
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
    Input& input=Input::instance();

    if (input.isKeyDown(GLFW_KEY_Z)){
        obje1->getTransform()->Rotation=vec3(0,0,0);
        obje2->getTransform()->Rotation=vec3(0,0,0);
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


int main() {
    app.init((char*)"Game", 800, 800);

    startTask* startTask1= new startTask(startFunction1,true);
    startTask* startTask2= new startTask(startFunction2,true);


    updateTask* cameraUpdateTask = new updateTask(cameraUpdate,true);
    updateTask* updateSceneTask =new updateTask(updateScene,true);
    
    updateTask* updateObje1RotationTask=new updateTask(updateObje1Rotation,true);

    sahne->addStartTask(startTask1);
    sahne->addUpdateTask(cameraUpdateTask);
    sahne->addUpdateTask(updateSceneTask);
    sahne->addUpdateTask(updateObje1RotationTask);

    sahne2->addStartTask(startTask2);
    sahne2->addUpdateTask(cameraUpdateTask);
    sahne2->addUpdateTask(updateSceneTask);
    
    app.addScene(sahne);
    app.addScene(sahne2);

    app.run();
    return 0;
}
