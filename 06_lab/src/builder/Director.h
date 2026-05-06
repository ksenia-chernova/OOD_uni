#pragma once
#include "ComputerBuilder.h"

class Director {
    ComputerBuilder* builder_;
public:
    explicit Director(ComputerBuilder* builder) : builder_(builder) {}

    void constructStandardPC() {
        builder_->reset();
        builder_->buildCPU();
        builder_->buildMotherboard();
        builder_->buildRAM();
        builder_->buildGPU();
    }

    void constructServer() {
        builder_->reset();
        builder_->buildCPU();
        builder_->buildMotherboard();
        builder_->buildRAM();
        builder_->buildGPU();
    }
};