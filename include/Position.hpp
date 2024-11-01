//
// Created by Leslie on 31.10.2024.
//

#ifndef FIMBULWINTERENGINE_POSITION_HPP
#define FIMBULWINTERENGINE_POSITION_HPP

#include "Component.hpp"

namespace fimbulwinter::engine {
    class Position : public virtual Component {
        std::array<float, 3> position;
    public:
        static ComponentName getName();

        Position(float x, float y, float z);

        [[nodiscard]] float &x();

        [[nodiscard]] float &y();

        [[nodiscard]] float &z();

        [[nodiscard]] const float &x() const;

        [[nodiscard]] const float &y() const;

        [[nodiscard]] const float &z() const;
    };
}

#endif //FIMBULWINTERENGINE_POSITION_HPP
