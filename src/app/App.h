#pragma once

#include <string>
#include <vector>
#include <memory>
#include "modbus/ModbusClient.h"

struct LogEntry {
    std::string timestamp;
    std::string type;  // "TX", "RX", "ERROR", "INFO"
    std::string message;
};

class App {
public:
    App();
    ~App();

    bool connectModbus(const SerialConfig& cfg);
    void disconnectModbus();
    bool isConnected() const;

    bool readHoldingRegs(int addr, int count);
    bool writeSingleReg(int addr, uint16_t value);

    const std::vector<LogEntry>& getLogs() const { return logs_; }
    const SerialConfig& getConfig() const { return config_; }
    void setConfig(const SerialConfig& cfg) { config_ = cfg; }

    void addLog(const std::string& type, const std::string& msg);
    void executeCommand(const std::string& cmd);

    std::string popMessage() {
        if (message_queue_.empty()) return "";
        auto msg = message_queue_.front();
        message_queue_.erase(message_queue_.begin());
        return msg;
    }
    bool hasMessage() const { return !message_queue_.empty(); }

private:
    std::unique_ptr<ModbusClient> modbus_;
    SerialConfig config_;
    std::vector<LogEntry> logs_;
    std::vector<std::string> message_queue_;

    std::string getCurrentTime();
};
