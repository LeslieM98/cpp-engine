//
// Created by Leslie on 09.11.2024.
//

#ifndef FIMBULWINTERENGINE_WINDOW_HPP
#define FIMBULWINTERENGINE_WINDOW_HPP

#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace fimbulwinter::engine::core {
    class Window {
        struct DestroyglfwWin {

            void operator()(GLFWwindow *ptr) {
                glfwDestroyWindow(ptr);
            }

        };

        static std::unique_ptr<Window> instance;

        std::unique_ptr<GLFWwindow, DestroyglfwWin> windowHandle;


    public:

        Window();

        Window(Window &&o) = delete;

        Window(const Window &o) = delete;

        ~Window();
    };
}

#endif //FIMBULWINTERENGINE_WINDOW_HPP
