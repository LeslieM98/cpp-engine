//
// Created by Leslie on 09.11.2024.
//
#include <iostream>


#include "Window.hpp"


using namespace fimbulwinter::engine;

Window::Window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->windowHandle.reset(glfwCreateWindow(800, 600, "Fimbulwinter Engine", nullptr, nullptr));
    if (windowHandle == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(windowHandle.get());
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glViewport(0, 0, 800, 600);
}

Window::~Window() {
    glfwTerminate();
}
