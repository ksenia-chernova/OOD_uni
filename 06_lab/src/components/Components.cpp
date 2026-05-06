#include "IComponent.h"

class CPU : public IComponent {
    std::string name_; Platform plat_; double price_;
public:
    CPU(std::string n, Platform p, double pr) : name_(std::move(n)), plat_(p), price_(pr) {}
    ~CPU() override = default;
    std::string getName() const override { return name_; }
    double getPrice() const override { return price_; }
    Platform getPlatform() const override { return plat_; }
    ComponentType getType() const override { return ComponentType::CPU; }
    IComponent* clone() const override { return new CPU(*this); }
};

class Motherboard : public IComponent {
    std::string name_; Platform plat_; double price_; std::string socket_;
public:
    Motherboard(std::string n, Platform p, double pr, std::string sock)
        : name_(std::move(n)), plat_(p), price_(pr), socket_(std::move(sock)) {}
    ~Motherboard() override = default;
    std::string getName() const override { return name_; }
    double getPrice() const override { return price_; }
    Platform getPlatform() const override { return plat_; }
    ComponentType getType() const override { return ComponentType::MOTHERBOARD; }
    const std::string& getSocket() const { return socket_; }
    IComponent* clone() const override { return new Motherboard(*this); }
};

class RAM : public IComponent {
    std::string name_; Platform plat_; double price_;
public:
    RAM(std::string n, Platform p, double pr) : name_(std::move(n)), plat_(p), price_(pr) {}
    ~RAM() override = default;
    std::string getName() const override { return name_; }
    double getPrice() const override { return price_; }
    Platform getPlatform() const override { return plat_; }
    ComponentType getType() const override { return ComponentType::RAM; }
    IComponent* clone() const override { return new RAM(*this); }
};

class GPU : public IComponent {
    std::string name_; Platform plat_; double price_;
public:
    GPU(std::string n, Platform p, double pr) : name_(std::move(n)), plat_(p), price_(pr) {}
    ~GPU() override = default;
    std::string getName() const override { return name_; }
    double getPrice() const override { return price_; }
    Platform getPlatform() const override { return plat_; }
    ComponentType getType() const override { return ComponentType::GPU; }
    IComponent* clone() const override { return new GPU(*this); }
};