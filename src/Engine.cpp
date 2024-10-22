//
// Created by Leslie on 13.10.2024.
//

#include "Engine.hpp"
#include "Component.hpp"

using namespace fimbulwinter::engine;

std::unordered_map<Component::ComponentName, Component::ComponentId> Component::registeredComponents;
Component::ComponentId Component::nextId{};

Component::Component(std::string name) : name(std::move(name)), id(Component::getComponentId(this->name)) {}

const std::string &Component::getName() const {
    return name;
}

bool Component::operator==(const Component &rhs) const {
    return name == rhs.name;
}

Component::ComponentId Component::getComponentId(const Component::ComponentName &componentName) {
    if (registeredComponents.contains(componentName)) {
        return registeredComponents[componentName];
    } else {
        return registeredComponents[componentName] = Component::nextId++;
    }
}

Component::ComponentId Component::getId() const {
    return id;
}

const Component::registeredComponentType &Component::getRegisteredComponents() {
    return Component::registeredComponents;
}

Position::Position(float x, float y, float z) : Component("Position"), position({x, y, z}) {
}

float &Position::x() {
    return this->position[0];
}

float &Position::y() {
    return this->position[1];
}

float &Position::z() {
    return this->position[2];
}

const float &Position::x() const {
    return this->position[0];
}

const float &Position::y() const {
    return this->position[1];
}

const float &Position::z() const {
    return this->position[2];
}

Component::ComponentName Position::getName() {
    return {"Position"};

}

Health::Health(int max, int current) : Component("Health"), max(max), current(current) {}

int Health::getMax() const {
    return max;
}

int Health::getCurrent() const {
    return current;
}

Component::ComponentName Health::getName() {
    return {"Health"};
}

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

SystemFunctorBase::SystemFunctorBase(const std::vector<Component::ComponentName> &componentNames,
                                     const std::function<void(const std::vector<Component *> &)> &system)
        : system(system), componentNames(componentNames) {}
