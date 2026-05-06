#pragma once
#include <map>
#include <string>
#include <stdexcept>

class PriceCatalog {
private:
    static PriceCatalog* instance_;
    std::map<std::string, double> prices_;

    PriceCatalog() {
        // Демо-данные
        prices_["Intel i7-12700K"] = 320.0;
        prices_["ASUS ROG Z690"] = 280.0;
        prices_["Corsair DDR5 32GB"] = 150.0;
        prices_["NVIDIA RTX 4070"] = 550.0;
        prices_["AMD EPYC 7443P"] = 1200.0;
        prices_["Supermicro H12SSL"] = 850.0;
        prices_["Samsung ECC DDR4 64GB"] = 300.0;
        prices_["NVIDIA A2000"] = 600.0;
    }
    PriceCatalog(const PriceCatalog&) = delete;
    PriceCatalog& operator=(const PriceCatalog&) = delete;
public:
    static PriceCatalog* getInstance() {
        if (!instance_) instance_ = new PriceCatalog();
        return instance_;
    }
    static void destroy() { delete instance_; instance_ = nullptr; }

    void registerPrice(const std::string& name, double price) { prices_[name] = price; }
    double getPrice(const std::string& name) const {
        auto it = prices_.find(name);
        if (it == prices_.end()) throw std::runtime_error("Price not found: " + name);
        return it->second;
    }
};

PriceCatalog* PriceCatalog::instance_ = nullptr;