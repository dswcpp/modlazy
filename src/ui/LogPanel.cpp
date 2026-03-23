#include "LogPanel.h"
#include "app/App.h"
#include "ftxui/dom/elements.hpp"

LogPanel::LogPanel(App* app) : app_(app) {}

ftxui::Component LogPanel::GetComponent() {
    auto content = ftxui::Renderer([this] {
        auto& logs = app_->getLogs();
        ftxui::Elements log_lines;

        for (const auto& log : logs) {
            auto line = ftxui::text(log.timestamp + " [" + log.type + "] " + log.message);

            if (log.type == "ERROR") line = line | ftxui::color(ftxui::Color::Red);
            else if (log.type == "TX") line = line | ftxui::color(ftxui::Color::Yellow);
            else if (log.type == "RX") line = line | ftxui::color(ftxui::Color::Green);

            log_lines.push_back(line);
        }

        return ftxui::vbox(log_lines);
    });

    auto scrollable = content | ftxui::yflex | ftxui::yframe;

    return ftxui::Renderer(scrollable, [scrollable] {
        return ftxui::vbox({
            ftxui::text("Logs") | ftxui::bold,
            ftxui::separator(),
            scrollable->Render() | ftxui::flex
        }) | ftxui::border;
    });
}

