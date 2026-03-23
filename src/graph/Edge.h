#pragma once

#include "State.h"
#include <string>
#include <functional>

class Edge {
public:
    std::string from;
    std::string to;
    std::function<bool(const AppState&)> condition;

    Edge(std::string f, std::string t, std::function<bool(const AppState&)> cond = nullptr)
        : from(f), to(t), condition(cond) {}
};
