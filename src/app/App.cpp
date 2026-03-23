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
        message_queue_.push_back("Connected successfully");
        return true;
    }

    addLog("ERROR", "Connect failed: " + err);
    message_queue_.push_back("Connection failed: " + err);
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
        oss << "Read [0x" << std::hex << std::uppercase << addr << "]: ";
        for (size_t i = 0; i < values.size(); ++i) {
            if (i > 0) oss << " ";
            oss << "0x" << std::setfill('0') << std::setw(4) << values[i];
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
        std::ostringstream oss;
        oss << "Write [0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << addr
            << "] = 0x" << std::setw(4) << value;
        addLog("TX", oss.str());
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

void App::executeCommand(const std::string& cmd) {
    std::istringstream iss(cmd);
    std::string action;
    iss >> action;

    if (action == "connect") {
        std::string device;
        int baud;
        char parity;
        int data_bits, stop_bits;
        if (iss >> device >> baud >> parity >> data_bits >> stop_bits) {
            SerialConfig cfg{device, baud, parity, data_bits, stop_bits, config_.slave_id, config_.response_timeout_ms};
            connectModbus(cfg);
        } else {
            addLog("ERROR", "Usage: connect <device> <baud> <parity> <data_bits> <stop_bits>");
        }
    } else if (action == "disconnect") {
        disconnectModbus();
    } else if (action == "slave") {
        int slave_id;
        if (iss >> slave_id) {
            config_.slave_id = slave_id;
            addLog("INFO", "Slave ID set to " + std::to_string(slave_id));
        } else {
            addLog("ERROR", "Usage: slave <id>");
        }
    } else if (action == "read") {
        std::string type, addr_str, count_str;
        if (iss >> type >> addr_str >> count_str) {
            int addr = std::stoi(addr_str, nullptr, 0);
            int count = std::stoi(count_str, nullptr, 0);
            if (type == "holding") {
                readHoldingRegs(addr, count);
            } else {
                addLog("ERROR", "Unknown register type: " + type);
            }
        } else {
            addLog("ERROR", "Usage: read <holding> <addr> <count>");
        }
    } else if (action == "write") {
        std::string addr_str, value_str;
        if (iss >> addr_str >> value_str) {
            int addr = std::stoi(addr_str, nullptr, 0);
            int value = std::stoi(value_str, nullptr, 0);
            writeSingleReg(addr, value);
        } else {
            addLog("ERROR", "Usage: write <addr> <value>");
        }
    } else {
        addLog("ERROR", "Unknown command: " + action);
    }
}
