//
// Created by Leslie on 15.10.2024.
//

#ifndef FIMBULWINTERENGINE_COMPONENT_HPP
#define FIMBULWINTERENGINE_COMPONENT_HPP

#include <string>

class Component {
    const std::string name;

public:
    Component(std::string name);

    virtual ~Component();
};


#endif //FIMBULWINTERENGINE_COMPONENT_HPP
