#include "application.hpp"
#include "TaskManager.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "Input.hpp"
#include "stbi_impl.hpp"

App::App(){}
App::~App(){
    //Destroy all of the objects and close the program normally. 
}

App& App::instance() {
    static App instance;
    return instance;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    App::instance().changeWindowRatio((float)width/(float)height);
}

void App::changeWindowRatio(float ratio){
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
    Input::instance().init(window);
    
    stbi_init();
}

float App::getScreenRatio(){
    return screenRatio;
}

void App::addScene(scene* Scene){
    scenes.push_back(Scene);
}

void App::setActiveScene(int sceneId){
    activeScene=scenes.data()[sceneId];
    TaskManager &taskManager=TaskManager::instance();
    taskManager.getActiveScenesTasks();
    taskManager.runStartTasks();

}
scene App::getActiveScene(){
    return *activeScene;
}

unsigned int App::getShaderProgramID(){
    return shaderProgram->id;
}

int App::run(){
    Input& input= Input::instance();
    if(initLog & 0b11100000){
        activeScene=scenes[0];

        Shader VertexShader(GL_VERTEX_SHADER,(char*)"./shaders/vs.glsl");
        Shader FragmentShader(GL_FRAGMENT_SHADER,(char*)"./shaders/fs.glsl");

        VertexShader.createShader();
        FragmentShader.createShader();

        VertexShader.compileShader();
        FragmentShader.compileShader();

        shaderProgram= new ShaderProgram;

        shaderProgram->attachShader(VertexShader.id);
        shaderProgram->attachShader(FragmentShader.id);

        shaderProgram->linkProgram();
            
        shaderProgram->use();

        TaskManager& taskManager=TaskManager::instance();

        taskManager.getActiveScenesTasks();
        taskManager.runStartTasks();

        while (!glfwWindowShouldClose(window)) {

            glClearColor(0.0f, 0.5f, 0.7f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            input.update();

            taskManager.runUpdateTasks();
        
            activeScene->drawScene();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        //Her şeyi delete et!

        delete shaderProgram;

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }
    else{
        return -1;
    }
}
