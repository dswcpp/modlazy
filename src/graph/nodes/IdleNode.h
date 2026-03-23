#pragma once

#include "graph/Node.h"

class IdleNode : public Node {
public:
    AppState process(AppState state) override;
    std::string getName() const override { return "idle"; }
};
