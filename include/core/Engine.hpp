//
// Created by Leslie on 13.10.2024.
//

#ifndef FIMBULWINTERENGINE_ENGINE_HPP
#define FIMBULWINTERENGINE_ENGINE_HPP

#include <vector>
#include <thread>
#include <optional>
#include <unordered_map>
#include <memory>

#include "core/Component.hpp"
#include "core/System.hpp"
#include "core/Window.hpp"

namespace fimbulwinter::engine::core {
    class Engine {
    public:
        using ComponentSet = std::unordered_map<size_t, std::unique_ptr<Component>>;
        using EntityStorage = std::vector<ComponentSet>;
        using SystemVector = std::vector<std::unique_ptr<SystemFunctorBase>>;
        using SystemStorage = std::vector<std::vector<SystemVector>>;
        using EntityId = int;

    private:
        EntityStorage entities;
        SystemStorage systemStorage;
        std::optional<std::jthread> workerThread;
        Window window;

        template<ComponentConcept T, ComponentConcept... Ts>
        ComponentSet instantiateComponentSet(T &component, Ts... components);

    public:
        template<ComponentConcept... T>
        EntityId instantiateEntity(T... components);

        void registerSystem(SystemFunctorBase *system);


        void tick();

        void run();

        void terminate();
    };

    template<ComponentConcept T, ComponentConcept... Ts>
    Engine::ComponentSet Engine::instantiateComponentSet(T &component, Ts... components) {
        auto key = typeid(T).hash_code();
        std::unique_ptr<Component> value = std::make_unique<T>(std::move(component));
        if constexpr (sizeof...(Ts) > 0) {
            ComponentSet componentSet = instantiateComponentSet(components...);
            componentSet.emplace(key, std::move(value));
            return componentSet;
        } else {
            ComponentSet componentSet;
            componentSet.emplace(key, std::move(value));
            return componentSet;
        }
    }


    template<ComponentConcept... T>
    Engine::EntityId Engine::instantiateEntity(T... components) {
        auto componentSet = instantiateComponentSet(components...);
        this->entities.emplace_back();

        return this->entities.size() - 1;
    }
}


#endif //FIMBULWINTERENGINE_ENGINE_HPP
