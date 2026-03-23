#!/bin/bash

set -e

echo "==> 配置项目..."
mkdir -p build
cd build
cmake ..

echo "==> 编译项目..."
make -j$(nproc)

echo "==> 编译完成！"
echo "运行: ./build/modlazy"
