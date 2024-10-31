//
// Created by Leslie on 31.10.2024.
//
#include "Health.hpp"

using namespace fimbulwinter::engine;

Health::Health(int max, int current) : Component("Health"), max(max), current(current) {}

int Health::getMax() const {
    return max;
}

int Health::getCurrent() const {
    return current;
}

Component::ComponentName Health::getName() {
    return {"Health"};
}