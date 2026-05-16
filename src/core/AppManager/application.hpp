#pragma once
#include "ObjectManager.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "vector"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//forward declaration
namespace CebeciEngine::Core{
    namespace App::Object{class ObjectManager;}
    class scene;
}
namespace CebeciEngine::Core::App {
class App{
public:

    static App& instance();

    void init(char* name,int windowWidth,int windowHeight);

    App(const App&) = delete;
    App& operator=(const App&) = delete;


    unsigned int getShaderProgramID();

    float getScreenRatio();

    void setActiveScene(int sceneId);
    scene* getActiveScene();
    
    void addScene(scene* Scene);

    void changeWindowRatio(float ratio);

    int run();

private:
    App();
    ~App();

    CebeciEngine::Core::App::Object::ObjectManager *objectManager;

    GLFWwindow* window;
    Render::ShaderProgram* shaderProgram;
    std::vector<scene*> scenes;
    
    scene* activeScene;
    float  screenRatio;
    char   initLog=0b00000000;
    //glfwInit - window init - gladLoad
};
}
