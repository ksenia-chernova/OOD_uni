#include <iostream>
#include <cassert>
#include <string>
#include <functional>

#include "components/IComponent.h"
#include "factories/Factories.cpp"
#include "core/PriceCatalog.h"
#include "builder/Computer.h"
#include "builder/ComputerBuilder.h"
#include "builder/Director.h"
#include "prototype/PresetManager.h"

struct TestResult {
    bool passed;
    std::string message;
};

TestResult runTest(const std::string& name, std::function<bool()> test) {
    try {
        bool res = test();
        if (res) return {true, "OK: " + name};
        return {false, "ERROR: " + name + " - assertion failed"};
    } catch (const std::exception& e) {
        return {false, "ERROR: " + name + " - " + e.what()};
    }
}

int main() {
    std::cout << "=== Запуск тестового раннера ===\n";
    int passed = 0, total = 5;

    // Тест 1: Singleton PriceCatalog
    auto t1 = runTest("Singleton PriceCatalog & Pricing", [](){
        PriceCatalog* cat = PriceCatalog::getInstance();
        double p = cat->getPrice("Intel i7-12700K");
        return (p == 320.0);
    });
    std::cout << t1.message << "\n"; if(t1.passed) passed++;

    // Тест 2: Abstract Factory
    auto t2 = runTest("Abstract Factory PC Creation", [](){
        PCFactory f;
        IComponent* cpu = f.createCPU();
        bool ok = (cpu->getPlatform() == Platform::PC && cpu->getType() == ComponentType::CPU);
        delete cpu;
        return ok;
    });
    std::cout << t2.message << "\n"; if(t2.passed) passed++;

    // Тест 3: Builder & Compatibility
    auto t3 = runTest("Builder Assembly & Validation", [](){
        PriceCatalog* cat = PriceCatalog::getInstance();
        PCFactory f;
        ComputerBuilder builder(&f, cat);
        builder.buildCPU(); builder.buildMotherboard(); builder.buildRAM(); builder.buildGPU();
        bool valid = builder.validateCompatibility();
        Computer* pc = builder.build(); // Передача владения
        double total = pc->getTotalPrice();
        delete pc;
        return valid && total > 0;
    });
    std::cout << t3.message << "\n"; if(t3.passed) passed++;

    // Тест 4: Prototype Deep Copy
    auto t4 = runTest("Prototype Deep Clone", [](){
        PCFactory f; PriceCatalog* cat = PriceCatalog::getInstance();
        ComputerBuilder builder(&f, cat);
        builder.buildCPU(); builder.buildMotherboard(); builder.buildRAM(); builder.buildGPU();
        Computer* original = builder.build();
        
        Computer* copy = original->clone();
        bool sameSpec = (original->getTotalPrice() == copy->getTotalPrice());
        
        // Проверяем независимость памяти
        delete copy; 
        bool originalAlive = (original->getTotalPrice() > 0);
        delete original;
        return sameSpec && originalAlive;
    });
    std::cout << t4.message << "\n"; if(t4.passed) passed++;

    // Тест 5: Preset Save/Load & DI
    auto t5 = runTest("PresetManager Save/Load (DI)", [](){
        ServerFactory sf; PriceCatalog* cat = PriceCatalog::getInstance();
        ComputerBuilder builder(&sf, cat);
        builder.buildCPU(); builder.buildMotherboard(); builder.buildRAM(); builder.buildGPU();
        Computer* server = builder.build();

        PresetManager mgr;
        mgr.savePreset("prod_srv", server);
        delete server; // Удаление оригинала

        Computer* restored = mgr.loadPreset("prod_srv");
        bool ok = (restored->checkCompatibility() && restored->getTotalPrice() > 1500.0);
        delete restored;
        return ok;
    });
    std::cout << t5.message << "\n"; if(t5.passed) passed++;

    std::cout << "\n=== Итог: " << passed << "/" << total << " тестов пройдено ===\n";

    // Демонстрация работы конфигуратора
    std::cout << "\n[Демонстрация] Сборка рабочей станции:\n";
    PCFactory pf;
    PriceCatalog* catalog = PriceCatalog::getInstance();
    ComputerBuilder cb(&pf, catalog);
    Director director(&cb);
    
    director.constructStandardPC();
    Computer* myPC = cb.build();
    std::cout << myPC->getSpecification();
    delete myPC;

    PriceCatalog::destroy(); // Очистка Singleton
    return (passed == total) ? 0 : 1;
}