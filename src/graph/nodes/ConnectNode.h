#pragma once

#include "graph/Node.h"

class App;

class ConnectNode : public Node {
public:
    explicit ConnectNode(App* app) : app_(app) {}
    AppState process(AppState state) override;
    std::string getName() const override { return "connect"; }

private:
    App* app_;
};
