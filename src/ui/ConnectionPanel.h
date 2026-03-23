#pragma once

#include "ftxui/component/component.hpp"
#include <string>

class App;

class ConnectionPanel {
public:
    explicit ConnectionPanel(App* app);
    ftxui::Component GetComponent();

private:
    App* app_;

    std::string device_input_ = "/dev/ttyUSB0";
    std::string baud_input_ = "9600";
    std::string parity_input_ = "N";
    std::string data_bits_input_ = "8";
    std::string stop_bits_input_ = "1";
    std::string slave_input_ = "1";
    std::string timeout_input_ = "500";
    std::string error_msg_;
};
