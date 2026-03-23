#include "ConnectionPanel.h"
#include "app/App.h"
#include "modbus/ModbusClient.h"
#include "ftxui/dom/elements.hpp"

ConnectionPanel::ConnectionPanel(App* app) : app_(app) {}

ftxui::Component ConnectionPanel::GetComponent() {
    auto device_input = ftxui::Input(&device_input_, "Device");
    auto baud_input = ftxui::Input(&baud_input_, "Baud");
    auto parity_input = ftxui::Input(&parity_input_, "Parity");
    auto data_bits_input = ftxui::Input(&data_bits_input_, "Data bits");
    auto stop_bits_input = ftxui::Input(&stop_bits_input_, "Stop bits");
    auto slave_input = ftxui::Input(&slave_input_, "Slave");
    auto timeout_input = ftxui::Input(&timeout_input_, "Timeout(ms)");

    auto connect_btn = ftxui::Button("Connect", [this] {
        if (!app_->isConnected()) {
            try {
                SerialConfig cfg;
                cfg.device = device_input_;
                cfg.baud = std::stoi(baud_input_);
                cfg.parity = parity_input_.empty() ? 'N' : parity_input_[0];
                cfg.data_bits = std::stoi(data_bits_input_);
                cfg.stop_bits = std::stoi(stop_bits_input_);
                cfg.slave_id = std::stoi(slave_input_);
                cfg.response_timeout_ms = std::stoi(timeout_input_);

                if (cfg.baud <= 0) {
                    error_msg_ = "Invalid baud rate";
                    return;
                }
                if (cfg.slave_id < 1 || cfg.slave_id > 247) {
                    error_msg_ = "Slave ID must be 1-247";
                    return;
                }

                error_msg_.clear();
                app_->setConfig(cfg);
                app_->connectModbus(cfg);
            } catch (const std::exception& e) {
                error_msg_ = "Invalid input: " + std::string(e.what());
            }
        }
    });

    auto disconnect_btn = ftxui::Button("Disconnect", [this] {
        if (app_->isConnected()) {
            app_->disconnectModbus();
        }
    });

    auto container = ftxui::Container::Vertical({
        device_input, baud_input, parity_input, data_bits_input,
        stop_bits_input, slave_input, timeout_input,
        ftxui::Container::Horizontal({connect_btn, disconnect_btn})
    });

    return ftxui::Renderer(container, [this, device_input, baud_input, parity_input,
                                       data_bits_input, stop_bits_input, slave_input,
                                       timeout_input, connect_btn, disconnect_btn] {
        auto status = app_->isConnected() ? "Connected" : "Disconnected";

        return ftxui::vbox({
            ftxui::text("Connection") | ftxui::bold,
            ftxui::separator(),
            ftxui::hbox({ftxui::text("Device:  "), device_input->Render()}),
            ftxui::hbox({ftxui::text("Baud:    "), baud_input->Render()}),
            ftxui::hbox({ftxui::text("Parity:  "), parity_input->Render()}),
            ftxui::hbox({ftxui::text("Data:    "), data_bits_input->Render()}),
            ftxui::hbox({ftxui::text("Stop:    "), stop_bits_input->Render()}),
            ftxui::hbox({ftxui::text("Slave:   "), slave_input->Render()}),
            ftxui::hbox({ftxui::text("Timeout: "), timeout_input->Render()}),
            ftxui::separator(),
            ftxui::hbox({connect_btn->Render(), ftxui::text(" "), disconnect_btn->Render()}),
            ftxui::separator(),
            ftxui::text("Status: " + std::string(status)) |
                (app_->isConnected() ? ftxui::color(ftxui::Color::Green) : ftxui::color(ftxui::Color::Red)),
            error_msg_.empty() ? ftxui::text("") : (ftxui::text("Error: " + error_msg_) | ftxui::color(ftxui::Color::Red))
        }) | ftxui::border;
    });
}
