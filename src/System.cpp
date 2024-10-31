//
// Created by Leslie on 31.10.2024.
//

#include "System.hpp"

using namespace fimbulwinter::engine;

SystemFunctorBase::SystemFunctorBase(const std::vector<Component::ComponentName> &componentNames,
                                     const std::function<void(const std::vector<Component *> &)> &system)
        : system(system), componentNames(componentNames) {}
