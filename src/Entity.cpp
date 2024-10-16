#include "Entity.hpp"

//
// Created by Leslie on 15.10.2024.
//
Entity::Entity(const FragmentType &id, const FragmentType &version) : id(id), version(version) {}

bool Entity::operator==(const Entity &rhs) const {
    return id == rhs.id &&
           version == rhs.version;
}

Entity::operator StorageType() const {
    return (this->version << sizeof(FragmentType) * 8) + this->id;
}

const Entity::FragmentType &Entity::getId() const {
    return this->id;
}

const Entity::FragmentType &Entity::getVersion() const {
    return this->version;
}
