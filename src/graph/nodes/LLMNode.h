#pragma once

#include "graph/Node.h"
#include <memory>

class LLMClient;
class App;

class LLMNode : public Node {
public:
    LLMNode(std::shared_ptr<LLMClient> llm, App* app);
    AppState process(AppState state) override;
    std::string getName() const override { return "llm"; }

private:
    std::shared_ptr<LLMClient> llm_;
    App* app_;

    std::string parseCommand(const std::string& response);
};
