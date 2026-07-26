#pragma once
#include "ObjectManager.hpp"
#include "TaskManager.hpp"
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

    bool isSceneActive(unsigned int sceneId);
    bool activateScene(unsigned int sceneId);
    bool deactivateScene(unsigned int sceneId);
    
    std::vector<scene*>& getActiveScenes();
    
    unsigned int addScene(scene* Scene);

    void changeWindowRatio(float ratio);

    int run();

private:
    App();
    ~App();

    GLFWwindow* window;
    Render::ShaderProgram* shaderProgram;
    std::vector<scene*> scenes;
    std::vector<scene*> activeScenes;

    float  screenRatio;
    char   initLog=0b00000000;
    //glfwInit - window init - gladLoad

    bool fault=false;
    char* faultLog=nullptr;
};
}
