//
// Created by Leslie on 22.10.2024.
//

#ifndef FIMBULWINTERENGINE_SYSTEM_HPP
#define FIMBULWINTERENGINE_SYSTEM_HPP

#include <functional>

#include "core/Component.hpp"

namespace fimbulwinter::engine {

    enum class Stage : int {
        LOGIC, RENDER,
    };

    enum class SubStage : int {
        FIRST, PRE, MAIN, POST, LAST
    };

    class SystemFunctorBase {
        const std::function<void(const std::vector<Component *> &)> system;
        const std::vector<Component::ComponentName> componentNames;

        const SubStage SUB_STAGE;
        const Stage STAGE;

    public:
        [[nodiscard]] const Stage getStage() const;

        [[nodiscard]] const SubStage getSubStage() const;


        SystemFunctorBase(const std::vector<Component::ComponentName> &componentNames,
                          const std::function<void(const std::vector<Component *> &)> &system,
                          SubStage subStage,
                          Stage stage);

        virtual ~SystemFunctorBase() = default;

        [[nodiscard]] bool run(const std::vector<Component *> &entityComponents) const;
    };

    template<ComponentConcept... Cs>
    class SystemFunctor : virtual public SystemFunctorBase {
    public:
        explicit SystemFunctor(std::function<void(const std::vector<Component *> &)> const &system,
                               SubStage subStage = SubStage::MAIN,
                               Stage stage = Stage::LOGIC
        ) : SystemFunctorBase(resolveComponentNames<Cs...>(), system, subStage, stage) {}
    };
}

#endif //FIMBULWINTERENGINE_SYSTEM_HPP
