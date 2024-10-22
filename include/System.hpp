//
// Created by Leslie on 22.10.2024.
//

#ifndef FIMBULWINTERENGINE_SYSTEM_HPP
#define FIMBULWINTERENGINE_SYSTEM_HPP

#include "Component.hpp"

namespace fimbulwinter::engine {
    template<ComponentConcept... Cs>
    class SystemFunctor {
        const std::vector<Component::ComponentName> componentNames = resolveComponentNames<Cs...>();
        const std::function<void(const std::vector<Component *> &)> system;
    public:
        explicit SystemFunctor(std::function<void(const std::vector<Component *> &)> const &system) : system(system) {}

        [[nodiscard]] bool run(const std::vector<Component *> &entityComponents) const {
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
    };
}

#endif //FIMBULWINTERENGINE_SYSTEM_HPP
