//
// Created by Leslie on 13.10.2024.
//

#ifndef FIMBULWINTERENGINE_ENGINE_HPP
#define FIMBULWINTERENGINE_ENGINE_HPP

#include <string>
#include <unordered_map>
#include <array>
#include <optional>
#include <vector>
#include <memory>
#include <iostream>
#include <concepts>
#include <algorithm>
#include <functional>

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

    class Engine {
    public:
        using EntityStorage = std::vector<std::vector<std::unique_ptr<Component>>>;
        using EntityId = int;
    private:
        EntityStorage entities;
    public:
        void resizeComponentStorage();

        EntityId instanciateEntity(std::vector<std::unique_ptr<Component>> &components);
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
        };
    };

    template<ComponentConcept... Cs>
    void createSystemFunctor() {
    }
}
#endif //FIMBULWINTERENGINE_ENGINE_HPP
