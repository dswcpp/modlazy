#include "CommandBar.h"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"

CommandBar::CommandBar(CommandCallback callback) : on_command_(callback) {}

ftxui::Component CommandBar::GetComponent() {
    auto input = ftxui::Input(&command_input_, "Enter command...");

    auto container = ftxui::Container::Vertical({input});

    auto with_event = ftxui::CatchEvent(container, [this](ftxui::Event event) {
        if (event == ftxui::Event::Return && !command_input_.empty()) {
            on_command_(command_input_);
            command_input_.clear();
            return true;
        }
        return false;
    });

    return ftxui::Renderer(with_event, [this, input] {
        return ftxui::hbox({
            ftxui::text(":") | ftxui::bold,
            input->Render() | ftxui::flex
        }) | ftxui::border;
    });
}
