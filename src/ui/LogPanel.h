#pragma once

#include "ftxui/component/component.hpp"

class App;

class LogPanel {
public:
    explicit LogPanel(App* app);
    ftxui::Component GetComponent();

private:
    App* app_;
    int scroll_position_ = 0;
};
