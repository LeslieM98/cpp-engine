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

    engine.resizeComponentStorage();

    auto moveForward = std::make_unique<SystemFunctor<Position>>([](auto components) {
        Component *first = components[0];
        auto *position = dynamic_cast<Position *>(first);
        position->x()++;
    });
    auto printPos = std::make_unique<SystemFunctor<Position>>([](auto components) {
        Component *first = components[0];
        auto *position = dynamic_cast<Position *>(first);
        std::cout << position->x() << ", " << position->y() << ", " << position->z() << std::endl;
    });

    engine.registerSystem(std::move(moveForward));
    engine.registerSystem(std::move(printPos));

    engine.tick();
    engine.tick();
    engine.tick();
    engine.tick();
    engine.tick();
}