//
// Created by Leslie on 13.10.2024.
//

#ifndef FIMBULWINTERENGINE_ENGINE_HPP
#define FIMBULWINTERENGINE_ENGINE_HPP

#include <vector>
#include <thread>
#include <optional>

#include "Component.hpp"
#include "System.hpp"
#include "Window.hpp"

namespace fimbulwinter::engine {
    class Engine {
    public:
        using EntityStorage = std::vector<std::vector<std::unique_ptr<Component>>>;
        using SystemVector = std::vector<std::unique_ptr<SystemFunctorBase>>;
        using SystemStorage = std::vector<std::vector<SystemVector>>;
        using EntityId = int;

    private:
        EntityStorage entities;
        SystemStorage systemStorage;
        std::optional<std::jthread> workerThread;
        Window window;

    public:
        void resizeComponentStorage();

        EntityId instanciateEntity(std::vector<Component *> components);

        void registerSystem(SystemFunctorBase *system);


        void tick();

        void run();

        void terminate();
    };
}
#endif //FIMBULWINTERENGINE_ENGINE_HPP
