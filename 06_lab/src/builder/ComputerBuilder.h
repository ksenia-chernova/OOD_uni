#pragma once
#include "../factories/IComponentFactory.h"
#include "../core/PriceCatalog.h"
#include "Computer.h"
#include <vector>

class ComputerBuilder {
    IComponentFactory* factory_; // DI
    PriceCatalog* catalog_;      // DI
    std::vector<IComponent*> parts_;
public:
    explicit ComputerBuilder(IComponentFactory* factory, PriceCatalog* catalog)
        : factory_(factory), catalog_(catalog) {}

    ~ComputerBuilder() {
        for (auto p : parts_) delete p; // Очистка при сбросе
        parts_.clear();
    }

    void reset() {
        for (auto p : parts_) delete p;
        parts_.clear();
    }

    void buildCPU() { parts_.push_back(factory_->createCPU()); }
    void buildMotherboard() { parts_.push_back(factory_->createMotherboard()); }
    void buildRAM() { parts_.push_back(factory_->createRAM()); }
    void buildGPU() { parts_.push_back(factory_->createGPU()); }

    bool validateCompatibility() const {
        if (parts_.empty()) return false;
        Platform base = parts_[0]->getPlatform();
        for (auto p : parts_) if (p->getPlatform() != base) return false;
        return true;
    }

    Computer* build() {
        if (!validateCompatibility()) throw std::runtime_error("Несовместимые компоненты!");
        Computer* pc = new Computer(factory_->getPlatform());
        for (auto p : parts_) pc->addComponent(p);
        parts_.clear(); // Передача права владения
        return pc;
    }
};