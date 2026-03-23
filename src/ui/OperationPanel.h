#pragma once

#include "ftxui/component/component.hpp"
#include <string>
#include <vector>

class App;

class OperationPanel {
public:
    explicit OperationPanel(App* app);
    ftxui::Component GetComponent();

private:
    App* app_;

    int selected_tab_ = 0;
    std::vector<std::string> tab_list_ = {"Read", "Write", "Quick"};

    // Read
    std::string read_addr_ = "0x0000";
    std::string read_count_ = "10";
    int read_type_ = 0;  // 0=Holding, 1=Input

    // Write Single
    std::string write_addr_ = "0x0000";
    std::string write_value_ = "0x0000";

    // Quick operations
    std::vector<std::pair<std::string, int>> quick_addrs_ = {
        {"0x0000", 0x0000},
        {"0x0010", 0x0010},
        {"0x0100", 0x0100}
    };
};
