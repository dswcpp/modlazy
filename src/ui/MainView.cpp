#include "MainView.h"
#include "app/App.h"
#include "ConnectionPanel.h"
#include "OperationPanel.h"
#include "LogPanel.h"
#include "HelpPanel.h"
#include "CommandBar.h"
#include "StatusBar.h"
#include "MessageBox.h"
#include "modbus/ModbusClient.h"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

MainView::MainView(App* app)
    : app_(app),
      conn_panel_(std::make_unique<ConnectionPanel>(app)),
      op_panel_(std::make_unique<OperationPanel>(app)),
      log_panel_(std::make_unique<LogPanel>(app)),
      help_panel_(std::make_unique<HelpPanel>()),
      cmd_bar_(std::make_unique<CommandBar>([app](const std::string& cmd) {
          app->executeCommand(cmd);
      })),
      status_bar_(std::make_unique<StatusBar>(app)) {}

MainView::~MainView() = default;

ftxui::Component MainView::GetComponent() {
    auto conn = conn_panel_->GetComponent();
    auto op = op_panel_->GetComponent();
    auto help = help_panel_->GetComponent();
    auto log = log_panel_->GetComponent();
    auto cmd = cmd_bar_->GetComponent();
    auto status = status_bar_->GetComponent();

    auto container = ftxui::Container::Vertical({
        status,
        ftxui::Container::Horizontal({conn, op, help}),
        log,
        cmd
    });

    return ftxui::Renderer(container, [=, this] {
        // 检查是否有新消息
        if (app_->hasMessage()) {
            message_text_ = app_->popMessage();
            show_message_ = true;
        }

        auto main_view = ftxui::vbox({
            status->Render(),
            ftxui::separator(),
            ftxui::hbox({
                conn->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30),
                ftxui::separator(),
                op->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30),
                ftxui::separator(),
                help->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30)
            }),
            ftxui::separator(),
            log->Render() | ftxui::flex,
            ftxui::separator(),
            cmd->Render() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3)
        });

        if (show_message_) {
            return ftxui::dbox({
                main_view,
                ftxui::vbox({
                    ftxui::text(message_text_) | ftxui::center,
                    ftxui::text("Press any key to close") | ftxui::dim | ftxui::center
                }) | ftxui::border | ftxui::center
            });
        }

        return main_view;
    });
}

void MainView::Run() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    auto component = GetComponent();

    auto with_shortcuts = ftxui::CatchEvent(component, [&](ftxui::Event event) {
        if (show_message_) {
            show_message_ = false;
            return true;
        }
        if (event == ftxui::Event::Character('q')) {
            screen.ExitLoopClosure()();
            return true;
        }
        if (event == ftxui::Event::Character('c')) {
            if (app_->isConnected()) {
                app_->disconnectModbus();
            } else {
                auto& cfg = app_->getConfig();
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
