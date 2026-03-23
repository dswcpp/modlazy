#include "OperationPanel.h"
#include "app/App.h"
#include "ftxui/dom/elements.hpp"

OperationPanel::OperationPanel(App* app) : app_(app) {}

ftxui::Component OperationPanel::GetComponent() {
    auto read_addr = ftxui::Input(&read_addr_input_, "Address");
    auto read_count = ftxui::Input(&read_count_input_, "Count");
    auto read_btn = ftxui::Button("Read", [this] {
        if (!app_->isConnected()) return;
        try {
            int addr = std::stoi(read_addr_input_, nullptr, 0);
            int count = std::stoi(read_count_input_, nullptr, 0);
            app_->readHoldingRegs(addr, count);
        } catch (...) {}
    });

    auto write_addr = ftxui::Input(&write_addr_input_, "Address");
    auto write_value = ftxui::Input(&write_value_input_, "Value");
    auto write_btn = ftxui::Button("Write", [this] {
        if (!app_->isConnected()) return;
        try {
            int addr = std::stoi(write_addr_input_, nullptr, 0);
            int value = std::stoi(write_value_input_, nullptr, 0);
            app_->writeSingleReg(addr, value);
        } catch (...) {}
    });

    auto container = ftxui::Container::Vertical({
        read_addr, read_count, read_btn,
        write_addr, write_value, write_btn
    });

    return ftxui::Renderer(container, [=] {
        return ftxui::vbox({
            ftxui::text("Operations") | ftxui::bold,
            ftxui::separator(),
            ftxui::text("Read Holding:"),
            ftxui::hbox({ftxui::text("Addr: "), read_addr->Render()}),
            ftxui::hbox({ftxui::text("Cnt:  "), read_count->Render()}),
            read_btn->Render(),
            ftxui::separator(),
            ftxui::text("Write Single:"),
            ftxui::hbox({ftxui::text("Addr: "), write_addr->Render()}),
            ftxui::hbox({ftxui::text("Val:  "), write_value->Render()}),
            write_btn->Render()
        }) | ftxui::border;
    });
}
