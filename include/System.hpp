//
// Created by Leslie on 22.10.2024.
//

#ifndef FIMBULWINTERENGINE_SYSTEM_HPP
#define FIMBULWINTERENGINE_SYSTEM_HPP

#include "Component.hpp"

namespace fimbulwinter::engine {
    class SystemFunctorBase {
        const std::function<void(const std::vector<Component *> &)> system;
        const std::vector<Component::ComponentName> componentNames;
    public:
        SystemFunctorBase(const std::vector<Component::ComponentName> &componentNames,
                          const std::function<void(const std::vector<Component *> &)> &system);

        virtual ~SystemFunctorBase() = default;

    public:
        [[nodiscard]] bool run(const std::vector<Component *> &entityComponents) const;
    };

    template<ComponentConcept... Cs>
    class SystemFunctor : virtual public SystemFunctorBase {
    public:
        explicit SystemFunctor(std::function<void(const std::vector<Component *> &)> const &system)
                : SystemFunctorBase(resolveComponentNames<Cs...>(), system) {}
    };
}

#endif //FIMBULWINTERENGINE_SYSTEM_HPP
