//
// Created by Leslie on 14.10.2024.
//

#ifndef FIMBULWINTERENGINE_ENTITY_HPP
#define FIMBULWINTERENGINE_ENTITY_HPP

#include <cstdint>

class Entity {
public:
    using FragmentType = uint16_t;
    using StorageType = uint32_t;

private:
    const FragmentType id;
    const FragmentType version;

public:
    Entity(const FragmentType &id, const FragmentType &version);

    bool operator==(const Entity &rhs) const;


    explicit operator StorageType() const;


    [[nodiscard]] const FragmentType &getId() const;

    [[nodiscard]] const FragmentType &getVersion() const;
};

#endif //FIMBULWINTERENGINE_ENTITY_HPP
