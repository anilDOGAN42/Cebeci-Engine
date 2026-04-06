#pragma once
#include "scene.hpp"
#include "shader.hpp"
#include "vector"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class App{
public:

    static App& instance();

    void init(char* name,int windowWidth,int windowHeight);

    App(const App&) = delete;
    App& operator=(const App&) = delete;


    unsigned int getShaderProgramID();

    float getScreenRatio();

    void setActiveScene(int sceneId);
    scene getActiveScene();
    
    void addScene(scene* Scene);

    void changeWindowRatio(float ratio);

    int run();

private:
    App();
    ~App();

    GLFWwindow* window;
    ShaderProgram* shaderProgram;
    std::vector<scene*> scenes;
    
    scene* activeScene;
    float  screenRatio;
    char   initLog=0b00000000;
    //glfwInit - window init - gladLoad
};