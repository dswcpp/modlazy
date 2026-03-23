#include "LLMNode.h"
#include "llm/LLMClient.h"
#include "app/App.h"

LLMNode::LLMNode(std::shared_ptr<LLMClient> llm, App* app)
    : llm_(llm), app_(app) {}

AppState LLMNode::process(AppState state) {
    if (state.last_command.empty()) return state;

    std::vector<Message> messages = {
        {"user", state.last_command}
    };

    std::string response = llm_->chat(messages);
    std::string command = parseCommand(response);

    if (!command.empty()) {
        app_->executeCommand(command);
    }

    state.last_command.clear();
    return state;
}

std::string LLMNode::parseCommand(const std::string& response) {
    // 简单解析：提取命令行
    // 后续可以使用更复杂的解析逻辑
    size_t pos = response.find("```");
    if (pos != std::string::npos) {
        size_t end = response.find("```", pos + 3);
        if (end != std::string::npos) {
            return response.substr(pos + 3, end - pos - 3);
        }
    }
    return response;
}

