//
// Created by Leslie on 13.10.2024.
//

#include "Engine.hpp"

using namespace fimbulwinter::engine;

void Engine::resizeComponentStorage() {
    const auto newSize = Component::getRegisteredComponents().size();

    for (auto &entity: Engine::entities) {
        entity.resize(newSize);
    }
}

void Engine::tick() {
    for (auto &system: this->systems) {
        for (auto &entity: this->entities) {
            std::vector<Component *> componentView(entity.size()); // TODO: Garbage Code
            for (int i = 0; i < entity.size(); i++) {
                componentView[i] = entity[i].get();
            }
            const auto systemHasRun = system->run(componentView);
        }
    }
}

Engine::EntityId Engine::instanciateEntity(const std::vector<Component *> components) {
    this->entities.emplace_back();
    this->resizeComponentStorage();
    auto &newestEntity = this->entities.back();

    for (auto &component: components) {
        newestEntity[component->getId()].reset(component);
    }
    return this->entities.size() - 1;
}

void Engine::registerSystem(SystemFunctorBase *system) {
    this->systems.emplace_back();
    this->systems.back().reset(system);
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
