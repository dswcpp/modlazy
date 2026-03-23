#include "App.h"
#include <chrono>
#include <iomanip>
#include <sstream>

App::App() : modbus_(std::make_unique<ModbusClient>()) {
    addLog("INFO", "ModLazy started");
}

App::~App() = default;

bool App::connectModbus(const SerialConfig& cfg) {
    config_ = cfg;
    std::string err;

    if (modbus_->connect(cfg, err)) {
        addLog("INFO", "Connected to " + cfg.device);
        return true;
    }

    addLog("ERROR", "Connect failed: " + err);
    return false;
}

void App::disconnectModbus() {
    modbus_->disconnect();
    addLog("INFO", "Disconnected");
}

bool App::isConnected() const {
    return modbus_->isConnected();
}

bool App::readHoldingRegs(int addr, int count) {
    std::vector<uint16_t> values;
    std::string err;

    if (modbus_->readHoldingRegisters(addr, count, values, err)) {
        std::ostringstream oss;
        oss << "Read [" << addr << "]: ";
        for (size_t i = 0; i < values.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << values[i];
        }
        addLog("RX", oss.str());
        return true;
    }

    addLog("ERROR", "Read failed: " + err);
    return false;
}

bool App::writeSingleReg(int addr, uint16_t value) {
    std::string err;

    if (modbus_->writeSingleRegister(addr, value, err)) {
        addLog("TX", "Write [" + std::to_string(addr) + "] = " + std::to_string(value));
        return true;
    }

    addLog("ERROR", "Write failed: " + err);
    return false;
}

void App::addLog(const std::string& type, const std::string& msg) {
    logs_.push_back({getCurrentTime(), type, msg});
}

std::string App::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%H:%M:%S");
    return oss.str();
}
