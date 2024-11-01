#include <iostream>
#include "include/Engine.hpp"
#include "Component.hpp"
#include "System.hpp"
#include "Health.hpp"
#include "Position.hpp"

using namespace fimbulwinter::engine;

int main() {
    Engine engine;

    std::cout << engine.instanciateEntity({new Health(10, 10)}) << std::endl;
    std::cout << engine.instanciateEntity({new Position(1, 2, 3)}) << std::endl;
    std::cout << engine.instanciateEntity({new Position(1, 2, 3), new Health(10, 9)}) << std::endl;

    engine.registerSystem(new SystemFunctor<Position>([](auto components) {
        auto *position = dynamic_cast<Position *>(components.front());
        position->x()++;
        std::cout << position->x() << ", " << position->y() << ", " << position->z() << std::endl;
    }));
    engine.registerSystem(new SystemFunctor<Position>([](auto components) {
        auto *position = dynamic_cast<Position *>(components.front());
        std::cout << position->x() << ", " << position->y() << ", " << position->z() << std::endl;
    }));

    engine.tick();
    engine.tick();
}