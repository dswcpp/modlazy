#pragma once

#include "ftxui/component/component.hpp"
#include <memory>

class App;

class MainView {
public:
    explicit MainView(App* app);

    ftxui::Component GetComponent();
    void Run();

private:
    App* app_;

    ftxui::Component CreateConnectionPanel();
    ftxui::Component CreateLogPanel();
    ftxui::Component CreateCommandBar();

    std::string command_input_;
    int selected_panel_ = 0;

    std::string device_input_ = "/dev/ttyUSB0";
    std::string baud_input_ = "9600";
    std::string slave_input_ = "1";
};
