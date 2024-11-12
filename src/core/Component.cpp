//
// Created by Leslie on 31.10.2024.
//

#include "core/Component.hpp"

using namespace fimbulwinter::engine::core;

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