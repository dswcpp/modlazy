#pragma once

#include <string>
#include <map>
#include <any>
#include <vector>
#include <optional>

enum class ConnectionStatus {
    Disconnected,
    Connecting,
    Connected,
    Error
};

struct LogEntry;

struct AppState {
    ConnectionStatus connection = ConnectionStatus::Disconnected;
    std::vector<LogEntry>* logs = nullptr;
    std::string last_command;
    std::optional<std::string> error;
    std::map<std::string, std::any> context;
};
