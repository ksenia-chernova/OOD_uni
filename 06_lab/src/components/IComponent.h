#pragma once
#include <string>

enum class Platform { PC, SERVER, WORKSTATION };
enum class ComponentType { CPU, MOTHERBOARD, RAM, GPU };

class IComponent {
public:
    virtual ~IComponent() = default;
    virtual std::string getName() const = 0;
    virtual double getPrice() const = 0;
    virtual Platform getPlatform() const = 0;
    virtual ComponentType getType() const = 0;
    virtual IComponent* clone() const = 0; // Prototype
};