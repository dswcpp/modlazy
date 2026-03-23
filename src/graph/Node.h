#pragma once

#include "State.h"
#include <string>

class Node {
public:
    virtual ~Node() = default;
    virtual AppState process(AppState state) = 0;
    virtual std::string getName() const = 0;
};
