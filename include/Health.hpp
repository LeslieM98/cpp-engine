//
// Created by Leslie on 31.10.2024.
//

#ifndef FIMBULWINTERENGINE_HEALTH_HPP
#define FIMBULWINTERENGINE_HEALTH_HPP

#include "Component.hpp"

namespace fimbulwinter::engine {
    class Health : public virtual Component {
        int max;
        int current;
    public:
        static ComponentName getName();

        Health(int max, int current);

        [[nodiscard]] int getMax() const;

        [[nodiscard]] int getCurrent() const;
    };
}
#endif //FIMBULWINTERENGINE_HEALTH_HPP
