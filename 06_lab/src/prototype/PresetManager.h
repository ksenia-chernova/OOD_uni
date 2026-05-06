#pragma once
#include "../builder/Computer.h"
#include <map>
#include <string>
#include <stdexcept>

class PresetManager {
    std::map<std::string, Computer*> presets_;
public:
    ~PresetManager() {
        for (auto& pair : presets_) delete pair.second;
    }

    void savePreset(const std::string& name, Computer* config) {
        if (presets_.count(name)) delete presets_[name]; // Очистка старого
        presets_[name] = config->clone(); // Глубокое копирование через Prototype
    }

    Computer* loadPreset(const std::string& name) const {
        auto it = presets_.find(name);
        if (it == presets_.end()) throw std::runtime_error("Пресет не найден: " + name);
        return it->second->clone(); // Возвращаем независимую копию
    }
};