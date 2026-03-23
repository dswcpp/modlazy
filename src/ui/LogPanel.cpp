#include "LogPanel.h"
#include "app/App.h"
#include "ftxui/dom/elements.hpp"

LogPanel::LogPanel(App* app) : app_(app) {}

ftxui::Component LogPanel::GetComponent() {
    return ftxui::Renderer([this] {
        auto& logs = app_->getLogs();
        ftxui::Elements log_lines;

        for (size_t i = 0; i < logs.size(); ++i) {
            auto& log = logs[i];
            auto line = ftxui::text(log.timestamp + " [" + log.type + "] " + log.message);

            if (log.type == "ERROR") line = line | ftxui::color(ftxui::Color::Red);
            else if (log.type == "TX") line = line | ftxui::color(ftxui::Color::Yellow);
            else if (log.type == "RX") line = line | ftxui::color(ftxui::Color::Green);

            log_lines.push_back(line);
        }

        return ftxui::vbox({
            ftxui::text("Logs") | ftxui::bold,
            ftxui::separator(),
            ftxui::vbox(log_lines) | ftxui::vscroll_indicator | ftxui::yframe | ftxui::flex
        }) | ftxui::border;
    });
}
