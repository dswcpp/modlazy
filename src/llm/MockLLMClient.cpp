#include "MockLLMClient.h"

std::string MockLLMClient::chat(const std::vector<Message>& messages) {
    if (messages.empty()) return "";

    auto& user_msg = messages.back().content;

    // 简单的规则匹配
    if (user_msg.find("读") != std::string::npos || user_msg.find("read") != std::string::npos) {
        return "read holding 0x0000 10";
    }
    if (user_msg.find("写") != std::string::npos || user_msg.find("write") != std::string::npos) {
        return "write 0x0000 0xFF";
    }

    return "Unknown command";
}
