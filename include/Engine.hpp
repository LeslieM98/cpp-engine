//
// Created by Leslie on 13.10.2024.
//

#ifndef FIMBULWINTERENGINE_ENGINE_HPP
#define FIMBULWINTERENGINE_ENGINE_HPP

#include <string>
#include <unordered_map>
#include <array>
#include <optional>
#include <vector>
#include <memory>

namespace fimbulwinter::engine {
    class Component {
    public:
        using ComponentName = std::string;
        using ComponentId = int;
        using registeredComponentType = std::unordered_map<ComponentName, ComponentId>;

    private:
        static registeredComponentType registeredComponents;
        static ComponentId nextId;

        const ComponentName name;
        const ComponentId id;

        static ComponentId getComponentId(const ComponentName &componentName);

    public:

        static const registeredComponentType &getRegisteredComponents();

        explicit Component(std::string name);

        [[nodiscard]] const ComponentName &getName() const;

        [[nodiscard]] ComponentId getId() const;

        bool operator==(const Component &rhs) const;


        virtual ~Component() = default;
    };

    class Engine {
    public:
        using EntityStorage = std::vector<std::vector<std::unique_ptr<Component>>>;
        using EntityId = int;
    private:
        EntityStorage entities;
    public:
        void resizeComponentStorage();

        EntityId instanciateEntity(std::vector<std::unique_ptr<Component>> &components);
    };

    class Position : public virtual Component {
        std::array<float, 3> position;
    public:
        Position(float x, float y, float z);

        [[nodiscard]] float &x();


        [[nodiscard]] float &y();

        [[nodiscard]] float &z();

        [[nodiscard]] const float &x() const;

        [[nodiscard]] const float &y() const;

        [[nodiscard]] const float &z() const;
    };

    class Health : public virtual Component {
        int max;
        int current;
    public:
        Health(int max, int current);

        [[nodiscard]] int getMax() const;

        [[nodiscard]] int getCurrent() const;
    };
}
#endif //FIMBULWINTERENGINE_ENGINE_HPP
