#pragma once
#include "../components/IComponent.h"

class IComponentFactory {
public:
    virtual ~IComponentFactory() = default;
    virtual IComponent* createCPU() = 0;
    virtual IComponent* createMotherboard() = 0;
    virtual IComponent* createRAM() = 0;
    virtual IComponent* createGPU() = 0;
    virtual Platform getPlatform() const = 0;
};