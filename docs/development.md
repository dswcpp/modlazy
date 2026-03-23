# ModLazy 开发指南

## 编译构建

### 依赖安装
```bash
# Ubuntu/Debian
sudo apt install build-essential cmake git
sudo apt install autoconf automake libtool

# macOS
brew install cmake autoconf automake libtool
```

### 编译步骤
```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### 运行
```bash
./modlazy
```

## 项目结构

```
modlazy/
├── src/
│   ├── main.cpp           # 入口
│   ├── app/               # 应用核心
│   ├── modbus/            # Modbus 客户端
│   └── ui/                # UI 组件
├── third_party/
│   ├── libmodbus/         # Modbus 库
│   └── ftxui/             # UI 框架
├── docs/                  # 文档
└── CMakeLists.txt
```

## 添加新 UI 组件

1. 创建头文件 `src/ui/NewPanel.h`
2. 创建实现文件 `src/ui/NewPanel.cpp`
3. 在 `CMakeLists.txt` 中添加源文件
4. 在 `MainView` 中集成

## 代码规范

- 使用 C++17 标准
- 类名使用 PascalCase
- 函数/变量使用 camelCase
- 成员变量使用 `name_` 后缀
- 常量使用 UPPER_SNAKE_CASE

## 调试

```bash
# 编译 Debug 版本
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

# 使用 gdb 调试
gdb ./modlazy
```

## 版本发布

```bash
git tag -a v0.x.x -m "Release v0.x.x"
git push --tags
```

