#pragma once

#include "ftxui/component/component.hpp"
#include <string>
#include <functional>

class MessageBox {
public:
    enum Type { Info, Warning, Error };

    static ftxui::Component Show(const std::string& title,
                                  const std::string& message,
                                  Type type,
                                  std::function<void()> on_close);
};
