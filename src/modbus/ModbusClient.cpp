#include "ModbusClient.h"
#include <modbus.h>
#include <cerrno>
#include <cstring>

ModbusClient::ModbusClient() = default;

ModbusClient::~ModbusClient() {
    disconnect();
}

bool ModbusClient::connect(const SerialConfig& cfg, std::string& err) {
    disconnect();

    ctx_ = modbus_new_rtu(
        cfg.device.c_str(),
        cfg.baud,
        cfg.parity,
        cfg.data_bits,
        cfg.stop_bits
    );

    if (!ctx_) {
        err = "modbus_new_rtu failed";
        last_error_ = err;
        return false;
    }

    modbus_set_slave(ctx_, cfg.slave_id);

    timeval tv{};
    tv.tv_sec = cfg.response_timeout_ms / 1000;
    tv.tv_usec = (cfg.response_timeout_ms % 1000) * 1000;
    modbus_set_response_timeout(ctx_, tv.tv_sec, tv.tv_usec);

    if (modbus_connect(ctx_) == -1) {
        err = modbus_strerror(errno);
        last_error_ = err;
        modbus_free(ctx_);
        ctx_ = nullptr;
        return false;
    }

    connected_ = true;
    return true;
}

void ModbusClient::disconnect() {
    if (ctx_) {
        modbus_close(ctx_);
        modbus_free(ctx_);
        ctx_ = nullptr;
    }
    connected_ = false;
}

bool ModbusClient::isConnected() const {
    return connected_;
}

bool ModbusClient::setSlave(int slave_id, std::string& err) {
    if (!ctx_) {
        err = "not connected";
        return false;
    }
    if (modbus_set_slave(ctx_, slave_id) == -1) {
        err = modbus_strerror(errno);
        last_error_ = err;
        return false;
    }
    return true;
}

bool ModbusClient::readHoldingRegisters(int addr, int count,
                                        std::vector<uint16_t>& out,
                                        std::string& err) {
    if (!ctx_) {
        err = "not connected";
        return false;
    }

    out.resize(count);
    int rc = modbus_read_registers(ctx_, addr, count, out.data());
    if (rc == -1) {
        err = modbus_strerror(errno);
        last_error_ = err;
        out.clear();
        return false;
    }
    out.resize(rc);
    return true;
}

bool ModbusClient::writeSingleRegister(int addr, uint16_t value, std::string& err) {
    if (!ctx_) {
        err = "not connected";
        return false;
    }

    int rc = modbus_write_register(ctx_, addr, value);
    if (rc == -1) {
        err = modbus_strerror(errno);
        last_error_ = err;
        return false;
    }
    return true;
}

std::string ModbusClient::lastError() const {
    return last_error_;
}
