//
// Created by Leslie on 31.10.2024.
//

#include "core/System.hpp"

using namespace fimbulwinter::engine;

SystemFunctorBase::SystemFunctorBase(const std::vector<Component::ComponentName> &componentNames,
                                     const std::function<void(const std::vector<Component *> &)> &system,
                                     SubStage subStage,
                                     Stage stage)
        : system(system), componentNames(componentNames), STAGE(stage), SUB_STAGE(subStage) {}

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

const Stage SystemFunctorBase::getStage() const {
    return STAGE;
}

const SubStage SystemFunctorBase::getSubStage() const {
    return SUB_STAGE;
}