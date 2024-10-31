//
// Created by Leslie on 31.10.2024.
//

#ifndef FIMBULWINTERENGINE_RESOURCE_HPP
#define FIMBULWINTERENGINE_RESOURCE_HPP

#include <string>

class Resource {
public:
    using ResourceName = std::string;

private:
    ResourceName resourceName;

public:
    [[nodiscard]] const ResourceName &getName() const;
};

#endif //FIMBULWINTERENGINE_RESOURCE_HPP
