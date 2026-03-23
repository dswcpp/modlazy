#pragma once

#include "ftxui/component/component.hpp"
#include <string>

class App;

class OperationPanel {
public:
    explicit OperationPanel(App* app);
    ftxui::Component GetComponent();

private:
    App* app_;

    int selected_tab_ = 0;

    // Read
    std::string read_addr_input_ = "0x0000";
    std::string read_count_input_ = "10";

    // Write Single
    std::string write_addr_input_ = "0x0000";
    std::string write_value_input_ = "0x0000";

    // Write Multiple
    std::string write_multi_addr_input_ = "0x0000";
    std::string write_multi_values_input_ = "0x00 0x00";

    std::string error_msg_;
};
