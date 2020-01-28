//
// Created by jake on 1/24/20.
//

#include "Window.h"



void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Window* user = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(key == GLFW_KEY_UNKNOWN) return; //guard against out of bounds

    if(action == GLFW_PRESS) {
        user->keysPressed[key] = true;
    } else if(action == GLFW_RELEASE) {
        user->keysPressed[key] = false;
    }
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
    Window* user = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(action == GLFW_PRESS) {
        user->mouseButtonsPressed[button] = true;
    } else if(action == GLFW_RELEASE) {
        user->mouseButtonsPressed[button] = false;
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    Window* user = static_cast<Window*>(glfwGetWindowUserPointer(window));

    user->mousePos = glm::vec2(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Window* user = static_cast<Window*>(glfwGetWindowUserPointer(window));

    user->scrollOffset = glm::vec2(xoffset, yoffset);
}

Window::Window(int width, int height, const std::string &title, bool resizeable)
    :width(width), height(height), title(title), resizeable(resizeable) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, this->resizeable);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    for(auto& e : keysPressed) e = false;
    for(auto& e : mouseButtonsPressed) e = false;
    //TODO: mouse shit

    this->windowHandle = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (this->windowHandle == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Opengl rejected window creation of a " + std::to_string(width) +
                                 +"x" + std::to_string(height) + " window with title " + title);
    }

    this->bind();

    glfwSetFramebufferSizeCallback(this->windowHandle, framebuffer_size_callback);
    glfwSetMouseButtonCallback(this->windowHandle, mouse_callback);
    glfwSetCursorPosCallback(this->windowHandle, cursor_position_callback);
    glfwSetScrollCallback(this->windowHandle, scroll_callback);

    glfwSetKeyCallback(Window::windowHandle, key_callback);
    glfwSetWindowUserPointer(this->windowHandle, this);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("GLAD failed to load");
    }

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    this->unbind();

    previousFrameTime = glfwGetTime();
}

void Window::bind() {
    glfwMakeContextCurrent(windowHandle);
}

void Window::unbind() {
    glfwMakeContextCurrent(0);
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setBackgroundColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Window::update() {
    glfwSwapBuffers(windowHandle);


    previousFrameTime = currentFrameTime;
    currentFrameTime = glfwGetTime();
    //its okay to be here, because callbacks are called upon poll events anyways
    prevMousePos = mousePos;
    scrollOffset = glm::vec2(0, 0);
    glfwPollEvents();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(windowHandle);
}

Window::~Window() {
    glfwTerminate();
}

bool Window::isKeyPressed(int key) {
    return keysPressed[key];
}

glm::vec2 Window::getMousePos() {
    return mousePos;
}

glm::vec2 Window::getDeltaMousePos() {
    return (mousePos - prevMousePos);
}

glm::vec2 Window::getMouseScroll() {
    return scrollOffset;
}

void Window::hideCursor() {
    glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

double Window::getTimeForLastFrame() {
    return currentFrameTime - previousFrameTime;
}


