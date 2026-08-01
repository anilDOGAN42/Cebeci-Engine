#include "application.hpp"
#include "ObjectManager.hpp"
#include "Task.hpp"
#include "TaskManager.hpp"
#include "Thread.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "Input.hpp"
#include "stbi_impl.hpp"
#include <iostream>
#include <vector>

using namespace CebeciEngine::Render;
using CebeciEngine::Core::App::Object::ObjectManager;
TaskManager& taskManager=TaskManager::instance();
ObjectManager& objectManager=ObjectManager::instance();
namespace CebeciEngine::Core::App {

App::App()=default;
App::~App()=default;

App& App::instance() {
    static App instance;
    return instance;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    App::instance().changeScreenRatio((float)width/(float)height);
}

void App::changeScreenRatio(float ratio){
    screenRatio=ratio;
}

void App::init(char* name,int windowWidth,int windowHeight){
    
    if (glfwInit()) {
        initLog = initLog | 0b10000000;
    }

    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
    window = glfwCreateWindow(windowWidth, windowHeight, name, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        
    }
    else{
        initLog = initLog | 0b01000000;
        glfwMakeContextCurrent(window);
    }

    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        initLog = initLog | 0b00100000;
    }

    if(initLog & 0b11100000){
        glViewport(0,0,windowWidth,windowHeight);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

    }

    screenRatio=(float)windowWidth/(float)windowHeight;
    Input::Input::instance().init(window);
    
    stbi_init();
    taskManager.initMainThread();

}

float App::getScreenRatio(){
    return screenRatio;
}

unsigned int App::addScene(scene* Scene){
    scenes.push_back(Scene);
    return scenes.size()-1;
}

bool App::isSceneActive(unsigned int sceneId){
    activeScenesMutex.lock();
    for(scene* Scene: activeScenes)
        if(Scene->id==sceneId){
            activeScenesMutex.unlock();
            return true;
        }
    activeScenesMutex.unlock();
    return false;
}

bool App::activateScene(unsigned int sceneId){
    if(sceneId>=scenes.size() || isSceneActive(sceneId)) return false;

    activeScenesMutex.lock();
    activeScenes.push_back(scenes.at(sceneId));
    activeScenesMutex.unlock();

    return true;
}
bool App::deactivateScene(unsigned int sceneId){
    if(isSceneActive(sceneId)){
        activeScenesMutex.lock();
        for(unsigned int i=0;i<activeScenes.size();i++)
            if(activeScenes.at(i)->id==sceneId)
                activeScenes.erase(activeScenes.begin()+i);
        
        activeScenesMutex.unlock();
        return true;
    }else{
        return false;
    }
}
std::vector<scene*>& App::getActiveScenes(){
    return activeScenes;
}

unsigned int App::getShaderProgramID(){
    return shaderProgram->id;
}

int App::run(){
    if(fault) return 1;
    Input::Input& input= Input::Input::instance();
    if(initLog & 0b11100000){
        Shader* VertexShader=new Shader(GL_VERTEX_SHADER,(char*)"./shaders/vs.glsl");
        Shader* FragmentShader=new Shader(GL_FRAGMENT_SHADER,(char*)"./shaders/fs.glsl");

        VertexShader->createShader();
        FragmentShader->createShader();

        VertexShader->compileShader();
        FragmentShader->compileShader();

        shaderProgram= new ShaderProgram;

        shaderProgram->attachShader(VertexShader->id);
        shaderProgram->attachShader(FragmentShader->id);

        shaderProgram->linkProgram();
            
        shaderProgram->use();

        delete VertexShader;
        delete FragmentShader;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glfwSwapBuffers(window);
        glfwPollEvents();

        while (!glfwWindowShouldClose(window) && !fault) {
            glClearColor(0.0f, 0.5f, 0.7f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            input.update();

            for(Task::Task* task:taskManager.MainThreadTasks){
                task->run();
            }
    
            activeScenes[0]->drawScene();    

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        if(fault){
            if(faultLog!=nullptr)
            std::cerr<<faultLog;
        }

        taskManager.deleteAllThreads();
        objectManager.deleteAllObjects();

        delete shaderProgram;

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }
    else{
        return -1;
    }
}
}

