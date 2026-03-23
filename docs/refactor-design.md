# ModLazy 重构架构设计

## 当前问题

1. UI 组件直接调用 App，耦合度高
2. 缺少状态管理
3. 没有事件系统
4. 错误处理分散

## 新架构设计

### 1. 分层架构

```
┌─────────────────────────────────────┐
│     Presentation Layer (UI)         │
│  ┌──────────┬──────────┬─────────┐  │
│  │ Panels   │ Views    │ Widgets │  │
│  └──────────┴──────────┴─────────┘  │
├─────────────────────────────────────┤
│     Application Layer               │
│  ┌──────────┬──────────┬─────────┐  │
│  │ Commands │ Queries  │ Events  │  │
│  └──────────┴──────────┴─────────┘  │
├─────────────────────────────────────┤
│     Domain Layer                    │
│  ┌──────────┬──────────┬─────────┐  │
│  │ Entities │ Services │ State   │  │
│  └──────────┴──────────┴─────────┘  │
├─────────────────────────────────────┤
│     Infrastructure Layer            │
│  ┌──────────┬──────────┬─────────┐  │
│  │ Modbus   │ Serial   │ Logger  │  │
│  └──────────┴──────────┴─────────┘  │
└─────────────────────────────────────┘
```

### 2. 状态机设计

```
┌─────────────┐
│ Disconnected│
└──────┬──────┘
       │ connect
       ↓
┌─────────────┐
│ Connecting  │
└──────┬──────┘
       │ success
       ↓
┌─────────────┐     read/write
│  Connected  │◄──────────────┐
└──────┬──────┘               │
       │ disconnect           │
       ↓                      │
┌─────────────┐               │
│Disconnecting│───────────────┘
└─────────────┘
```

### 3. 事件驱动

```cpp
// 事件类型
enum class EventType {
    ConnectionChanged,
    DataReceived,
    ErrorOccurred,
    CommandExecuted
};

// 事件总线
class EventBus {
    void publish(Event event);
    void subscribe(EventType type, Handler handler);
};
```

### 4. CQRS 模式

**Commands (写操作)**
- ConnectCommand
- DisconnectCommand
- ReadRegisterCommand
- WriteRegisterCommand

**Queries (读操作)**
- GetConnectionStatusQuery
- GetLogsQuery
- GetConfigQuery

### 5. 依赖注入

```cpp
class ServiceContainer {
    template<typename T>
    void register(std::shared_ptr<T> service);

    template<typename T>
    std::shared_ptr<T> resolve();
};
```

## 重构步骤

1. 引入事件总线
2. 实现状态机
3. 分离命令和查询
4. 添加依赖注入容器
5. 重构 UI 组件使用事件订阅


