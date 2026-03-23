#pragma once

#include "ftxui/component/component.hpp"
#include <string>
#include <functional>

class CommandBar {
public:
    using CommandCallback = std::function<void(const std::string&)>;

    explicit CommandBar(CommandCallback callback);
    ftxui::Component GetComponent();

private:
    std::string command_input_;
    CommandCallback on_command_;
};
