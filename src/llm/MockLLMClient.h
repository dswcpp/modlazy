#pragma once

#include "LLMClient.h"

class MockLLMClient : public LLMClient {
public:
    std::string chat(const std::vector<Message>& messages) override;
};
