#include "MessageBox.h"
#include "ftxui/dom/elements.hpp"

ftxui::Component MessageBox::Show(const std::string& title,
                                    const std::string& message,
                                    Type type,
                                    std::function<void()> on_close) {
    auto close_btn = ftxui::Button("OK", on_close);

    return ftxui::Renderer(close_btn, [=] {
        ftxui::Color color;
        switch (type) {
            case Info: color = ftxui::Color::Blue; break;
            case Warning: color = ftxui::Color::Yellow; break;
            case Error: color = ftxui::Color::Red; break;
        }

        return ftxui::vbox({
            ftxui::text(title) | ftxui::bold | ftxui::color(color),
            ftxui::separator(),
            ftxui::paragraph(message),
            ftxui::separator(),
            close_btn->Render() | ftxui::center
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 50);
    });
}

