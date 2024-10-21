#include <iostream>
#include "include/Engine.hpp"

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

    SystemFunctor<Position> moveForward([](auto components) {
        Component *first = components[0];
        auto *position = dynamic_cast<Position *>(first);
        position->x()++;
    });

    engine.resizeComponentStorage();
}