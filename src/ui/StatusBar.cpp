#include "StatusBar.h"
#include "app/App.h"
#include "ftxui/dom/elements.hpp"

StatusBar::StatusBar(App* app) : app_(app) {}

ftxui::Component StatusBar::GetComponent() {
    return ftxui::Renderer([this] {
        auto& cfg = app_->getConfig();
        bool connected = app_->isConnected();

        auto status_text = connected ? "Connected" : "Disconnected";
        auto status_color = connected ? ftxui::Color::Green : ftxui::Color::Red;

        return ftxui::hbox({
            ftxui::text("Status: ") | ftxui::bold,
            ftxui::text(status_text) | ftxui::color(status_color),
            ftxui::separator(),
            ftxui::text(" Device: " + cfg.device),
            ftxui::text(" | Baud: " + std::to_string(cfg.baud)),
            ftxui::text(" | Slave: " + std::to_string(cfg.slave_id))
        }) | ftxui::border;
    });
}

