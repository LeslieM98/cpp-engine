//
// Created by Leslie on 13.10.2024.
//

#include "Engine.hpp"

using namespace fimbulwinter::engine;

void Engine::resizeComponentStorage() {
    const auto newSize = Component::getRegisteredComponents().size();

    for (auto &x: Engine::entities) {
        x.resize(newSize);
    }
}

Engine::EntityId Engine::instanciateEntity(std::vector<std::unique_ptr<Component>> &components) {
    this->entities.emplace_back();
    this->resizeComponentStorage();
    auto &newestEntity = this->entities.back();

    for (auto &component: components) {
        newestEntity[component->getId()] = std::move(component);
    }
    return this->entities.size() - 1;
}

void Engine::registerSystem(std::unique_ptr<SystemFunctorBase> system) {
    this->systems.push_back(std::move(system));
}

void Engine::tick() {
    for (auto &system: this->systems) {
        for (auto &entity: this->entities) {
            std::vector<Component *> componentView(entity.size()); // TODO: Garbage Code
            for (int i = 0; i < entity.size(); i++) {
                componentView[i] = entity[i].get();
            }
            system->run(componentView);
        }
    }
}

[[nodiscard]] bool SystemFunctorBase::run(const std::vector<Component *> &entityComponents) const {
    std::vector<Component *> parameters;

    for (const auto &componentName: componentNames) {
        const auto id = Component::getRegisteredComponents().at(componentName);
        const auto matchingComponent = entityComponents.at(id);
        if (entityComponents.at(id)) {
            parameters.emplace_back(matchingComponent);
        } else {
            return false;
        }
    }

    system(parameters);
    return true;
}
