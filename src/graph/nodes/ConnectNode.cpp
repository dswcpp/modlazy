#include "ConnectNode.h"
#include "../../app/App.h"

AppState ConnectNode::process(AppState state) {
    state.connection = ConnectionStatus::Connecting;

    if (app_->isConnected()) {
        state.connection = ConnectionStatus::Connected;
    } else {
        state.connection = ConnectionStatus::Disconnected;
        state.error = "Connection failed";
    }

    return state;
}
