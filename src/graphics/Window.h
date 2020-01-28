//
// Created by jake on 1/24/20.
//

#ifndef DEBUG_WINDOW_H
#define DEBUG_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <mutex>
#include <stdexcept>
#include <array>

#define MAX_KEYS GLFW_KEY_LAST
#define MAX_MOUSE_BUTTONS GLFW_MOUSE_BUTTON_LAST

class Window {
private:
    int width, height;
    GLFWwindow *windowHandle;
    std::string title;
    bool resizeable;

    std::array<int, MAX_KEYS>  keysPressed;
    std::array<int, MAX_MOUSE_BUTTONS>  mouseButtonsPressed;

    glm::vec2 mousePos;
    glm::vec2 prevMousePos;

    glm::vec2 scrollOffset;

    double previousFrameTime;
    double currentFrameTime;
public:
    Window(int width, int height, const std::string &title, bool resizeable);
    ~Window();

    bool isKeyPressed(int key);
    glm::vec2 getMousePos();
    glm::vec2 getDeltaMousePos();
    glm::vec2 getMouseScroll();

    void bind();
    void unbind();
    void clear();
    void setBackgroundColor(float r, float g, float b, float a);
    void update();
    bool shouldClose();

    void hideCursor();
    double getTimeForLastFrame();

    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void mouse_callback(GLFWwindow* window, int button, int action, int mods);
    friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};


#endif //DEBUG_WINDOW_H
