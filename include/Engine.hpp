//
// Created by Leslie on 13.10.2024.
//

#ifndef FIMBULWINTERENGINE_ENGINE_HPP
#define FIMBULWINTERENGINE_ENGINE_HPP

#include <vector>
#include <memory>

#include "Component.hpp"
#include "System.hpp"

namespace fimbulwinter::engine {

    class Engine {
    public:
        using EntityStorage = std::vector<std::vector<std::unique_ptr<Component>>>;
        using EntityId = int;
    private:
        EntityStorage entities;
        std::vector<std::unique_ptr<SystemFunctorBase>> systems;
    public:
        void resizeComponentStorage();

        EntityId instanciateEntity(const std::vector<Component *> components);


        void registerSystem(std::unique_ptr<SystemFunctorBase> system);

        void tick();
    };
}
#endif //FIMBULWINTERENGINE_ENGINE_HPP
