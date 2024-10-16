//
// Created by Leslie on 15.10.2024.
//
#include "Component.hpp"

#include <utility>

Component::Component(std::string name) : name(std::move(name)) {}

