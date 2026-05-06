#include "IComponentFactory.h"
#include "../components/Components.cpp" // В реальном проекте подключать заголовки, здесь для компактности

class PCFactory : public IComponentFactory {
public:
    ~PCFactory() override = default;
    IComponent* createCPU() override { return new CPU("Intel i7-12700K", Platform::PC, 320.0); }
    IComponent* createMotherboard() override { return new Motherboard("ASUS ROG Z690", Platform::PC, 280.0, "LGA1700"); }
    IComponent* createRAM() override { return new RAM("Corsair DDR5 32GB", Platform::PC, 150.0); }
    IComponent* createGPU() override { return new GPU("NVIDIA RTX 4070", Platform::PC, 550.0); }
    Platform getPlatform() const override { return Platform::PC; }
};

class ServerFactory : public IComponentFactory {
public:
    ~ServerFactory() override = default;
    IComponent* createCPU() override { return new CPU("AMD EPYC 7443P", Platform::SERVER, 1200.0); }
    IComponent* createMotherboard() override { return new Motherboard("Supermicro H12SSL", Platform::SERVER, 850.0, "SP3"); }
    IComponent* createRAM() override { return new RAM("Samsung ECC DDR4 64GB", Platform::SERVER, 300.0); }
    IComponent* createGPU() override { return new GPU("NVIDIA A2000", Platform::SERVER, 600.0); }
    Platform getPlatform() const override { return Platform::SERVER; }
};