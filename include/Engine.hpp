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
#include "Component.hpp"

namespace fimbulwinter::engine {

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
}
#endif //FIMBULWINTERENGINE_ENGINE_HPP
