//
// Created by Leslie on 09.11.2024.
//

#ifndef FIMBULWINTERENGINE_WINDOW_HPP
#define FIMBULWINTERENGINE_WINDOW_HPP

#include <memory>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace fimbulwinter::engine {
    class Window {
        struct DestroyglfwWin {

            void operator()(GLFWwindow *ptr) {
                glfwDestroyWindow(ptr);
            }

        };

        static std::unique_ptr<Window> instance;

        std::unique_ptr<GLFWwindow, DestroyglfwWin> windowHandle;


    public:
        static Window &getInstance();

        Window();

        Window(Window &&o) = delete;

        Window(const Window &o) = delete;
    };
}

#endif //FIMBULWINTERENGINE_WINDOW_HPP
