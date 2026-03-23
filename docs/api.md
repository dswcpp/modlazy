# ModLazy API 文档

## 命令行接口

### 连接命令
```
connect <device> <baud> <parity> <data_bits> <stop_bits>
```
示例：`connect /dev/ttyUSB0 9600 N 8 1`

### 断开连接
```
disconnect
```

### 设置从站 ID
```
slave <id>
```
示例：`slave 1`

### 读保持寄存器
```
read holding <addr> <count>
```
示例：`read holding 0x0000 10`

### 写单个寄存器
```
write <addr> <value>
```
示例：`write 0x0010 0xFF`

## 快捷键

- `q` - 退出程序
- `c` - 快速连接/断开
- `r` - 快速读取（地址 0x0000，数量 10）
- `Tab` - 切换焦点
- `↑↓` - 滚动日志

## 数据格式

所有地址和数值支持：
- 十六进制：`0x10`, `0xFF`
- 十进制：`16`, `255`
