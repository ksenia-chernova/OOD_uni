#pragma once
#include "../components/IComponent.h"
#include <vector>
#include <string>
#include <sstream>

class Computer {
    std::vector<IComponent*> components_;
    Platform platform_;
public:
    explicit Computer(Platform p) : platform_(p) {}
    ~Computer() {
        for (auto c : components_) delete c;
    }

    void addComponent(IComponent* comp) {
        components_.push_back(comp);
        platform_ = comp->getPlatform();
    }

    double getTotalPrice() const {
        double sum = 0.0;
        for (auto c : components_) sum += c->getPrice();
        return sum;
    }

    bool checkCompatibility() const {
        if (components_.size() < 4) return false;
        Platform base = components_[0]->getPlatform();
        for (auto c : components_) if (c->getPlatform() != base) return false;
        // Простая проверка сокета CPU и MB
        const Motherboard* mb = nullptr;
        const CPU* cpu = nullptr;
        for (auto c : components_) {
            if (c->getType() == ComponentType::MOTHERBOARD) mb = static_cast<const Motherboard*>(c);
            if (c->getType() == ComponentType::CPU) cpu = static_cast<const CPU*>(c);
        }
        if (mb && cpu) {
            // В реальном проекте сравнивались бы сокеты. Здесь имитируем совместимость платформы.
            return true; 
        }
        return false;
    }

    std::string getSpecification() const {
        std::ostringstream oss;
        oss << "=== Спецификация устройства (" << (platform_ == Platform::PC ? "PC" : "SERVER") << ") ===\n";
        for (auto c : components_) oss << "  - " << c->getName() << " ($" << c->getPrice() << ")\n";
        oss << "Итого: $" << getTotalPrice() << "\n";
        oss << "Совместимость: " << (checkCompatibility() ? "OK" : "FAIL") << "\n";
        return oss.str();
    }

    Computer* clone() const { // Prototype для конфигурации
        auto* clone = new Computer(platform_);
        for (auto c : components_) clone->addComponent(c->clone());
        return clone;
    }
};