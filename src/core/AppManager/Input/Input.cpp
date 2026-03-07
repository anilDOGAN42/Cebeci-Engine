#include "Input.hpp"
#include "GLFW/glfw3.h"
#include <iostream>

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

    previousKeys=tempPreviousKeys;
    prevMouseX=tempPrevMouseX;
    prevMouseY=tempPrevMouseY;

    tempPreviousKeys = currentKeys;
    tempPrevMouseX = mouseX;
    tempPrevMouseY = mouseY;

}

bool Input::isKeyDown(int key) {
    return currentKeys[key];
}

bool Input::isKeyPressed(int key) {
    return currentKeys[key] && !previousKeys[key];
}

bool Input::isKeyReleased(int key) {
    return !currentKeys[key] && previousKeys[key];
}

double Input::getMouseX() {
    return mouseX; 
}

double Input::getMouseY() {
    return mouseY; 
}

double Input::getMouseDX() { 
    double DX = mouseX - prevMouseX;
    return DX;
}
double Input::getMouseDY() { 
    double DY = mouseY - prevMouseY;
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
    instance().mouseX = xpos;
    instance().mouseY = ypos;
}
