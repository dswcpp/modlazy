#pragma once

#include "Node.h"
#include "Edge.h"
#include <memory>
#include <vector>
#include <map>

class StateGraph {
public:
    void addNode(const std::string& name, std::shared_ptr<Node> node);
    void addEdge(const Edge& edge);
    void setEntryPoint(const std::string& node);

    AppState run(AppState initial_state);

private:
    std::map<std::string, std::shared_ptr<Node>> nodes_;
    std::vector<Edge> edges_;
    std::string entry_point_;

    std::string getNextNode(const std::string& current, const AppState& state);
};
