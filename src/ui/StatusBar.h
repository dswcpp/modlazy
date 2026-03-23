#pragma once

#include "ftxui/component/component.hpp"
#include <string>

class App;

class StatusBar {
public:
    explicit StatusBar(App* app);
    ftxui::Component GetComponent();

private:
    App* app_;
};
