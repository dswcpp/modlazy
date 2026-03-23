# ModLazy - RS485/Modbus RTU TUI Tool

一个类似 lazygit 风格的 RS485/Modbus RTU 终端工具。

## 特性

- 🖥️ 现代化 TUI 界面（基于 FTXUI）
- 🔌 支持 Modbus RTU 串口通信（基于 libmodbus）
- 📊 实时日志显示
- ⚡ 快捷键操作
- 💾 会话保存

## 依赖

- C++17 或更高
- CMake 3.16+
- libmodbus
- FTXUI（通过 FetchContent 自动获取）

## 编译

```bash
mkdir build && cd build
cmake ..
make
```

## 运行

```bash
./modlazy
```

## 快捷键

- `Tab` - 切换面板
- `c` - 连接/断开
- `r` - 读保持寄存器
- `q` - 退出
- `:` - 命令模式

## 命令

```
:connect /dev/ttyUSB0 9600 N 8 1
:slave 1
:read holding 0 10
```
