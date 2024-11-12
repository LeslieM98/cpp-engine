#include <iostream>
#include "include/Engine.hpp"
#include "Window.hpp"
#include "include/Health.hpp"
#include "include/Position.hpp"

using namespace fimbulwinter::engine;
using namespace std::chrono_literals;

int main() {
    Engine engine;

    std::cout << engine.instanciateEntity({new Health(10, 10)}) << std::endl;
    std::cout << engine.instanciateEntity({new Position(1, 2, 3)}) << std::endl;
    std::cout << engine.instanciateEntity({new Position(1, 2, 3), new Health(10, 9)}) << std::endl;

    engine.registerSystem(new SystemFunctor<Position>([](auto components) {
        auto *position = dynamic_cast<Position *>(components.front());
        position->x()++;
    }));

    engine.registerSystem(new SystemFunctor<Position>([](auto components) {
        auto *position = dynamic_cast<Position *>(components.front());
        std::cout << position->x() << ", " << position->y() << ", " << position->z() << std::endl;
    }, SubStage::POST));

    engine.tick();
    engine.tick();

    engine.run();
    std::this_thread::sleep_for(2s);
    engine.terminate();
    Window::terminate();
}