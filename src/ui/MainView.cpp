#include "MainView.h"
#include "app/App.h"
#include "modbus/ModbusClient.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

MainView::MainView(App* app) : app_(app) {}

ftxui::Component MainView::CreateConnectionPanel() {
    auto device_input = ftxui::Input(&device_input_, "Device");
    auto baud_input = ftxui::Input(&baud_input_, "Baud");
    auto slave_input = ftxui::Input(&slave_input_, "Slave");

    auto container = ftxui::Container::Vertical({device_input, baud_input, slave_input});

    return ftxui::Renderer(container, [this, device_input, baud_input, slave_input] {
        auto status = app_->isConnected() ? "Connected" : "Disconnected";

        return ftxui::vbox({
            ftxui::text("Connection") | ftxui::bold,
            ftxui::separator(),
            ftxui::hbox({ftxui::text("Device: "), device_input->Render()}),
            ftxui::hbox({ftxui::text("Baud:   "), baud_input->Render()}),
            ftxui::hbox({ftxui::text("Slave:  "), slave_input->Render()}),
            ftxui::separator(),
            ftxui::text("Status: " + std::string(status)) |
                (app_->isConnected() ? ftxui::color(ftxui::Color::Green) : ftxui::color(ftxui::Color::Red))
        }) | ftxui::border;
    });
}

ftxui::Component MainView::CreateLogPanel() {
    return ftxui::Renderer([this] {
        auto& logs = app_->getLogs();
        ftxui::Elements log_lines;

        int start = logs.size() > 20 ? logs.size() - 20 : 0;
        for (size_t i = start; i < logs.size(); ++i) {
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
            ftxui::vbox(log_lines)
        }) | ftxui::border;
    });
}

ftxui::Component MainView::CreateCommandBar() {
    auto input = ftxui::Input(&command_input_, "Enter command...");

    return ftxui::Renderer(input, [this, input] {
        return ftxui::hbox({
            ftxui::text(":") | ftxui::bold,
            input->Render() | ftxui::flex
        }) | ftxui::border;
    });
}

ftxui::Component MainView::GetComponent() {
    auto conn_panel = CreateConnectionPanel();
    auto log_panel = CreateLogPanel();
    auto cmd_bar = CreateCommandBar();

    auto container = ftxui::Container::Vertical({
        ftxui::Container::Horizontal({conn_panel, log_panel}),
        cmd_bar
    });

    return ftxui::Renderer(container, [=] {
        return ftxui::vbox({
            ftxui::hbox({
                conn_panel->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 40),
                ftxui::separator(),
                log_panel->Render() | ftxui::flex
            }) | ftxui::flex,
            ftxui::separator(),
            cmd_bar->Render() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3)
        });
    });
}

void MainView::Run() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    auto component = GetComponent();

    auto with_shortcuts = ftxui::CatchEvent(component, [&](ftxui::Event event) {
        if (event == ftxui::Event::Character('q')) {
            screen.ExitLoopClosure()();
            return true;
        }
        if (event == ftxui::Event::Character('c')) {
            if (app_->isConnected()) {
                app_->disconnectModbus();
            } else {
                SerialConfig cfg;
                cfg.device = device_input_;
                cfg.baud = std::stoi(baud_input_);
                cfg.slave_id = std::stoi(slave_input_);
                app_->setConfig(cfg);
                app_->connectModbus(cfg);
            }
            return true;
        }
        if (event == ftxui::Event::Character('r')) {
            if (app_->isConnected()) {
                app_->readHoldingRegs(0, 10);
            }
            return true;
        }
        return false;
    });

    screen.Loop(with_shortcuts);
}
