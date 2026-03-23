# ModLazy 架构设计文档

## 项目概述

ModLazy 是一个类似 lazygit 风格的 RS485/Modbus RTU 终端工具，提供现代化的 TUI 界面用于 Modbus 设备调试。

## 技术栈

- **语言**: C++17
- **构建系统**: CMake 3.16+
- **UI 框架**: FTXUI (终端 UI)
- **通信库**: libmodbus (Modbus RTU)

## 系统架构

```
┌─────────────────────────────────────────┐
│           MainView (主界面)              │
├─────────────────────────────────────────┤
│  StatusBar (状态栏)                      │
├───────────┬───────────┬─────────────────┤
│Connection │Operation  │ Help            │
│Panel      │Panel      │ Panel           │
├───────────┴───────────┴─────────────────┤
│         LogPanel (日志面板)              │
├─────────────────────────────────────────┤
│         CommandBar (命令栏)              │
└─────────────────────────────────────────┘
```

## 核心模块

### 1. App (应用核心)
- 管理 Modbus 连接
- 处理读写操作
- 维护日志队列
- 执行命令解析

### 2. ModbusClient (通信层)
- 封装 libmodbus
- 串口连接管理
- Modbus RTU 协议实现

### 3. UI 组件

#### StatusBar
- 显示连接状态
- 显示设备配置信息

#### ConnectionPanel
- 串口参数配置
- 连接/断开操作

#### OperationPanel
- 读保持寄存器
- 写单个寄存器
- 快速操作按钮

#### LogPanel
- 实时日志显示
- 支持滚动查看
- 颜色区分日志类型

#### HelpPanel
- 快捷键说明
- 使用提示

#### CommandBar
- 命令行输入
- 命令解析执行

#### MessageBox
- 消息提示弹窗
- 支持 Info/Warning/Error 类型

## 数据流

```
用户操作 → UI组件 → App → ModbusClient → 串口设备
                ↓
              日志系统
```

