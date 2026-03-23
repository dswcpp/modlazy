# ModLazy LangGraph 架构设计

## 概述

引入 LangGraph 风格的状态图架构，为后续接入大模型（LLM）做准备。

## 核心概念

### 1. 状态图（State Graph）

```
        ┌─────────────┐
        │   START     │
        └──────┬──────┘
               │
        ┌──────▼──────┐
        │  IDLE       │◄────────┐
        └──────┬──────┘         │
               │                │
        ┌──────▼──────┐         │
        │  CONNECTING │         │
        └──────┬──────┘         │
               │                │
        ┌──────▼──────┐         │
        │  CONNECTED  │─────────┤
        └──────┬──────┘         │
               │                │
        ┌──────▼──────┐         │
        │  EXECUTING  │─────────┤
        └──────┬──────┘         │
               │                │
        ┌──────▼──────┐         │
        │  ERROR      │─────────┘
        └─────────────┘
```

### 2. 节点（Nodes）

每个节点代表一个状态处理器：

```cpp
class Node {
    virtual State process(State input) = 0;
    virtual std::string getName() = 0;
};
```

**核心节点：**
- `IdleNode` - 空闲状态
- `ConnectNode` - 连接处理
- `ExecuteNode` - 命令执行
- `ErrorNode` - 错误处理
- `LLMNode` - LLM 推理（预留）
```

### 3. 边（Edges）

定义状态转换条件：

```cpp
class Edge {
    std::string from;
    std::string to;
    std::function<bool(State)> condition;
};
```

### 4. 状态（State）

```cpp
struct AppState {
    ConnectionStatus connection;
    std::vector<LogEntry> logs;
    std::string last_command;
    std::optional<std::string> error;
    std::map<std::string, std::any> context;
};
```

## LLM 集成设计

### 1. LLM 节点

```cpp
class LLMNode : public Node {
    State process(State input) override {
        // 调用 LLM API
        auto response = llm_->chat(input.last_command);
        // 解析为 Modbus 命令
        auto command = parseCommand(response);
        return executeCommand(command, input);
    }
};
```

### 2. 应用场景

- **自然语言命令**: "读取地址 100 的 10 个寄存器"
- **智能诊断**: 分析日志，给出建议
- **自动化脚本**: 生成测试序列

## 实现步骤

### Phase 1: 基础图架构
1. 实现 StateGraph 类
2. 实现基础节点（Idle, Connect, Execute）
3. 定义状态转换规则

### Phase 2: LLM 集成
1. 添加 LLM 客户端接口
2. 实现 LLMNode
3. 命令解析器

### Phase 3: 高级功能
1. 对话历史管理
2. 上下文记忆
3. 智能建议




