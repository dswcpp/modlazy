#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

typedef struct _modbus modbus_t;

struct SerialConfig {
    std::string device = "/dev/ttyUSB0";
    int baud = 9600;
    char parity = 'N';
    int data_bits = 8;
    int stop_bits = 1;
    int slave_id = 1;
    int response_timeout_ms = 500;
};

class ModbusClient {
public:
    ModbusClient();
    ~ModbusClient();

    ModbusClient(const ModbusClient&) = delete;
    ModbusClient& operator=(const ModbusClient&) = delete;

    bool connect(const SerialConfig& cfg, std::string& err);
    void disconnect();
    bool isConnected() const;

    bool setSlave(int slave_id, std::string& err);

    bool readHoldingRegisters(int addr, int count,
                              std::vector<uint16_t>& out,
                              std::string& err);

    bool writeSingleRegister(int addr, uint16_t value, std::string& err);

    std::string lastError() const;

private:
    modbus_t* ctx_ = nullptr;
    bool connected_ = false;
    std::string last_error_;
};
