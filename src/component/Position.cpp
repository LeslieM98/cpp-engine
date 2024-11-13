//
// Created by Leslie on 31.10.2024.
//

#include "component/Position.hpp"

using namespace fimbulwinter::engine::component;
using namespace fimbulwinter::engine::core;

Position::Position(float x, float y, float z) : Component(typeid(Position).name()), position({x, y, z}) {
}

float &Position::x() {
    return this->position[0];
}

float &Position::y() {
    return this->position[1];
}

float &Position::z() {
    return this->position[2];
}

const float &Position::x() const {
    return this->position[0];
}

const float &Position::y() const {
    return this->position[1];
}

const float &Position::z() const {
    return this->position[2];
}

Component::ComponentName Position::getName() {
    return {"Position"};

}