cmake_minimum_required(VERSION 3.16)
project(modlazy LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# libmodbus from source
include(ExternalProject)
set(LIBMODBUS_PREFIX ${CMAKE_BINARY_DIR}/libmodbus)
set(LIBMODBUS_INSTALL ${LIBMODBUS_PREFIX}/install)

ExternalProject_Add(
    libmodbus_external
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/third_party/libmodbus
    CONFIGURE_COMMAND ${CMAKE_SOURCE_DIR}/third_party/libmodbus/autogen.sh
        COMMAND ${CMAKE_SOURCE_DIR}/third_party/libmodbus/configure
        --prefix=${LIBMODBUS_INSTALL}
        --enable-static
        --disable-shared
    BUILD_COMMAND make
    INSTALL_COMMAND make install
    BUILD_IN_SOURCE 1
)

set(LIBMODBUS_INCLUDE_DIRS ${LIBMODBUS_INSTALL}/include/modbus)
set(LIBMODBUS_LIBRARIES ${LIBMODBUS_INSTALL}/lib/libmodbus.a)

# FTXUI from source
add_subdirectory(third_party/ftxui EXCLUDE_FROM_ALL)

# Source files
add_executable(modlazy
    src/main.cpp
    src/modbus/ModbusClient.cpp
    src/app/App.cpp
    src/ui/MainView.cpp
    src/ui/ConnectionPanel.cpp
    src/ui/OperationPanel.cpp
    src/ui/LogPanel.cpp
    src/ui/HelpPanel.cpp
    src/ui/CommandBar.cpp
    src/ui/StatusBar.cpp
    src/ui/MessageBox.cpp
    src/graph/StateGraph.cpp
    src/graph/nodes/IdleNode.cpp
    src/graph/nodes/ConnectNode.cpp
    src/graph/nodes/ExecuteNode.cpp
    src/graph/nodes/LLMNode.cpp
    src/llm/MockLLMClient.cpp
)

target_include_directories(modlazy PRIVATE
    ${LIBMODBUS_INCLUDE_DIRS}
    ${LIBMODBUS_INSTALL}/include
    src
)

target_link_libraries(modlazy PRIVATE
    ${LIBMODBUS_LIBRARIES}
    ftxui::screen
    ftxui::dom
    ftxui::component
)

add_dependencies(modlazy libmodbus_external)

target_compile_options(modlazy PRIVATE
    -Wall -Wextra -Wpedantic
    ${LIBMODBUS_CFLAGS_OTHER}
)
