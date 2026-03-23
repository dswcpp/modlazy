#include "OperationPanel.h"
#include "app/App.h"
#include "ftxui/dom/elements.hpp"

OperationPanel::OperationPanel(App* app) : app_(app) {}

ftxui::Component OperationPanel::GetComponent() {
    auto read_addr = ftxui::Input(&read_addr_, "Address");
    auto read_count = ftxui::Input(&read_count_, "Count");
    auto read_btn = ftxui::Button("Read", [this] {
        if (!app_->isConnected()) return;
        try {
            app_->readHoldingRegs(std::stoi(read_addr_, nullptr, 0), std::stoi(read_count_, nullptr, 0));
        } catch (...) {}
    });

    auto write_addr = ftxui::Input(&write_addr_, "Address");
    auto write_value = ftxui::Input(&write_value_, "Value");
    auto write_btn = ftxui::Button("Write", [this] {
        if (!app_->isConnected()) return;
        try {
            app_->writeSingleReg(std::stoi(write_addr_, nullptr, 0), std::stoi(write_value_, nullptr, 0));
        } catch (...) {}
    });

    auto quick_0 = ftxui::Button("0x00", [this] {
        if (app_->isConnected()) app_->readHoldingRegs(0x00, 10);
    });
    auto quick_1 = ftxui::Button("0x10", [this] {
        if (app_->isConnected()) app_->readHoldingRegs(0x10, 10);
    });
    auto quick_2 = ftxui::Button("0x100", [this] {
        if (app_->isConnected()) app_->readHoldingRegs(0x100, 10);
    });

    auto container = ftxui::Container::Vertical({
        read_addr, read_count, read_btn,
        write_addr, write_value, write_btn,
        ftxui::Container::Horizontal({quick_0, quick_1, quick_2})
    });

    return ftxui::Renderer(container, [=] {
        return ftxui::vbox({
            ftxui::text("Operations") | ftxui::bold,
            ftxui::separator(),
            ftxui::text("Read:"),
            ftxui::hbox({ftxui::text("Addr: "), read_addr->Render()}),
            ftxui::hbox({ftxui::text("Cnt:  "), read_count->Render()}),
            read_btn->Render(),
            ftxui::separator(),
            ftxui::text("Write:"),
            ftxui::hbox({ftxui::text("Addr: "), write_addr->Render()}),
            ftxui::hbox({ftxui::text("Val:  "), write_value->Render()}),
            write_btn->Render(),
            ftxui::separator(),
            ftxui::text("Quick:") | ftxui::dim,
            ftxui::hbox({quick_0->Render(), quick_1->Render(), quick_2->Render()})
        }) | ftxui::border;
    });
}


