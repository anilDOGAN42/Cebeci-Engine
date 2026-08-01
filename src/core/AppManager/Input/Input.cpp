#include "Input.hpp"
#include "GLFW/glfw3.h"


namespace CebeciEngine::Core::App::Input {
Input& Input::instance() {
    static Input i;
    return i;
}

void Input::init(GLFWwindow* window) {
    this->window=window;
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorCallback);
}

void Input::update() {
    inputMutex.lock();

    previousKeys=tempPreviousKeys;
    prevMouseX=tempPrevMouseX;
    prevMouseY=tempPrevMouseY;

    tempPreviousKeys = currentKeys;
    tempPrevMouseX = mouseX;
    tempPrevMouseY = mouseY;

    inputMutex.unlock();
}

bool Input::isKeyDown(int key) {
    inputMutex.lock();
    bool down = currentKeys[key];
    inputMutex.unlock();

    return down;
}

bool Input::isKeyPressed(int key) {
    inputMutex.lock();
    bool pressed = currentKeys[key] && !previousKeys[key];
    inputMutex.unlock();

    return pressed;
}

bool Input::isKeyReleased(int key) {
    inputMutex.lock();
    bool released = !currentKeys[key] && previousKeys[key];
    inputMutex.unlock();

    return released;
}

double Input::getMouseX() {
    inputMutex.lock();
    double mX = mouseX; 
    inputMutex.unlock();
    return mX;

}

double Input::getMouseY() {
    inputMutex.lock();
    double mY = mouseY; 
    inputMutex.unlock();
    return mY;
}

double Input::getMouseDX() { 
    inputMutex.lock();
    double DX = mouseX - prevMouseX;
    inputMutex.unlock();
    return DX;
}
double Input::getMouseDY() { 
    inputMutex.lock();
    double DY = mouseY - prevMouseY;
    inputMutex.unlock();
    return DY;
}

void Input::lockMouse(){
    glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);
}
void Input::freeMouse(){
    glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_NORMAL);
}

void Input::keyCallback(GLFWwindow*, int key, int, int action, int) {
    if (action == GLFW_PRESS)
        instance().currentKeys[key] = true;
    else if (action == GLFW_RELEASE)
        instance().currentKeys[key] = false;
}

void Input::cursorCallback(GLFWwindow*, double xpos, double ypos) {
    Input& input=instance();
    
    input.inputMutex.lock();
    input.mouseX = xpos;
    input.mouseY = ypos;
    input.inputMutex.unlock();
}
}