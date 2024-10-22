//
// Created by Leslie on 22.10.2024.
//

#ifndef FIMBULWINTERENGINE_COMPONENT_HPP
#define FIMBULWINTERENGINE_COMPONENT_HPP

#include <functional>
#include <algorithm>
#include <concepts>
#include <iostream>
#include <memory>
#include <vector>
#include <optional>
#include <array>
#include <unordered_map>
#include <string>

namespace fimbulwinter::engine {
    class Component {
    public:
        using ComponentName = std::string;
        using ComponentId = int;
        using registeredComponentType = std::unordered_map<ComponentName, ComponentId>;

    private:
        static registeredComponentType registeredComponents;
        static ComponentId nextId;

        const ComponentName name;
        const ComponentId id;

        static ComponentId getComponentId(const ComponentName &componentName);

    public:

        static const registeredComponentType &getRegisteredComponents();

        explicit Component(std::string name);

        [[nodiscard]] const ComponentName &getName() const;

        [[nodiscard]] ComponentId getId() const;

        bool operator==(const Component &rhs) const;


        virtual ~Component() = default;
    };

    class Position : public virtual Component {
        std::array<float, 3> position;
    public:
        static ComponentName getName();

        Position(float x, float y, float z);

        [[nodiscard]] float &x();

        [[nodiscard]] float &y();

        [[nodiscard]] float &z();

        [[nodiscard]] const float &x() const;

        [[nodiscard]] const float &y() const;

        [[nodiscard]] const float &z() const;
    };

    class Health : public virtual Component {
        int max;
        int current;
    public:
        static ComponentName getName();

        Health(int max, int current);

        [[nodiscard]] int getMax() const;

        [[nodiscard]] int getCurrent() const;
    };

    template<typename T>
    concept ComponentConcept =requires(T t) {
        { T::getName() } -> std::convertible_to<Component::ComponentName>;
        requires std::is_base_of_v<Component, T>;
    };

    template<ComponentConcept C, ComponentConcept... Cs>
    std::vector<Component::ComponentName> resolveComponentNames() {
        std::vector<Component::ComponentName> names = {C::getName()};
        if constexpr (sizeof...(Cs) == 0) {
            return {names};
        } else {
            const auto remainingNames = resolveComponentNames<Cs...>();
            names.insert(names.end(), remainingNames.begin(), remainingNames.end());
            return names;
        }
    }
}
#endif //FIMBULWINTERENGINE_COMPONENT_HPP
