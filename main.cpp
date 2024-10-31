#include <iostream>
#include "include/Engine.hpp"
#include "Component.hpp"
#include "System.hpp"
#include "Health.hpp"
#include "Position.hpp"

using namespace fimbulwinter::engine;

int main() {
    Engine engine;

    std::unique_ptr<Component> health = std::make_unique<Health>(10, 9);
    std::vector<std::unique_ptr<Component>> components1;
    components1.emplace_back(std::move(health));

    std::unique_ptr<Component> pos = std::make_unique<Position>(1, 2, 3);
    std::vector<std::unique_ptr<Component>> components2;
    components2.emplace_back(std::move(pos));

    std::unique_ptr<Component> pos1 = std::make_unique<Position>(1, 2, 3);
    std::unique_ptr<Component> health1 = std::make_unique<Health>(10, 9);
    std::vector<std::unique_ptr<Component>> components3;
    components3.emplace_back(std::move(health1));
    components3.emplace_back(std::move(pos1));


    std::cout << engine.instanciateEntity(components1) << std::endl;
    std::cout << engine.instanciateEntity(components2) << std::endl;
    std::cout << engine.instanciateEntity(components3) << std::endl;

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