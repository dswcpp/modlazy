#pragma once

#include "graph/Node.h"

class App;

class ExecuteNode : public Node {
public:
    explicit ExecuteNode(App* app) : app_(app) {}
    AppState process(AppState state) override;
    std::string getName() const override { return "execute"; }

private:
    App* app_;
};
