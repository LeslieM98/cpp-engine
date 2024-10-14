//
// Created by Leslie on 14.10.2024.
//

#ifndef FIMBULWINTERENGINE_TRANSFORM3D_HPP
#define FIMBULWINTERENGINE_TRANSFORM3D_HPP

#include "Vector3D.hpp"

class Transform3D {
    Vector3D position;
    Vector3D rotation;
    Vector3D scale;
public:

    Transform3D() = default;

    Transform3D(const Transform3D &other) = default;

    Transform3D(Transform3D &&other) noexcept = default;

    Transform3D(Vector3D position, Vector3D rotation, Vector3D scale);


    [[nodiscard]] const Vector3D &getPosition() const;

    [[nodiscard]] const Vector3D &getRotation() const;

    [[nodiscard]] const Vector3D &getScale() const;


    [[nodiscard]] Vector3D &getPosition();

    [[nodiscard]] Vector3D &getRotation();

    [[nodiscard]] Vector3D &getScale();


    bool operator==(const Transform3D &rhs) const = default;
};

#endif //FIMBULWINTERENGINE_TRANSFORM3D_HPP
