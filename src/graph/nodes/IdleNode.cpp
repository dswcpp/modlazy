#include "IdleNode.h"

AppState IdleNode::process(AppState state) {
    // 空闲状态，等待命令
    return state;
}
