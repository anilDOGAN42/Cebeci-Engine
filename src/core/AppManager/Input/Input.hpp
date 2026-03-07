#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

class Input {
public:
    static Input& instance();

    void init(GLFWwindow* window);
    void update();

    void lockMouse();
    void freeMouse();

    bool isKeyDown(int key);
    bool isKeyPressed(int key);
    bool isKeyReleased(int key);

    double getMouseX();
    double getMouseY();
    double getMouseDX();
    double getMouseDY();

private:
    Input() = default;

    GLFWwindow* window;


    static void keyCallback(GLFWwindow*, int key, int scancode, int action, int mods);
    static void cursorCallback(GLFWwindow*, double xpos, double ypos);

    std::unordered_map<int, bool> currentKeys;
    std::unordered_map<int, bool> tempPreviousKeys;
    std::unordered_map<int, bool> previousKeys;

    double mouseX = 0, mouseY = 0;
    double prevMouseX = 0, prevMouseY = 0;
    double tempPrevMouseX = 0, tempPrevMouseY = 0;
};
