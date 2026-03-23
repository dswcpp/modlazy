#include "StateGraph.h"

void StateGraph::addNode(const std::string& name, std::shared_ptr<Node> node) {
    nodes_[name] = node;
}

void StateGraph::addEdge(const Edge& edge) {
    edges_.push_back(edge);
}

void StateGraph::setEntryPoint(const std::string& node) {
    entry_point_ = node;
}

AppState StateGraph::run(AppState initial_state) {
    std::string current = entry_point_;
    AppState state = initial_state;

    while (!current.empty()) {
        auto it = nodes_.find(current);
        if (it == nodes_.end()) break;

        state = it->second->process(state);
        current = getNextNode(current, state);
    }

    return state;
}

std::string StateGraph::getNextNode(const std::string& current, const AppState& state) {
    for (const auto& edge : edges_) {
        if (edge.from == current) {
            if (!edge.condition || edge.condition(state)) {
                return edge.to;
            }
        }
    }
    return "";
}

