//
// Created by Leslie on 14.10.2024.
//

#include <utility>
#include "Transform3D.hpp"

const Vector3D &Transform3D::getPosition() const {
    return this->position;
}

const Vector3D &Transform3D::getRotation() const {
    return this->rotation;
}

const Vector3D &Transform3D::getScale() const {
    return this->scale;
}

Vector3D &Transform3D::getPosition() {
    return this->position;
}

Vector3D &Transform3D::getRotation() {
    return this->rotation;
}

Vector3D &Transform3D::getScale() {
    return this->scale;
}

Transform3D::Transform3D(Vector3D position, Vector3D rotation, Vector3D scale)
        : position(position),
          rotation(rotation),
          scale(scale) {}
