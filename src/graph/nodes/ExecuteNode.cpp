#include "ExecuteNode.h"
#include "../../app/App.h"

AppState ExecuteNode::process(AppState state) {
    if (!state.last_command.empty()) {
        app_->executeCommand(state.last_command);
        state.last_command.clear();
    }
    return state;
}
