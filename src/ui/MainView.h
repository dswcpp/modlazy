#pragma once

#include "ftxui/component/component.hpp"
#include <memory>

class App;
class ConnectionPanel;
class OperationPanel;
class LogPanel;
class HelpPanel;
class CommandBar;
class StatusBar;

class MainView {
public:
    explicit MainView(App* app);
    ~MainView();

    ftxui::Component GetComponent();
    void Run();

private:
    App* app_;

    std::unique_ptr<ConnectionPanel> conn_panel_;
    std::unique_ptr<OperationPanel> op_panel_;
    std::unique_ptr<LogPanel> log_panel_;
    std::unique_ptr<HelpPanel> help_panel_;
    std::unique_ptr<CommandBar> cmd_bar_;
    std::unique_ptr<StatusBar> status_bar_;

    bool show_message_ = false;
    std::string message_text_;
};
